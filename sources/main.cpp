#include <iostream>         // Для std::cout, std::cerr
#include <map>
#include "FileReader.h"     // Подключение класса FileReader
#include "WordTokenizer.h"  // Подключение класса WordTokenizer
#include "FrequencyCounter.h" // Подключение класса FrequencyCounter
#include "CSVWriter.h"      // Подключение класса CSVWriter

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
                // Используем map для накопления частот слов
        std::map<std::string, int> wordFrequencies;
        int totalWords = 0;  // Счетчик общего количества слов
        // Потоковая обработка файла
        reader.readLinesStreaming(argv[1], [&](const std::string& line) {
            // Обрабатываем каждую строку и сразу подсчитываем слова
            tokenizer.tokenizeStreaming(line, [&](const std::string& word) {
                wordFrequencies[word]++;  // Увеличиваем счетчик для слова
                totalWords++;              // Увеличиваем общий счетчик
            });
        });
        
        CSVWriter writer;
        writer.write(argv[2], wordFrequencies);
    } catch (const std::exception& e) {
        // Обработка и вывод ошибок
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;  // Возврат кода ошибки
    }

    return 0;  // Успешное завершение программы
} 
