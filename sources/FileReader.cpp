#include "FileReader.h"    // Подключение собственного заголовочного файла
#include <fstream>         // Для работы с файловыми потоками
#include <stdexcept>       // Для исключений std::runtime_error

// Реализация метода чтения строк из файла
std::list<std::string> FileReader::readLines(const std::string& filename) {
    std::list<std::string> lines;  // Создание списка для хранения строк
    std::ifstream file(filename);  // Открытие файла для чтения
    
    // Проверка успешности открытия файла
    if (!file.is_open()) {
        // Выброс исключения если файл не открылся
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string line;  // Временная переменная для хранения текущей строки
    
    // Чтение файла построчно до конца
    while (std::getline(file, line)) {
        lines.push_back(line);  // Добавление строки в список
    }
    
    return lines;  // Возврат списка всех строк
} 
