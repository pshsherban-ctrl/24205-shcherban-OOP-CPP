#include "FrequencyCounter.h"  // Подключение собственного заголовочного файла

// Реализация метода подсчета частоты слов
std::map<std::string, int> FrequencyCounter::count(const std::list<std::string>& words) {
    std::map<std::string, int> freqMap;  // Создание словаря для подсчета частот
    
    // Цикл по всем словам из списка
    for (const auto& word : words) {
        freqMap[word]++;  // Увеличение счетчика для текущего слова
        // Если слова нет в map, он автоматически создается со значением 0, затем инкрементируется
    }
    
    return freqMap;  // Возврат словаря с частотами
} 
