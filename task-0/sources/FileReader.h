#ifndef FILEREADER_H  // Защита от повторного включения заголовочного файла
#define FILEREADER_H

#include <string>    
#include <fstream>

class FileReader {
private:
    std::ifstream file;  // Файловый поток для чтения

public:
    // Открывает файл для чтения
    void open(const std::string& filename);
    
    // Читает следующую строку из файла
    std::string next();
    
    // Проверяет, достигнут ли конец файла
    bool isEof() const;
    
    // Закрывает файл
    void close();
};

#endif 