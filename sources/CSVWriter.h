#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <string>
#include <vector>
#include <fstream>

class CSVWriter {
private:
    std::ofstream file;  // Файловый поток для записи

public:
    // Открывает файл для записи
    void open(const std::string& filename);
    
    // Записывает вектор строк как строку CSV (колонки через запятую)
    void writeRow(const std::vector<std::string>& columns);
    
    // Закрывает файл
    void close();
};

#endif
