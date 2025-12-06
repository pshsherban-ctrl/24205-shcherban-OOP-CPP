#include "game_controller.hpp"
#include "universe_file_handler.hpp"
#include "universe_renderer.hpp"
#include "preset_universes.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>

// Основной игровой цикл
void GameController::run() {
    running = true;  // Устанавливаем флаг работы
    
    // Показываем приветственное сообщение
    UniverseRenderer::show_welcome_message();
    
    // Отображаем информацию о вселенной
    UniverseRenderer::render_info(universe);
    
    // Отрисовываем поле с границами
    UniverseRenderer::render_with_border(universe);
    
    std::string command;  // Переменная для хранения введенной команды
    
    // Основной цикл обработки команд
    while (running) {
        std::cout << "\nCommand> ";       // Приглашение для ввода команды
        std::getline(std::cin, command);  // Чтение команды из консоли
        
        // Проверка на конец файла (Ctrl+D в Linux/Mac, Ctrl+Z в Windows)
        if (std::cin.eof()) {
            std::cout << "\nExiting...\n";
            break;
        }
        
        // Пропускаем пустые команды
        if (command.empty()) {
            continue;
        }
        
        // Обрабатываем команду
        process_command(command);
    }
}

// Обработка введенной команды
void GameController::process_command(const std::string& command) {
    // Разбиваем команду на токены (слова)
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    // Если нет токенов, выходим
    if (tokens.empty()) {
        return;
    }
    
    // Приводим первую команду к нижнему регистру для удобства сравнения
    std::string cmd = tokens[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    
    // Обработка различных команд
    if (cmd == "help") {
        // Команда помощи - выводим список доступных команд
        show_help();
    } else if (cmd == "tick" || cmd == "t") {
        // Команда tick/t - выполнить итерации
        execute_tick_command(tokens);
    } else if (cmd == "dump") {
        // Команда dump - сохранить вселенную в файл
        execute_dump_command(tokens);
    } else if (cmd == "exit" || cmd == "quit") {
        // Команда выхода - завершаем программу
        running = false;
        std::cout << "Goodbye!\n";
    } else if (cmd == "clear") {
        // Команда clear - очистить экран и перерисовать поле
        UniverseRenderer::clear_screen();
        UniverseRenderer::render_info(universe);
        UniverseRenderer::render_with_border(universe);
    } else if (cmd == "load") {
        // Команда load - загрузить вселенную из файла
        if (tokens.size() < 2) {
            std::cout << "Usage: load <filename>\n";
        } else {
            try {
                load_universe_from_file(tokens[1]);  // Загружаем вселенную
                // Перерисовываем экран
                UniverseRenderer::clear_screen();
                UniverseRenderer::render_info(universe);
                UniverseRenderer::render_with_border(universe);
            } catch (const std::exception& e) {
                // Обработка ошибки загрузки
                std::cerr << "Error loading file: " << e.what() << "\n";
            }
        }
    } else if (cmd == "preset") {
        // Команда preset - выбор из предустановленных вселенных
        PresetUniverses::show_preset_menu();  // Показываем меню пресетов
        std::cout << "Enter preset number: ";
        
        int choice;
        if (std::cin >> choice) {
            // Читаем выбор пользователя
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            // Получаем список доступных пресетов
            auto presets = PresetUniverses::get_available_presets();
            if (choice >= 1 && choice <= static_cast<int>(presets.size())) {
                // Создаем выбранную вселенную
                universe = PresetUniverses::create(presets[choice - 1].second);
                // Перерисовываем экран
                UniverseRenderer::clear_screen();
                UniverseRenderer::render_info(universe);
                UniverseRenderer::render_with_border(universe);
            } else {
                std::cout << "Invalid preset number.\n";
            }
        } else {
            // Очищаем флаги ошибок cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
        }
    } else {
        // Неизвестная команда
        std::cout << "Unknown command. Type 'help' for available commands.\n";
    }
}

// Обработка команды tick
void GameController::execute_tick_command(const std::vector<std::string>& tokens) {
    int n = 1;  // Количество итераций по умолчанию
    
    // Если указано количество итераций
    if (tokens.size() > 1) {
        try {
            n = std::stoi(tokens[1]);  // Парсим число итераций
            
            // Проверяем, что число положительное
            if (n <= 0) {
                std::cout << "Number of iterations must be positive.\n";
                return;
            }
        } catch (const std::exception&) {
            // Ошибка преобразования строки в число
            std::cout << "Invalid number of iterations.\n";
            return;
        }
    }
    
    // Выполняем итерации
    universe.tick(n);
    
    // Перерисовываем экран
    UniverseRenderer::clear_screen();
    UniverseRenderer::render_info(universe);
    UniverseRenderer::render_with_border(universe);
} 

// Конструктор по умолчанию
GameController::GameController() 
    : universe(40, 20, Rule::default_rule(), "Glider Demo"), running(false) {
    
    // Инициализируем глайдер
    std::vector<std::pair<int, int>> glider = {
        {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}
    };
    universe.load_from_coordinates(glider);
}

// Конструктор с загрузкой из файла
GameController::GameController(const std::string& filename) 
    : universe(1, 1, Rule::default_rule(), "Loaded Universe"), running(false) {
    load_universe_from_file(filename);
}

// Обработка команды dump
void GameController::execute_dump_command(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        std::cout << "Usage: dump <filename>\n";
    } else {
        try {
            save_universe_to_file(tokens[1]);
        } catch (const std::exception& e) {
            std::cerr << "Error saving file: " << e.what() << "\n";
        }
    }
}

// Вывод справки
void GameController::show_help() const {
    std::cout << "\nAvailable commands:\n";
    std::cout << "  help                 - Show this help message\n";
    std::cout << "  tick [n] (or t [n])  - Advance n iterations (default: 1)\n";
    std::cout << "  dump <filename>      - Save current universe to file\n";
    std::cout << "  load <filename>      - Load universe from file\n";
    std::cout << "  preset               - Choose from preset universes\n";
    std::cout << "  clear                - Clear screen and redraw\n";
    std::cout << "  exit (or quit)       - Exit the program\n";
}

// Загрузка вселенной из файла
void GameController::load_universe_from_file(const std::string& filename) {
    universe = UniverseFileHandler::load_from_file(filename);
}

// Сохранение вселенной в файл
void GameController::save_universe_to_file(const std::string& filename) const {
    UniverseFileHandler::save_to_file(universe, filename);
}

// Запускает оффлайн режим обработки (без интерактивного взаимодействия)
// Загружает вселенную из файла, выполняет заданное количество итераций и сохраняет результат
void GameController::run_offline(const std::string& input_file,
                                 const std::string& output_file,
                                 int iterations) {
    try {
        // Загружаем вселенную из входного файла
        load_universe_from_file(input_file);
        
        std::cout << "Processing " << iterations << " iterations...\n";
        std::cout << "Initial generation: " << universe.get_generation() << "\n";
        
        // Выполняем указанное количество итераций
        universe.tick(iterations);
        
        // Сохраняем результат в выходной файл
        save_universe_to_file(output_file);
        
        std::cout << "Done! Universe saved to: " << output_file << "\n";
        std::cout << "Final generation: " << universe.get_generation() << "\n";
    } catch (const std::exception& e) {
        // Обработка возможных исключений при загрузке/сохранении
        std::cerr << "Error: " << e.what() << "\n";
    }
}