#ifndef CSVWRITER_H 
#define CSVWRITER_H

#include <string>  // Для std::string
#include <vector>
#include <utility>  // для std::pair
#include <fstream>

class CSVWriter {
private:
    std::ofstream file;  // Файловый поток для записи

public:
    // Открывает файл для записи
    void open(const std::string& filename);
    
    // Записывает статистику в CSV формате
    void write(const std::vector<std::pair<std::string, int>>& stats);
    
    // Закрывает файл
    void close();
};

#endif
