#include "FileReader.h"    // Подключение собственного заголовочного файла
#include <fstream>         // Для работы с файловыми потоками
#include <stdexcept>       // Для исключений std::runtime_error

// Реализация метода чтения строк из файла
void FileReader::readLinesStreaming(const std::string& filename, std::function<void(const std::string&)> processLine) {
    std::ifstream file(filename);  // Открытие файла для чтения
    
    // Проверка успешности открытия файла
    if (!file.is_open()) {
        // Выброс исключения если файл не открылся
        throw std::runtime_error("Cannot open input.txt");
    }
    
    std::string line;  // Буфер для одной строки
    
    // Чтение файла построчно, не сохраняя все сроки в памяти
    while (std::getline(file, line)) {
       processLine(line);  // обработка каждой строки стразу
    }
} 
