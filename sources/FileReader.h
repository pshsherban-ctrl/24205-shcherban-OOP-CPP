#ifndef FILEREADER_H  // Защита от повторного включения заголовочного файла
#define FILEREADER_H

#include <string>    // Для использования std::string
#include <list>      // Для использования std::list

class FileReader {
public:
    // Метод для чтения всех строк из файла
    std::list<std::string> readLines(const std::string& filename);
};

#endif // FILEREADER_H 
