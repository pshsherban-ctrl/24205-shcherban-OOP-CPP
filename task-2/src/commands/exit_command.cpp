#include "commands/exit_command.hpp"
#include "game_controller.hpp"
#include <iostream>

void ExitCommand::execute(GameController& controller, 
                         const std::vector<std::string>& args) {
    controller.stop();  // Устанавливает флаг running = false
    std::cout << "Goodbye!\n";
}