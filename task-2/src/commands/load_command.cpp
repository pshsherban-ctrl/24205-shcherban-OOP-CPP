#include "commands/load_command.hpp"
#include "game_controller.hpp"
#include <iostream>

void LoadCommand::execute(GameController& controller, 
                         const std::vector<std::string>& args) {
    std::string filename;
    
    if (!validate_args(args, filename)) {
        return;
    }
    
    try {
        controller.load_universe_from_file(filename);
        controller.redraw();  // Перерисовываем после загрузки
    } catch (const std::exception& e) {
        std::cerr << "Error loading file: " << e.what() << "\n";
    }
}

bool LoadCommand::validate_args(const std::vector<std::string>& args, std::string& filename) {
    if (args.size() < 2) {
        std::cout << "Usage: load <filename>\n";
        return false;
    }
    filename = args[1];
    return true;
}