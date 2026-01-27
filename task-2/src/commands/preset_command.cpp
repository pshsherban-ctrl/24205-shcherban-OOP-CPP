#include "commands/preset_command.hpp"
#include "game_controller.hpp"
#include "preset_universes.hpp"
#include <iostream>
#include <limits>

void PresetCommand::execute(GameController& controller, 
                           const std::vector<std::string>& args) {
    PresetUniverses::show_preset_menu();
    std::cout << "Enter preset number: ";
    
    int choice;
    if (std::cin >> choice) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        auto presets = PresetUniverses::get_available_presets();
        if (choice >= 1 && choice <= static_cast<int>(presets.size())) {
            auto universe = PresetUniverses::create(presets[choice - 1].second);
            controller.set_universe(std::move(universe));
            controller.redraw();
        } else {
            std::cout << "Invalid preset number.\n";
        }
    } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
    }
}