#include "CSVWriter.h"       // Подключение собственного заголовочного файла
#include <algorithm>         // Для std::sort
#include <stdexcept>         // Для std::runtime_error

// Вспомогательная функция для сравнения пар (слово-частота) по убыванию частоты, сортирует статистику от самых частых слов к самым редким
bool compareByFrequency(const std::pair<std::string, int>& a, 
                       const std::pair<std::string, int>& b) {
    return a.second > b.second;  // Сравниваем по второму элементу (частоте) в порядке убывания
}

// Реализация метода открытия файла для записи
void CSVWriter::open(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
}

// Реализация метода записи статистики в CSV файл
void CSVWriter::write(const std::vector<std::pair<std::string, int>>& stats) {
    if (!file.is_open()) {
        throw std::runtime_error("File is not open for writing");
    }
    
    // Создаем копию переданной статистики для сортировки, не изменяем оригинальные данные
    std::vector<std::pair<std::string, int>> sortedStats = stats;
    
    // Сортируем статистику по убыванию частоты с использованием вспомогательной функции
    std::sort(sortedStats.begin(), sortedStats.end(), compareByFrequency);
    
    // Подсчитываем общее количество слов для вычисления процентных частот
    int totalWords = 0;
    for (const auto& pair : sortedStats) {
        totalWords += pair.second;  // Суммируем все частоты
    }
    
    // Записываем заголовок CSV файла
    file << "Word,Frequency,Frequency (%)\n";
    
    // Записываем данные для каждого слова
    for (const auto& pair : sortedStats) {
        // (частота слова / общее количество слов) * 100%
        double percentage = (static_cast<double>(pair.second) / totalWords) * 100.0;
        
        // Записываем строку в CSV формате: слово, абсолютная частота, процентная частота
        file << pair.first << "," << pair.second << "," << percentage << "\n";
    }
}

// Реализация метода закрытия файла
void CSVWriter::close() {
    if (file.is_open()) {
        file.close(); 
    }
}