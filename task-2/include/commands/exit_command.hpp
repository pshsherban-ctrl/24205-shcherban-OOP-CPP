#ifndef EXIT_COMMAND_HPP
#define EXIT_COMMAND_HPP

#include "command.hpp"
#include <string>
#include <vector>

// Команда выхода из программы
class ExitCommand : public Command {
public:
    void execute(GameController& controller, 
                const std::vector<std::string>& args) override;
    
    std::string get_description() const override {
        return "Exit the program";
    }
    
    std::string get_syntax() const override {
        return "exit  or  quit";
    }
    
    std::string get_name() const override {
        return "exit";
    }
};

#endif