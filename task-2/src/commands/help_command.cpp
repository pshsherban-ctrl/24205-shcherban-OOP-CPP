#include "commands/help_command.hpp"
#include "../game_controller.hpp"
#include <iostream>
#include <iomanip>

// Конструктор инициализирует ссылку на карту команд
HelpCommand::HelpCommand(const std::map<std::string, CommandPtr>& commands_ref)
    : commands(commands_ref) {}

void HelpCommand::execute(GameController& controller, 
                         const std::vector<std::string>& args) {
    if (args.size() > 1) {
        // Показать справку по конкретной команде
        show_command_help(args[1]);
    } else {
        // Показать общую справку
        std::cout << "\nAvailable commands:\n";
        std::cout << std::string(50, '-') << "\n";
        
        for (const auto& [name, cmd] : commands) {
            std::cout << std::left << std::setw(15) << cmd->get_syntax()
                      << " - " << cmd->get_description() << "\n";
        }
        
        std::cout << "\nType 'help <command>' for detailed information.\n";
        std::cout << std::string(50, '-') << "\n";
    }
}

void HelpCommand::show_command_help(const std::string& command_name) {
    auto it = commands.find(command_name);
    if (it == commands.end()) {
        std::cout << "Unknown command: " << command_name << "\n";
        return;
    }
    
    const auto& cmd = it->second;
    std::cout << "\nCommand: " << cmd->get_name() << "\n";
    std::cout << "Syntax: " << cmd->get_syntax() << "\n";
    std::cout << "Description: " << cmd->get_description() << "\n\n";
}