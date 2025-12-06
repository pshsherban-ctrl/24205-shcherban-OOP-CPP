#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <string>
#include "universe.hpp"

class GameController {
private:
    Universe universe;
    bool running;
    
    void process_command(const std::string& command);
    void show_help() const;
    void execute_tick_command(const std::vector<std::string>& tokens);
    void execute_dump_command(const std::vector<std::string>& tokens);
    
public:
    GameController();
    explicit GameController(const std::string& filename);
    
    void run();
    void run_offline(const std::string& input_file, 
                     const std::string& output_file, 
                     int iterations);
    
    void load_universe_from_file(const std::string& filename);
    void save_universe_to_file(const std::string& filename) const;
};

#endif  
