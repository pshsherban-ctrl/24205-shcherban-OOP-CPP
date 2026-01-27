#ifndef HELP_COMMAND_HPP
#define HELP_COMMAND_HPP

#include "command.hpp"
#include <string>
#include <vector>
#include <map>
#include <memory>

// Команда вывода справки
class HelpCommand : public Command {
public:
    // Конструктор принимает карту всех доступных команд
    explicit HelpCommand(const std::map<std::string, CommandPtr>& commands);
    
    void execute(GameController& controller, 
                const std::vector<std::string>& args) override;
    
    std::string get_description() const override {
        return "Show this help message";
    }
    
    std::string get_syntax() const override {
        return "help";
    }
    
    std::string get_name() const override {
        return "help";
    }
    
private:
    const std::map<std::string, CommandPtr>& commands;
    
    // Вывод подробной справки по конкретной команде
    void show_command_help(const std::string& command_name);
};

#endif 