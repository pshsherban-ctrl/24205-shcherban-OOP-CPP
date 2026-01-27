#ifndef CLEAR_COMMAND_HPP
#define CLEAR_COMMAND_HPP

#include "command.hpp"
#include <string>
#include <vector>

// Команда очистки экрана
class ClearCommand : public Command {
public:
    void execute(GameController& controller, 
                const std::vector<std::string>& args) override;
    
    std::string get_description() const override {
        return "Clear screen and redraw universe";
    }
    
    std::string get_syntax() const override {
        return "clear";
    }
    
    std::string get_name() const override {
        return "clear";
    }
};

#endif 