#include <fstream>   // Для работы с файлами (ifstream, ofstream)
#include <iostream>  // Для ввода/вывода (cout, cerr)
#include <list>      // Для использования контейнера std::list
#include <map>       // Для использования контейнера std::map
#include <vector>    // Для использования контейнера std::vector
#include <string>    // Для работы со строками std::string
#include <algorithm> // Для алгоритмов (sort)
#include <cctype>    // Для функций работы с символами (isalnum, tolower)

// Функция сравнения для сортировки по убыванию частоты
bool compare(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){
    return a.second > b.second; // Сравниваем по второму элементу (частоте)
}

int main(int argc, char* argv[]){
    // Проверка количества аргументов командной строки
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.csv>" << std::endl;
        return 1; // Возвращаем код ошибки
    }

    // Открываем входной файл для чтения
    std::ifstream input_file(argv[1]);
    // Проверяем, успешно ли открылся файл
    if (!input_file.is_open()){
        std::cerr << "Error: Cannot open input file." << std::endl;
        return 1; // Возвращаем код ошибки
    }

    // Создаем map для подсчета слов (ключ - слово, значение - частота)
    std::map<std::string, int> word_count;
    // Создаем list для хранения строк из файла (по требованию задания)
    std::list<std::string> lines;
    std::string line; // Переменная для хранения текущей строки

    // Читаем файл построчно с помощью std::getline
    while (std::getline(input_file, line)){
        lines.push_back(line); // Сохраняем строку в list
    }

    input_file.close(); // Закрываем входной файл

    // Обрабатываем каждую строку из list
    for (const auto& current_line : lines){
        std::string word; // Переменная для накопления текущего слова
        // Обрабатываем каждый символ в строке
        for (char c : current_line) {
            // Проверяем, является ли символ буквой или цифрой
            if (std::isalnum(static_cast<unsigned char>(c))){
                // Добавляем символ к текущему слову (в нижнем регистре)
                word += std::tolower(static_cast<unsigned char>(c));
            }else if (!word.empty()){
                // Если встретили разделитель и слово не пустое
                word_count[word]++; // Увеличиваем счетчик для этого слова
                word.clear(); // Очищаем переменную для следующего слова
            }
        }
        // Обрабатываем последнее слово в строке (если оно есть)
        if (!word.empty()){
            word_count[word]++; // Увеличиваем счетчик для последнего слова
        }
    }

    // Создаем вектор из пар (слово, частота) для сортировки
    std::vector<std::pair<std::string, int>> words(word_count.begin(), word_count.end());
    // Сортируем вектор по убыванию частоты с помощью функции compare
    std::sort(words.begin(), words.end(), compare);

    // Подсчитываем общее количество слов
    int total_words = 0;
    for (const auto& pair : words){
        total_words += pair.second; // Суммируем все частоты
    }

    // Открываем выходной файл для записи
    std::ofstream output_file(argv[2]);
    // Проверяем, успешно ли открылся файл
    if (!output_file.is_open()){
        std::cerr << "Error: Cannot open output file." << std::endl;
        return 1; // Возвращаем код ошибки
    }

    // Записываем данные в CSV файл
    for (const auto& pair : words){
        // Вычисляем процентную частоту
        double percentage = (static_cast<double>(pair.second) / total_words) * 100.0;
        // Записываем: слово, частота, частота в процентах
        output_file << pair.first << "," << pair.second << "," << percentage << "\n";
    }
    output_file.close(); // Закрываем выходной файл

    return 0; // Успешное завершение программы
}