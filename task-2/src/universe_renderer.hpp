#ifndef UNIVERSE_RENDERER_HPP
#define UNIVERSE_RENDERER_HPP

#include <string>
#include "universe.hpp"

// Класс для отображения (рендеринга) игрового поля в консоли
// Отвечает за визуализацию вселенной и взаимодействие с пользователем
class UniverseRenderer {
public:
    // Отображает вселенную в консоли без границ
    static void render(const Universe& universe);
    
    // Отображает вселенную в консоли с рамкой (границами)
    static void render_with_border(const Universe& universe);
    
    // Отображает информацию о вселенной (имя, правило, поколение, размер)
    static void render_info(const Universe& universe);
    
    // Очищает экран консоли (кроссплатформенно)
    static void clear_screen();
    
    // Показывает приветственное сообщение при запуске программы
    static void show_welcome_message();
    
private:
    // Символы для отрисовки (можно изменить для кастомизации)
    static const char LIVE_CELL = 'O';        // Символ живой клетки
    static const char DEAD_CELL = '.';        // Символ мёртвой клетки
    static const char BORDER_VERTICAL = '|';  // Вертикальная граница
    static const char BORDER_HORIZONTAL = '-';// Горизонтальная граница
    static const char BORDER_CORNER = '+';    // Угол границы
};

#endif // UNIVERSE_RENDERER_HPP