#ifndef FREQUENCYCOUNTER_H  // Защита от повторного включения
#define FREQUENCYCOUNTER_H

#include <string>  // Для std::string
#include <map>     // Для std::map
#include <list>    // Для std::list

class FrequencyCounter {
public:
    // Метод для подсчета частоты встречаемости слов
    std::map<std::string, int> count(const std::list<std::string>& words);
};

#endif // FREQUENCYCOUNTER_H 
