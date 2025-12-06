#include "FileReader.h"    
#include <stdexcept>       // Для исключений std::runtime_error

// Реализация метода чтения строк из файла
void FileReader::open(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
}

std::string FileReader::next() {
    std::string line;
    if (std::getline(file, line)) {
        return line;
    }
    return "";  // Возвращаем пустую строку при EOF
}

bool FileReader::isEof() const {
    return file.eof();
}

void FileReader::close() {
    if (file.is_open()) {
        file.close();
    }
}