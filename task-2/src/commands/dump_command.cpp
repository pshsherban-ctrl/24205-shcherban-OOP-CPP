#include "commands/dump_command.hpp"
#include "game_controller.hpp"
#include <iostream>

void DumpCommand::execute(GameController& controller, 
                         const std::vector<std::string>& args) {
    std::string filename;
    
    if (!validate_args(args, filename)) {
        return;
    }
    
    try {
        controller.save_universe_to_file(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error saving file: " << e.what() << "\n";
    }
}

bool DumpCommand::validate_args(const std::vector<std::string>& args, std::string& filename) {
    if (args.size() < 2) {
        std::cout << "Usage: dump <filename>\n";
        return false;
    }
    filename = args[1];
    return true;
}