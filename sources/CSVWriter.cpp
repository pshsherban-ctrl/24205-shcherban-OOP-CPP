#include "CSVWriter.h"
#include <stdexcept>

void CSVWriter::open(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
}

void CSVWriter::writeRow(const std::vector<std::string>& columns) {
    if (!file.is_open()) {
        throw std::runtime_error("File is not open for writing");
    }
    
    for (size_t i = 0; i < columns.size(); ++i) {
        file << columns[i];
        if (i < columns.size() - 1) {
            file << ",";  // Разделитель между колонками
        }
    }
    file << "\n";  // Конец строки
}

void CSVWriter::close() {
    if (file.is_open()) {
        file.close();
    }
}
