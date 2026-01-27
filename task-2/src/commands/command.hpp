#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <memory>
#include <vector>

class GameController;
class Universe;

class Command {
public:
    virtual ~Command() = default;

    // Принимает контроллер игры и аргументы команды
    virtual void execute(GameController& controller, 
                        const std::vector<std::string>& args) = 0;
    
    // Возвращает описание команды (для справки)
    virtual std::string get_description() const = 0;
    
    // Возвращает синтаксис команды (для справки)
    virtual std::string get_syntax() const = 0;
    
    // Возвращает имя команды
    virtual std::string get_name() const = 0;
};

using CommandPtr = std::unique_ptr<Command>;

#endif