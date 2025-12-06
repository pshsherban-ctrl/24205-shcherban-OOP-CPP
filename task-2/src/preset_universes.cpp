#include "preset_universes.hpp"
#include <iostream>
#include <vector>

// Создаёт вселенную по указанному пресету
Universe PresetUniverses::create(PresetUniverses::Preset preset) {
    // Используем switch для выбора соответствующего метода создания
    switch (preset) {
        case PresetUniverses::Preset::GLIDER:
            return create_glider();                // Создаём глайдер
        case PresetUniverses::Preset::GOSPER_GLIDER_GUN:
            return create_gosper_glider_gun();     // Создаём ружьё Госпера
        case PresetUniverses::Preset::PULSAR:
            return create_pulsar();                // Создаём пульсар
        case PresetUniverses::Preset::SPACESHIP:
            return create_spaceship();             // Создаём космический корабль
        case PresetUniverses::Preset::HIVE:
            return create_hive();                  // Создаём улей
        case PresetUniverses::Preset::HIGHLIFE_REPLICATOR:
            return create_highlife_replicator();   // Создаём HighLife репликатор
        case PresetUniverses::Preset::DAY_AND_NIGHT:
            return create_day_and_night();         // Создаём паттерн "День и ночь"
        case PresetUniverses::Preset::SEEDS_EXPLOSION:
            return create_seeds_explosion();       // Создаём Seeds взрыв
        case PresetUniverses::Preset::MAZE_GROWTH:
            return create_maze_growth();           // Создаём рост лабиринта
        case PresetUniverses::Preset::PATTERN_2X2:
            return create_pattern_2x2();           // Создаём 2x2 паттерн
        default:
            return create_glider();                // По умолчанию возвращаем глайдер
    }
}

// Возвращает список всех доступных пресетов с их названиями
std::vector<std::pair<std::string, PresetUniverses::Preset>> PresetUniverses::get_available_presets() {
    // Создаём и возвращаем вектор пар "название - значение пресета"
    return {
        {"Glider", PresetUniverses::Preset::GLIDER},                       // Глайдер
        {"Gosper Glider Gun", PresetUniverses::Preset::GOSPER_GLIDER_GUN}, // Ружьё Госпера
        {"Pulsar", PresetUniverses::Preset::PULSAR},                       // Пульсар
        {"Lightweight Spaceship", PresetUniverses::Preset::SPACESHIP},     // Космический корабль
        {"Beehive", PresetUniverses::Preset::HIVE},                        // Улей
        {"HighLife Replicator", PresetUniverses::Preset::HIGHLIFE_REPLICATOR}, // HighLife репликатор
        {"Day & Night Pattern", PresetUniverses::Preset::DAY_AND_NIGHT},   // "День и ночь"
        {"Seeds Explosion", PresetUniverses::Preset::SEEDS_EXPLOSION},     // Seeds взрыв
        {"Maze Growth", PresetUniverses::Preset::MAZE_GROWTH},             // Рост лабиринта
        {"2x2 Pattern", PresetUniverses::Preset::PATTERN_2X2}              // 2x2 паттерн
    };
}

// Показывает меню выбора пресета в консоли
void PresetUniverses::show_preset_menu() {
    // Получаем список доступных пресетов
    auto presets = get_available_presets();
    
    std::cout << "\nAvailable Preset Universes:\n";
    std::cout << std::string(40, '-') << "\n";  // Рисуем разделительную линию
    
    // Выводим нумерованный список пресетов
    for (size_t i = 0; i < presets.size(); ++i) {
        std::cout << i + 1 << ". " << presets[i].first << "\n";  // Номер и название
    }
    
    std::cout << std::string(40, '-') << "\n";  // Рисуем завершающую линию
}

// === Реализации конкретных пресетов ===

// Создаёт вселену с глайдером (классическая движущаяся структура)
Universe PresetUniverses::create_glider() {
    // Создаём вселенную размером 40x20 с правилом B3/S23 и именем "Glider"
    Universe universe(40, 20, Rule("B3/S23"), "Glider");
    
    // Координаты живых клеток, образующих глайдер
    std::vector<std::pair<int, int>> coords = {
        {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}  // Форма глайдера
    };
    
    // Загружаем координаты во вселенную
    universe.load_from_coordinates(coords);
    return universe;  // Возвращаем созданную вселенную
}

// Создаёт планерное ружьё Госпера
Universe PresetUniverses::create_gosper_glider_gun() {
    // Создаём большую вселенную для размещения ружья Госпера
    Universe universe(50, 30, Rule("B3/S23"), "Gosper Glider Gun");
    
    // Координаты живых клеток ружья Госпера
    std::vector<std::pair<int, int>> coords = {
        // Левый стабилизатор
        {1,5},{2,5},{1,6},{2,6},
        // Левый эмиттер
        {11,5},{11,6},{11,7},{12,4},{12,8},{13,3},{13,9},{14,3},{14,9},
        {15,6},{16,4},{16,8},{17,5},{17,6},{17,7},{18,6},
        // Правый эмиттер
        {21,3},{21,4},{21,5},{22,3},{22,4},{22,5},{23,2},{23,6},
        {25,1},{25,2},{25,6},{25,7},
        // Правый стабилизатор
        {35,3},{35,4},{36,3},{36,4}
    };
    
    universe.load_from_coordinates(coords);
    return universe;
}

