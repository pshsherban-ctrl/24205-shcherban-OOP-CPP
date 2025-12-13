#include "game_controller.hpp"
#include "command_line_parser.hpp"
#include <iostream>

// Главная функция программы - точка входа
int main(int argc, char* argv[]) {
    // Парсим аргументы командной строки
    auto options = CommandLineParser::parse(argc, argv);
    
    // Если была ошибка парсинга, выводим сообщение и завершаем программу
    if (options.error) {
        std::cerr << "Error: " << options.error_message << "\n\n";
        CommandLineParser::show_usage(argv[0]);  // Показываем справку по использованию
        return 1;  // Возвращаем код ошибки
    }
    
    // Если запрошена справка, выводим её и завершаем программу
    if (options.help_requested) {
        CommandLineParser::show_usage(argv[0]);
        return 0;  // Успешное завершение
    }
    
    // Основной блок выполнения программы
    try {
        if (options.offline_mode) {
            // Режим 3: оффлайн обработка
            // Создаем контроллер
            GameController controller;
            // Выполняем обработку в оффлайн режиме
            controller.run_offline(options.input_file, 
                                 options.output_file, 
                                 options.iterations);
        } else {
            // Интерактивные режимы
            if (!options.input_file.empty()) {
                // Режим 1: интерактивный с загрузкой из файла
                GameController controller(options.input_file);
                controller.run();
            } else {
                // Режим 2: интерактивный с предустановленной вселенной
                GameController controller;
                controller.run();
            }
        }
    } catch (const std::exception& e) {
        // Обработка исключений: выводим сообщение об ошибке и завершаем программу
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;  // Возвращаем код ошибки
    }
    
    return 0; 
}