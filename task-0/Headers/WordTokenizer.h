#ifndef WORDTOKENIZER_H  // Защита от повторного включения
#define WORDTOKENIZER_H

#include <string>  // Для std::string
#include <list>    // Для std::list

class WordTokenizer {
public:
    // Метод для разбиения строк на отдельные слова
    std::list<std::string> tokenize(const std::list<std::string>& lines);
};

#endif // WORDTOKENIZER_H 
