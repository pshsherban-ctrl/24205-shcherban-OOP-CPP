#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <string>
#include "universe.hpp"

// Главный класс, управляющий игровым процессом
// Координирует взаимодействие между пользователем, вселенной и отрисовкой
class GameController {
private:
    Universe universe;  // Текущая игровая вселенная
    bool running;       // Флаг работы программы (true - работает, false - завершение)
    
    // Обрабатывает введенную пользователем команду
    void process_command(const std::string& command);
    
    // Выводит справку по доступным командам
    void show_help() const;
    
    // Обрабатывает команду tick/t
    void execute_tick_command(const std::vector<std::string>& tokens);
    
    // Обрабатывает команду dump
    void execute_dump_command(const std::vector<std::string>& tokens);
    
public:
    // Конструктор по умолчанию (создает вселенную с глайдером)
    GameController();
    
    // Конструктор с загрузкой вселенной из файла
    explicit GameController(const std::string& filename);
    
    // Запускает интерактивный режим игры
    void run();
    
    // Запускает оффлайн обработку (без интерактивного взаимодействия)
    void run_offline(const std::string& input_file, 
                     const std::string& output_file, 
                     int iterations);
    
    // Загружает вселенную из файла
    void load_universe_from_file(const std::string& filename);
    
    // Сохраняет вселенную в файл
    void save_universe_to_file(const std::string& filename) const;
};

#endif 