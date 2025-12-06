#ifndef CSVWRITER_H  // Защита от повторного включения
#define CSVWRITER_H

#include <string>  // Для std::string
#include <map>     // Для std::map

class CSVWriter {
public:
    // Метод для записи результатов в CSV файл
    void write(const std::string& filename, const std::map<std::string, int>& freqMap);
};

#endif // CSVWRITER_H 
