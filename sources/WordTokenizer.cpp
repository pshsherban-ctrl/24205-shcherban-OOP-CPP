#include "WordTokenizer.h"  // Подключение собственного заголовочного файла
#include <cctype>           // Для функций isalnum и tolower

void WordTokenizer::tokenizeStreaming(const std::string& line, 
                                     std::function<void(const std::string&)> processWord) {
    std::string word;  // Буфер для одного слова
    
    // Обрабатываем каждый символ строки
    for (char c : line) {
        // Если символ буква или цифра - добавляем к текущему слову
        if (std::isalnum(static_cast<unsigned char>(c))) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        } else if (!word.empty()) {
            // Если встретили разделитель и слово не пустое - обрабатываем слово
            processWord(word);  // Отправляем слово на обработку
            word.clear();       // Очищаем буфер для следующего слова
        }
    }
    
    // Обрабатываем последнее слово в строке (если есть)
    if (!word.empty()) {
        processWord(word);
    }
}