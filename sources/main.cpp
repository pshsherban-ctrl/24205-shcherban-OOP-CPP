#include <iostream>         // Для std::cout, std::cerr
#include "FileReader.h"     
#include "WordTokenizer.h"  
#include "FrequencyCounter.h" 
#include "CSVWriter.h"      

int main(int argc, char* argv[]) {
    // Проверка количества аргументов командной строки
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.csv>\n";
        return 1; 
    }

    // Блок try-catch для обработки исключений
    try {
        FileReader reader;      
        WordTokenizer tokenizer; 
        FrequencyCounter counter; 
        CSVWriter writer;

        // Открываем файлы
        reader.open(argv[1]);
        writer.open(argv[2]);

        // Обрабатываем файл построчно
        while (!reader.isEof()) {
            std::string line = reader.next();
            if (!line.empty()) {
                // Токенизируем строку и добавляем слова в счетчик
                tokenizer.tokenizeStreaming(line, [&](const std::string& word) {
                    counter.addWord(word);
                });
            }
        }
        
        // Получаем статистику и записываем в CSV
        auto stats = counter.stats();
        writer.write(stats);
        
        // Закрываем файлы
        reader.close();
        writer.close();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;  // Возврат кода ошибки
    }

    return 0;
} 
