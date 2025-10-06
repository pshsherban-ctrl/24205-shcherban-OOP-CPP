#include "WordTokenizer.h"  // Подключение собственного заголовочного файла
#include <cctype>           // Для функций isalnum и tolower
#include <algorithm>        // Для std::transform (хотя в этой реализации не используется)

// Реализация метода разбиения строк на слова
std::list<std::string> WordTokenizer::tokenize(const std::list<std::string>& lines) {
    std::list<std::string> words;  // Создание списка для хранения слов
    
    // Цикл по всем строкам из входного списка
    for (const auto& line : lines) {
        std::string word;  // Временная переменная для накопления текущего слова
        
        // Цикл по каждому символу в строке
        for (char c : line) {
            // Проверка, является ли символ буквой или цифрой
            if (std::isalnum(static_cast<unsigned char>(c))) {
                // Добавление символа к текущему слову (в нижнем регистре)
                word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            } else if (!word.empty()) {
                // Если встретили разделитель и слово не пустое, сохраняем слово
                words.push_back(word);  // Добавление слова в список
                word.clear();           // Очистка временной переменной для следующего слова
            }
        }
        
        // Проверка на случай, если слово было в конце строки без разделителя
        if (!word.empty()) {
            words.push_back(word);  // Добавление последнего слова из строки
        }
    }
    
    return words;  // Возврат списка всех слов
} 
