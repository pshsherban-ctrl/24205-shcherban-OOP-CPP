#include "commands/clear_command.hpp"
#include "game_controller.hpp"

void ClearCommand::execute(GameController& controller, 
                          const std::vector<std::string>& args) {
    controller.redraw();  // Очищает экран и перерисовывает вселенную
}