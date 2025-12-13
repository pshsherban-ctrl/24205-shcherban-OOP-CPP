#include <iostream>         // Для std::cout, std::cerr
#include <iomanip>  
#include <sstream>
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
        
        // Получаем статистику
        auto stats = counter.stats();
        int totalWords = counter.totalWords();
        
        // Записываем заголовок
        writer.writeRow({"Word", "Frequency", "Frequency (%)"});
        
        // Сортируем статистику по убыванию частоты
        std::sort(stats.begin(), stats.end(), 
                 [](const auto& a, const auto& b) {
                     return a.second > b.second;
                 });
        
        // Записываем данные
        for (const auto& [word, frequency] : stats) {
            // Вычисляем процентную частоту
            double percentage = (static_cast<double>(frequency) / totalWords) * 100.0;
            
            // Форматируем проценты с 6 знаками после запятой
            std::ostringstream percentageStream;
            percentageStream << std::fixed << std::setprecision(6) << percentage;
            
            // Создаем вектор колонок и записываем строку
            std::vector<std::string> columns = {
                word,
                std::to_string(frequency),
                percentageStream.str()
            };
            
            writer.writeRow(columns);
        }
        
        
        // Закрываем файлы
        reader.close();
        writer.close();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;  // Возврат кода ошибки
    }

    return 0;
} 
