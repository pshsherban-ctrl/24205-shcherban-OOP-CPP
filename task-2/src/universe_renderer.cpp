#include "universe_renderer.hpp"
#include <iostream>
#include <iomanip>

// Подключаем платформозависимые заголовки для очистки экрана
#ifdef _WIN32
#include <windows.h>  // Для Windows API функций
#else
#include <cstdlib>    // Для системных вызовов в Unix-системах
#endif

// Отображает вселенную в консоли без границ (простая отрисовка)
void UniverseRenderer::render(const Universe& universe) {
    // Проходим по всем строкам (y) и столбцам (x) поля
    for (int y = 0; y < universe.get_height(); ++y) {
        for (int x = 0; x < universe.get_width(); ++x) {
            // Выводим символ в зависимости от состояния клетки
            std::cout << (universe.get_cell(x, y) ? LIVE_CELL : DEAD_CELL);
        }
        std::cout << '\n';  // Переход на новую строку после каждой строки поля
    }
}

// Отображает вселенную в консоли с рамкой вокруг поля
void UniverseRenderer::render_with_border(const Universe& universe) {
    // Верхняя граница: угловой символ + горизонтальная линия по ширине поля + угловой символ
    std::cout << BORDER_CORNER;
    for (int x = 0; x < universe.get_width(); ++x) {
        std::cout << BORDER_HORIZONTAL;  // Рисуем горизонтальную линию
    }
    std::cout << BORDER_CORNER << '\n';
    
    // Отрисовка самого поля с вертикальными границами по бокам
    for (int y = 0; y < universe.get_height(); ++y) {
        std::cout << BORDER_VERTICAL;  // Левая вертикальная граница
        for (int x = 0; x < universe.get_width(); ++x) {
            // Выводим символ клетки (живая 'O' или мёртвая '.')
            std::cout << (universe.get_cell(x, y) ? LIVE_CELL : DEAD_CELL);
        }
        std::cout << BORDER_VERTICAL << '\n';  // Правая вертикальная граница
    }
    
    // Нижняя граница (аналогично верхней)
    std::cout << BORDER_CORNER;
    for (int x = 0; x < universe.get_width(); ++x) {
        std::cout << BORDER_HORIZONTAL;
    }
    std::cout << BORDER_CORNER << '\n';
}

// Отображает информационную панель о текущем состоянии вселенной
void UniverseRenderer::render_info(const Universe& universe) {
    std::cout << "\n=== Conway's Game of Life ===\n";
    std::cout << "Name: " << universe.get_name() << "\n";              // Имя вселенной
    std::cout << "Generation: " << universe.get_generation() << "\n";  // Номер поколения
    std::cout << "Rule: " << universe.get_rule().to_string() << "\n";  // Правило игры
    std::cout << "Size: " << universe.get_width() << " x " << universe.get_height() << "\n";  // Размеры поля
    std::cout << std::string(40, '=') << "\n\n";  // Разделительная линия
}

// Очищает экран консоли 
void UniverseRenderer::clear_screen() {
#ifdef _WIN32
    // Реализация для Windows с использованием Windows API
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // Получаем хэндл консоли
    COORD coord = {0, 0};  // Координаты начала очистки (левый верхний угол)
    DWORD count;  // Переменная для хранения количества обработанных символов
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;  // Структура для информации о буфере экрана
    
    // Получаем информацию о текущем буфере экрана
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        // Вычисляем общее количество ячеек в консоли (ширина * высота)
        DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        
        // Заполняем всю консоль пробелами
        FillConsoleOutputCharacter(hStdOut, ' ', cellCount, coord, &count);
        
        // Заполняем атрибуты (цвета) текущими атрибутами
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, coord, &count);
        
        // Устанавливаем курсор в начальную позицию (0, 0)
        SetConsoleCursorPosition(hStdOut, coord);
    }
#else
    // \033[2J - очистка всего экрана
    // \033[1;1H - перемещение курсора в позицию (1, 1)
    std::cout << "\033[2J\033[1;1H";
#endif
}

// Показывает приветственное сообщение при запуске программы
void UniverseRenderer::show_welcome_message() {
    clear_screen();  // Очищаем экран перед выводом приветствия
    
    // Выводим ASCII-арт название игры для красивого оформления
    std::cout << R"(
   _____                           __    _      __  
  / ___/__  __ _  __ _  ___ ____  / /   (_)__  / /__
 / /__/ _ \/  ' \/  ' \/ _ `/ _ \/ _ \/ / _ \/  '_/
 \___/\___/_/_/_/_/_/_/\_,_/_//_/_.__/_/_//_/_/\_\
                                                   
)" << std::endl;
    
    // Основное приветственное сообщение
    std::cout << "Welcome to Conway's Game of Life!\n";
    std::cout << "Type 'help' for available commands.\n";
    std::cout << "Type 'exit' to quit.\n\n";
}