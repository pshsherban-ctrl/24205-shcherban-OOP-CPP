 
#ifndef UNIVERSE_RENDERER_HPP
#define UNIVERSE_RENDERER_HPP

#include <string>
#include "universe.hpp"

class UniverseRenderer {
public:
    static void render(const Universe& universe);
    static void render_with_border(const Universe& universe);
    static void render_info(const Universe& universe);
    static void clear_screen();
    static void show_welcome_message();
    
private:
    static const char LIVE_CELL = 'O';
    static const char DEAD_CELL = '.';
    static const char BORDER_VERTICAL = '|';
    static const char BORDER_HORIZONTAL = '-';
    static const char BORDER_CORNER = '+';
};

#endif 