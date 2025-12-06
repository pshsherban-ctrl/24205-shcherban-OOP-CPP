#ifndef FREQUENCYCOUNTER_H  // Защита от повторного включения
#define FREQUENCYCOUNTER_H

#include <string>  // Для std::string
#include <map>     // Для std::map
#include <vector>
#include <utility>  // для std::pair

class FrequencyCounter {
private:
    std::map<std::string, int> wordCounts;  // map для подсчета слов
    int totalWordCount;  // Общее количество слов

public:
    FrequencyCounter() : totalWordCount(0) {}
    
    // Добавляет слово в статистику
    void addWord(const std::string& word);
    
    // Возвращает статистику в виде вектора пар (слово, частота)
    std::vector<std::pair<std::string, int>> stats() const;
    
    // Возвращает общее количество обработанных слов
    int totalWords() const;
};

#endif
