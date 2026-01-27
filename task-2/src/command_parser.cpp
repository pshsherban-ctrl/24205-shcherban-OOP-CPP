#include "command_parser.hpp"
#include "commands/tick_command.hpp"
#include "commands/dump_command.hpp"
#include "commands/exit_command.hpp"
#include "commands/help_command.hpp"
#include "commands/clear_command.hpp"
#include "commands/load_command.hpp"
#include "commands/preset_command.hpp"
#include <sstream>
#include <algorithm>

// Конструктор инициализирует все команды
CommandParser::CommandParser() {
    initialize_commands();
    initialize_aliases();
}

// Инициализация всех доступных команд
void CommandParser::initialize_commands() {
    // Создаем и регистрируем все команды
    commands["tick"] = std::make_unique<TickCommand>();
    commands["dump"] = std::make_unique<DumpCommand>();
    commands["exit"] = std::make_unique<ExitCommand>();
    
    // HelpCommand требует ссылку на карту команд
    commands["help"] = std::make_unique<HelpCommand>(commands);
    
    commands["clear"] = std::make_unique<ClearCommand>();
    commands["load"] = std::make_unique<LoadCommand>();
    commands["preset"] = std::make_unique<PresetCommand>();
}

// Инициализация алиасов команд
void CommandParser::initialize_aliases() {
    register_alias("t", "tick");       // t → tick
    register_alias("q", "exit");       // q → exit
    register_alias("quit", "exit");    // quit → exit
    register_alias("?", "help");       // ? → help
    register_alias("cls", "clear");    // cls → clear
    register_alias("c", "clear");      // c → clear
}

// Разбор строки ввода и создание команды
CommandPtr CommandParser::parse(const std::string& input_line) {
    auto tokens = tokenize(input_line);
    if (tokens.empty()) {
        return nullptr;  // Пустая строка
    }
    
    std::string command_name = tokens[0];
    std::transform(command_name.begin(), command_name.end(), 
                   command_name.begin(), ::tolower);
    
    // Разрешаем алиасы
    command_name = resolve_command_name(command_name);
    
    // Ищем команду
    auto it = commands.find(command_name);
    if (it == commands.end()) {
        return nullptr;  // Команда не найдена
    }
    return std::move(it->second);  // Перемещаем владение
}

// Разделение строки на токены
std::vector<std::string> CommandParser::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// Разрешение имени команды с учетом алиасов
std::string CommandParser::resolve_command_name(const std::string& input_name) {
    auto it = aliases.find(input_name);
    if (it != aliases.end()) {
        return it->second;  // Возвращаем реальное имя команды
    }
    return input_name;  // Не алиас, возвращаем как есть
}

// Регистрация алиаса
void CommandParser::register_alias(const std::string& alias, 
                                   const std::string& command_name) {
    aliases[alias] = command_name;
}

// Получение всех команд
const std::map<std::string, CommandPtr>& CommandParser::get_all_commands() const {
    return commands;
}