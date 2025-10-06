#include <iostream>         // Для std::cout, std::cerr
#include "FileReader.h"     // Подключение класса FileReader
#include "WordTokenizer.h"  // Подключение класса WordTokenizer
#include "FrequencyCounter.h" // Подключение класса FrequencyCounter
#include "CSVWriter.h"      // Подключение класса CSVWriter

// Главная функция программы
int main(int argc, char* argv[]) {
    // Проверка количества аргументов командной строки
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.csv>\n";
        return 1;  // Возврат кода ошибки
    }

    // Блок try-catch для обработки исключений
    try {
        FileReader reader;        // Создание объекта для чтения файлов
        WordTokenizer tokenizer;  // Создание объекта для разбиения на слова
        FrequencyCounter counter; // Создание объекта для подсчета частот
        CSVWriter writer;         // Создание объекта для записи CSV

        // Чтение всех строк из входного файла
        auto lines = reader.readLines(argv[1]);
        
        // Разбиение строк на отдельные слова
        auto words = tokenizer.tokenize(lines);
        
        // Подсчет частоты каждого слова
        auto freqMap = counter.count(words);
        
        // Запись результатов в выходной CSV файл
        writer.write(argv[2], freqMap);
        
    } catch (const std::exception& e) {
        // Обработка и вывод ошибок
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;  // Возврат кода ошибки
    }

    return 0;  // Успешное завершение программы
} 
