#include "CSVWriter.h"       // Подключение собственного заголовочного файла
#include <fstream>           // Для работы с файловыми потоками
#include <vector>            // Для std::vector
#include <algorithm>         // Для std::sort
#include <stdexcept>         // Для std::runtime_error

// Вспомогательная функция для сравнения пар (слово-частота) по убыванию частоты
bool comparePairs(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;  // Сравнение по второму элементу (частоте) в порядке убывания
}

// Реализация метода записи в CSV файл
void CSVWriter::write(const std::string& filename, const std::map<std::string, int>& freqMap) {
    std::ofstream file(filename);  // Открытие файла для записи
    
    // Проверка успешности открытия файла
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    // Запись заголовка CSV файла
    file << "Word,Frequency,Frequency (%)\n";
    
    // Подсчет общего количества слов для вычисления процентов
    int totalWords = 0;
    for (const auto& pair : freqMap) {
        totalWords += pair.second;  // Суммирование всех частот
    }
    
    // Создание вектора из пар словаря для сортировки
    std::vector<std::pair<std::string, int>> sortedPairs(freqMap.begin(), freqMap.end());
    
    // Сортировка вектора по убыванию частоты с использованием вспомогательной функции
    std::sort(sortedPairs.begin(), sortedPairs.end(), comparePairs);
    
    // Цикл по отсортированным парам для записи в файл
    for (const auto& pair : sortedPairs) {
        // Вычисление процентной частоты
        double percentage = (static_cast<double>(pair.second) / totalWords) * 100.0;
        
        // Запись строки в CSV: слово, абсолютная частота, процентная частота
        file << pair.first << "," << pair.second << "," << percentage << "\n";
    }
} 
