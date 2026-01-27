#ifndef PRESET_COMMAND_HPP
#define PRESET_COMMAND_HPP

#include "command.hpp"
#include <string>
#include <vector>

// Команда выбора предустановленной вселенной
class PresetCommand : public Command {
public:
    void execute(GameController& controller, 
                const std::vector<std::string>& args) override;
    
    std::string get_description() const override {
        return "Choose from preset universes";
    }
    
    std::string get_syntax() const override {
        return "preset";
    }
    
    std::string get_name() const override {
        return "preset";
    }
};

#endif 