#include "commands/tick_command.hpp"
#include "game_controller.hpp"
#include <iostream>
#include <stdexcept>

// Реализация паттерна "Команда": конкретная реализация выполнения команды tick
void TickCommand::execute(GameController& controller, 
                         const std::vector<std::string>& args) {
    int iterations = 1;
    
    if (!validate_args(args, iterations)) {
        return;  // Валидация уже вывела сообщение об ошибке
    }
    
    // Получаем вселенную из контроллера и выполняем итерации
    controller.get_universe().tick(iterations);
    
    // Перерисовываем экран через контроллер
    controller.redraw();
}

// Валидация аргументов команды tick
bool TickCommand::validate_args(const std::vector<std::string>& args, int& iterations) {
    if (args.size() > 1) {
        try {
            iterations = std::stoi(args[1]);
            if (iterations <= 0) {
                std::cout << "Number of iterations must be positive.\n";
                return false;
            }
        } catch (const std::exception&) {
            std::cout << "Invalid number of iterations.\n";
            return false;
        }
    }
    return true;
}