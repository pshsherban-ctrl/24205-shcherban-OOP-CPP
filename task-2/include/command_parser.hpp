#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include "commands/command.hpp"
#include <string>
#include <vector>
#include <memory>
#include <map>

// Класс для разбора и создания команд из строки ввода
class CommandParser {
public:
    // Инициализация со всеми доступными командами
    CommandParser();
    
    // Разбор строки ввода и создание соответствующей команды
    // Возвращает указатель на команду или nullptr если команда не найдена
    CommandPtr parse(const std::string& input_line);
    
    // Получение списка всех доступных команд (для справки)
    const std::map<std::string, CommandPtr>& get_all_commands() const;
    
    // Регистрация алиасов команд (например, "t" для "tick")
    void register_alias(const std::string& alias, const std::string& command_name);
    
private:
    // Карта всех доступных команд (ключ - имя команды)
    std::map<std::string, CommandPtr> commands;
    
    // Карта алиасов (ключ - алиас, значение - имя команды)
    std::map<std::string, std::string> aliases;
    
    // Разделение строки на токены (команда и аргументы)
    std::vector<std::string> tokenize(const std::string& input);
    
    // Получение реального имени команды (с учетом алиасов)
    std::string resolve_command_name(const std::string& input_name);
    
    // Инициализация команд
    void initialize_commands();
};

#endif 