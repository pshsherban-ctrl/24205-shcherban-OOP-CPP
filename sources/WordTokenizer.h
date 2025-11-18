#ifndef WORDTOKENIZER_H  // Защита от повторного включения
#define WORDTOKENIZER_H

#include <string>  // Для std::string
#include <list>    // Для std::list
#include <functional>  // Добавлено для std::function

class WordTokenizer {
public:
    // Метод для потоковой обработки строки с callback для каждого слова
    void tokenizeStreaming(const std::string& line, std::function<void(const std::string&)> processWord);
};

#endif // WORDTOKENIZER_H 
