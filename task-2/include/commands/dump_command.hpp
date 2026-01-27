#ifndef DUMP_COMMAND_HPP
#define DUMP_COMMAND_HPP

#include "command.hpp"
#include <string>
#include <vector>

// Команда сохранения вселенной в файл
class DumpCommand : public Command {
public:
    void execute(GameController& controller, 
                const std::vector<std::string>& args) override;
    
    std::string get_description() const override {
        return "Save current universe to a file";
    }
    
    std::string get_syntax() const override {
        return "dump <filename>";
    }
    
    std::string get_name() const override {
        return "dump";
    }
    
private:
    bool validate_args(const std::vector<std::string>& args, std::string& filename);
};

#endif