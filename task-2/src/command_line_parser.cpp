#include "command_line_parser.hpp"
#include <iostream>
#include <algorithm>

// Парсинг аргументов командной строки
CommandLineParser::Options CommandLineParser::parse(int argc, char* argv[]) {
    Options options;  // Структура для хранения распарсенных опций
    
    // Проходим по всем аргументам командной строки, начиная с 1 (0 - имя программы)
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];  // Текущий аргумент
        
        // Проверка на опцию помощи
        if (arg == "-h" || arg == "--help") {
            options.help_requested = true;
            return options;  // Возвращаем сразу, так как help имеет высший приоритет
        }
        // Проверка на опцию количества итераций
        else if (arg == "-i" || arg.substr(0, 11) == "--iterations") {
            options.offline_mode = true;  // Включаем оффлайн режим
            
            std::string value;  // Значение опции
            if (arg.find('=') != std::string::npos) {
                // Опция в формате --iterations=N
                auto parts = split_option(arg);
                value = parts.second;  // Извлекаем значение после '='
            } else if (i + 1 < argc) {
                // Опция в формате -i N (отдельное значение)
                value = argv[++i];  // Берем следующий аргумент как значение
            } else {
                // Нет значения для опции
                options.error = true;
                options.error_message = "Missing value for iterations option";
                return options;
            }
            
            // Преобразуем строку в число
            try {
                options.iterations = std::stoi(value);
                if (options.iterations <= 0) {
                    options.error = true;
                    options.error_message = "Iterations must be positive";
                    return options;
                }
            } catch (const std::exception&) {
                // Ошибка преобразования
                options.error = true;
                options.error_message = "Invalid iterations value: " + value;
                return options;
            }
        }
        // Проверка на опцию выходного файла
        else if (arg == "-o" || arg.substr(0, 8) == "--output") {
            options.offline_mode = true;  // Включаем оффлайн режим
            
            if (arg.find('=') != std::string::npos) {
                // Опция в формате --output=filename
                auto parts = split_option(arg);
                options.output_file = parts.second;
            } else if (i + 1 < argc) {
                // Опция в формате -o filename
                options.output_file = argv[++i];
            } else {
                // Нет значения для опции
                options.error = true;
                options.error_message = "Missing value for output option";
                return options;
            }
        }
        else {
            // Если аргумент не является опцией, считаем его входным файлом
            if (options.input_file.empty()) {
                options.input_file = arg;  // Первый неопционный аргумент - входной файл
            } else {
                // Лишние аргументы - выводим предупреждение
                std::cerr << "Warning: Ignoring extra argument: " << arg << "\n";
            }
        }
    }
    
    // Дополнительные проверки для оффлайн режима
    if (options.offline_mode) {
        // В оффлайн режиме обязательны все три параметра
        if (options.input_file.empty()) {
            options.error = true;
            options.error_message = "Input file required for offline mode";
            return options;
        }
        if (options.output_file.empty()) {
            options.error = true;
            options.error_message = "Output file required for offline mode";
            return options;
        }
        if (options.iterations <= 0) {
            options.error = true;
            options.error_message = "Iterations required for offline mode";
            return options;
        }
    }
    
    return options;  // Возвращаем распарсенные опции
} 

// Разделяет опцию формата "--ключ=значение" на пару (ключ, значение)
std::pair<std::string, std::string> CommandLineParser::split_option(const std::string& option) {
    size_t eq_pos = option.find('=');
    if (eq_pos == std::string::npos) {
        return {option, ""};  // Если нет '=', возвращаем всю строку как ключ
    }
    
    std::string key = option.substr(0, eq_pos);
    std::string value = option.substr(eq_pos + 1);
    
    // Убираем двойные кавычки вокруг значения, если они есть
    if (!value.empty() && value.front() == '"' && value.back() == '"') {
        value = value.substr(1, value.length() - 2);
    }
    
    return {key, value};
}

// Выводит справку по использованию программы
void CommandLineParser::show_usage(const std::string& program_name) {
    std::cout << "Conway's Game of Life Simulator\n\n";
    std::cout << "Usage:\n";
    std::cout << "  " << program_name << " [options] [input_file]\n\n";
    std::cout << "Modes:\n";
    std::cout << "  1. Interactive with file: " << program_name << " universe.life\n";
    std::cout << "  2. Interactive (no file): " << program_name << "\n";
    std::cout << "  3. Offline processing: " << program_name << " -i N -o output.life input.life\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help                 Show this help message\n";
    std::cout << "  -i, --iterations=N         Number of iterations (offline mode)\n";
    std::cout << "  -o, --output=FILE          Output file (offline mode)\n\n";
    std::cout << "Interactive commands:\n";
    std::cout << "  help                       Show available commands\n";
    std::cout << "  tick [N]                   Advance N generations\n";
    std::cout << "  dump FILENAME              Save universe to file\n";
    std::cout << "  load FILENAME              Load universe from file\n";
    std::cout << "  preset                     Choose from preset universes\n";
    std::cout << "  exit                       Exit the program\n";
}