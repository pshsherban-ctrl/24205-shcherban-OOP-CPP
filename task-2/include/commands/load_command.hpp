#ifndef LOAD_COMMAND_HPP
#define LOAD_COMMAND_HPP

#include "command.hpp"
#include <string>
#include <vector>

// Команда загрузки вселенной из файла
class LoadCommand : public Command {
public:
    void execute(GameController& controller, 
                const std::vector<std::string>& args) override;
    
    std::string get_description() const override {
        return "Load universe from file";
    }
    
    std::string get_syntax() const override {
        return "load <filename>";
    }
    
    std::string get_name() const override {
        return "load";
    }
    
private:
    bool validate_args(const std::vector<std::string>& args, std::string& filename);
};

#endif 