// Создаёт пульсар (периодический осциллятор с периодом 3)
Universe PresetUniverses::create_pulsar() {
    Universe universe(30, 30, Rule("B3/S23"), "Pulsar");
    std::vector<std::pair<int, int>> coords = {
        // Верхние и нижние "лепестки"
        {2,4},{3,4},{4,4},{8,4},{9,4},{10,4},
        {2,5},{10,5},
        {2,6},{3,6},{4,6},{8,6},{9,6},{10,6},
        // Левые и правые "лепестки"
        {4,2},{5,2},{6,2},{4,3},{5,3},{6,3},{4,7},{5,7},{6,7},{4,8},{5,8},{6,8},
        {8,2},{9,2},{10,2},{8,3},{9,3},{10,3},{8,7},{9,7},{10,7},{8,8},{9,8},{10,8},
        // Обратные верхние и нижние "лепестки"
        {2,9},{3,9},{4,9},{8,9},{9,9},{10,9},
        {2,10},{10,10},
        {2,11},{3,11},{4,11},{8,11},{9,11},{10,11}
    };
    universe.load_from_coordinates(coords);
    return universe;
}

// Создаёт лёгкий космический корабль (Lightweight Spaceship - LWSS)
Universe PresetUniverses::create_spaceship() {
    Universe universe(30, 20, Rule("B3/S23"), "Lightweight Spaceship");
    std::vector<std::pair<int, int>> coords = {
        {1,0},{2,0},{3,0},{4,0},  // Верхняя часть корпуса
        {0,1},{4,1},               // Боковые выступы
        {4,2},                     // Хвост
        {0,3},{3,3}                // Нижняя часть
    };
    universe.load_from_coordinates(coords);
    return universe;
}

// Создаёт улей (стабильная неподвижная структура из 6 клеток)
Universe PresetUniverses::create_hive() {
    Universe universe(20, 20, Rule("B3/S23"), "Beehive");
    std::vector<std::pair<int, int>> coords = {
        {1,1},{2,1},  // Верхняя часть улья
        {0,2},{3,2},  // Средняя часть (с дыркой посередине)
        {1,3},{2,3}   // Нижняя часть улья
    };
    universe.load_from_coordinates(coords);
    return universe;
}

// Создаёт репликатор для правила HighLife (B36/S23)
Universe PresetUniverses::create_highlife_replicator() {
    // HighLife - вариант игры "Жизнь" с дополнительным правилом рождения при 6 соседях
    Universe universe(40, 40, Rule("B36/S23"), "HighLife Replicator");
    std::vector<std::pair<int, int>> coords = {
        {0,0},{1,0},{0,1},{1,1},      // Первый блок 2x2
        {10,10},{11,10},{10,11},{11,11},  // Второй блок 2x2
        {20,20},{21,20},{20,21},{21,21}   // Третий блок 2x2
    };
    universe.load_from_coordinates(coords);
    return universe;
}

// Создаёт паттерн для правила "День и ночь" (B3678/S34678)
Universe PresetUniverses::create_day_and_night() {
    // "День и ночь" - симметричное правило, интересное своими паттернами
    Universe universe(30, 30, Rule("B3678/S34678"), "Day & Night");
    std::vector<std::pair<int, int>> coords = {
        {10,10},{11,10},{12,10},  // Горизонтальная линия из 3 клеток
        {10,11},{12,11},          // Две клетки по бокам
        {10,12},{11,12},{12,12}   // Горизонтальная линия из 3 клеток (снизу)
    };
    universe.load_from_coordinates(coords);
    return universe;
}

// Создаёт конфигурацию для правила Seeds (B2/S)
Universe PresetUniverses::create_seeds_explosion() {
    // Seeds - правило, где клетки никогда не выживают (только рождаются)
    // Из одной клетки возникает быстрорастущая структура
    Universe universe(30, 30, Rule("B2/S"), "Seeds Explosion");
    std::vector<std::pair<int, int>> coords = {
        {15,15}  // Всего одна живая клетка в центре
    };
    universe.load_from_coordinates(coords);
    return universe;
}

// Создаёт конфигурацию для роста лабиринта (B3/S12345)
Universe PresetUniverses::create_maze_growth() {
    // Правило, создающее лабиринтоподобные структуры
    Universe universe(40, 40, Rule("B3/S12345"), "Maze Growth");
    std::vector<std::pair<int, int>> coords = {
        {20,20},{21,20},{22,20},  // Горизонтальная линия из 3 клеток
        {20,21},{22,21},          // Две клетки по бокам
        {20,22},{21,22},{22,22}   // Горизонтальная линия из 3 клеток
    };
    universe.load_from_coordinates(coords);
    return universe;
}

// Создаёт 2x2 паттерн для специального правила (B36/S125)
Universe PresetUniverses::create_pattern_2x2() {
    // Простой 2x2 блок для демонстрации специального правила
    Universe universe(30, 30, Rule("B36/S125"), "2x2 Pattern");
    std::vector<std::pair<int, int>> coords = {
        {10,10},{11,10},  // Верхняя строка 2x2 блока
        {10,11},{11,11}   // Нижняя строка 2x2 блока
    };
    universe.load_from_coordinates(coords);
    return universe;
}