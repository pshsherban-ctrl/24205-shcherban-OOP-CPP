#ifndef UNIVERSE_FILE_HANDLER_HPP
#define UNIVERSE_FILE_HANDLER_HPP

#include <string>
#include <fstream>
#include "universe.hpp"

class UniverseFileHandler {
public:
    static Universe load_from_file(const std::string& filename);
    static void save_to_file(const Universe& universe, const std::string& filename);
    
private:
    static void parse_life_106(std::ifstream& file, Universe& universe, 
                               std::vector<std::pair<int, int>>& coordinates);
    static std::pair<int, int> parse_coordinate(const std::string& line);
    static std::pair<int, int> find_grid_size(const std::vector<std::pair<int, int>>& coordinates);
};

#endif 
