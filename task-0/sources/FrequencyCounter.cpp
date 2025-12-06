#include "FrequencyCounter.h" 

// Реализация метода добавления слова в статистику
void FrequencyCounter::addWord(const std::string& word) {
    // Проверяем, что слово не пустое
    if (!word.empty()) {
        // Увеличиваем счетчик для данного слова
        // Если слова нет в map, он автоматически создается со значением 0, затем инкрементируется
        wordCounts[word]++;
        
        // Увеличиваем общий счетчик слов
        totalWordCount++;
    }
}

// Реализация метода получения статистики
std::vector<std::pair<std::string, int>> FrequencyCounter::stats() const {
    // Создаем вектор для хранения результатов
    std::vector<std::pair<std::string, int>> result;
    
    // Проходим по всем элементам map и копируем их в вектор
    for (const auto& pair : wordCounts) {
        result.push_back(pair);  // Добавляем пару (слово, частота) в вектор
    }
    
    // Возвращаем заполненный вектор
    return result;
}
// Реализация метода получения общего количества слов
int FrequencyCounter::totalWords() const {
    // Возвращаем значение счетчика общего количества слов
    return totalWordCount;
}