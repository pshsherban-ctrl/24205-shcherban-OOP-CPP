#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

// Функция для запуска программы и проверки кода возврата
bool runProgram(const std::vector<std::string>& args, int expectedExitCode) {
    std::string command = "./word_count";
    for (const auto& arg : args) {
        command += " " + arg;
    }
    
    int result = system(command.c_str());
    return WEXITSTATUS(result) == expectedExitCode;
}

// Функция для проверки существования файла
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Функция для проверки содержимого файла
bool fileContains(const std::string& filename, const std::string& content) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(content) != std::string::npos) {
            return true;
        }
    }
    return false;
}

int main() {
    // Компилируем программу
    std::cout << "Компиляция программы" << std::endl;
    if (system("g++ -I. -o word_count main.cpp FileReader.cpp WordTokenizer.cpp FrequencyCounter.cpp CSVWriter.cpp") != 0) {
        std::cerr << "Ошибка компиляции!" << std::endl;
        return 1;
    }
    
    std::cout << "Компиляция успешна!" << std::endl;
    
    // Тест 1: Запуск без аргументов
    std::cout << "Тест 1: Запуск без аргументов" << std::endl;
    if (runProgram({}, 1)) {
        std::cout << "Тест 1 пройден" << std::endl;
    } else {
        std::cerr << "Тест 1 не пройден" << std::endl;
        return 1;
    }
    
    // Тест 2: Запуск с одним аргументом
    std::cout << "Тест 2: Запуск с одним аргументом" << std::endl;
    if (runProgram({"input.txt"}, 1)) {
        std::cout << "Тест 2 пройден" << std::endl;
    } else {
        std::cerr << "Тест 2 не пройден" << std::endl;
        return 1;
    }
    
    // Тест 3: Несуществующий входной файл
    std::cout << "Тест 3: Несуществующий входной файл" << std::endl;
    if (runProgram({"nonexist.txt", "input.txt"}, 1)) {
        std::cout << "Тест 3 пройден" << std::endl;
    } else {
        std::cerr << "Тест 3 не пройден" << std::endl;
        return 1;
    }
    
    // Тест 4: Нормальная работа
    std::cout << "Тест 4: Нормальная работа программы" << std::endl;
    
    // Создаем тестовый входной файл
    std::ofstream input("test_input.txt");
    input << "Hello world! This is a test.\n";
    input << "Testing, testing 123. Hello again!\n";
    input << "C++ programming is fun and challenging.";
    input.close();
    
    if (runProgram({"test_input.txt", "test_output.csv"}, 0)) {
        std::cout << "Программа завершилась успешно" << std::endl;
        
        // Проверяем выходной файл
        if (fileExists("test_output.csv")) {
            std::cout << "Выходной файл создан" << std::endl;
            
            if (fileContains("test_output.csv", "Word,Frequency,Frequency (%)")) {
                std::cout << "Заголовок CSV корректен" << std::endl;
            } else {
                std::cerr << "Заголовок CSV отсутствует" << std::endl;
                return 1;
            }
            
            // Выводим содержимое для проверки
            std::cout << "Содержимое CSV файла:" << std::endl;
            system("cat test_output.csv");
            
        } else {
            std::cerr << "Выходной файл не создан" << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Программа завершилась с ошибкой" << std::endl;
        return 1;
    }
    
    // Тест 5: Проверка обработки разных символов
    std::cout << "Тест 5: Проверка обработки специальных символов" << std::endl;
    
    std::ofstream input2("test_input2.txt");
    input2 << "Word1, word2; word3! word4? word5: word6 - word7.\n";
    input2 << "Multiple    spaces    between    words.";
    input2.close();
    
    if (runProgram({"test_input2.txt", "test_output2.csv"}, 0)) {
        std::cout << "Тест 5 пройден: специальные символы обработаны" << std::endl;
    } else {
        std::cerr << "Тест 5 не пройден" << std::endl;
        return 1;
    }
    
    system("rm -f test_input.txt test_output.csv test_input2.txt test_output2.csv word_count");
    
    std::cout << "Все тесты пройдены успешно!" << std::endl;
    return 0;
} 
