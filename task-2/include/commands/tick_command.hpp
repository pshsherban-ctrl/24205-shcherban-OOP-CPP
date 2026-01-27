#ifndef TICK_COMMAND_HPP
#define TICK_COMMAND_HPP

#include "command.hpp"
#include <string>
#include <vector>

// Команда выполнения итераций игры
// Наследует базовый класс Command и реализует паттерн "Команда"
class TickCommand : public Command {
public:
    // Реализация абстрактных методов базового класса
    void execute(GameController& controller, 
                const std::vector<std::string>& args) override;
    
    std::string get_description() const override {
        return "Advance the simulation by N generations";
    }
    
    std::string get_syntax() const override {
        return "tick [N]  or  t [N]";
    }
    
    std::string get_name() const override {
        return "tick";
    }
    
private:
    // Валидация аргументов команды
    bool validate_args(const std::vector<std::string>& args, int& iterations);
};

#endif