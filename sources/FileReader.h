#ifndef FILEREADER_H  // Защита от повторного включения заголовочного файла
#define FILEREADER_H

#include <string>    // Для использования std::string
#include <list>      // Для использования std::list
#include <functional>  // Добавлено для std::function

class FileReader {
public:
    // Метод для потокового чтения файла с callback-функцией для каждой строки
    void readLinesStreaming(const std::string& filename, std::function<void(const std::string&)> processLine);
};

#endif // FILEREADER_H 
