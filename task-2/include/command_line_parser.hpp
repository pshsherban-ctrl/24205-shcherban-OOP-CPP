#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <string>

// Класс для парсинга аргументов командной строки
// Обрабатывает флаги и параметры, переданные при запуске программы
class CommandLineParser {
public:
    // Структура для хранения распарсенных опций командной строки
    struct Options {
        std::string input_file;     // Путь к входному файлу (если указан)
        std::string output_file;    // Путь к выходному файлу (для оффлайн режима)
        int iterations = 0;         // Количество итераций (для оффлайн режима)
        bool offline_mode = false;  // Флаг оффлайн режима обработки
        bool help_requested = false;// Флаг запроса справки
        bool error = false;         // Флаг ошибки парсинга
        std::string error_message;  // Сообщение об ошибке (если error == true)
    };
    
    // Парсит аргументы командной строки
    static Options parse(int argc, char* argv[]);
    
    // Выводит справку по использованию программы
    static void show_usage(const std::string& program_name);
    
private:
    // Вспомогательный метод для разделения опции формата "--ключ=значение"
    static std::pair<std::string, std::string> split_option(const std::string& option);
};

#endif