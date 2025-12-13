#ifndef PRESET_UNIVERSES_HPP
#define PRESET_UNIVERSES_HPP

#include "universe.hpp"
#include <vector>

// Класс для создания предустановленных (пресетных) вселенных
// Содержит набор известных и интересных конфигураций для демонстрации
class PresetUniverses {
public:
    // Перечисление доступных пресетов (предустановленных вселенных)
    enum class Preset {
        GLIDER,               // Глайдер - простейшая движущаяся структура
        GOSPER_GLIDER_GUN,    // Планерное ружьё Госпера - генератор глайдеров
        PULSAR,               // Пульсар - осциллятор с периодом 3
        SPACESHIP,            // Лёгкий космический корабль - движущаяся структура
        HIVE,                 // Улей - стабильная неподвижная структура
        HIGHLIFE_REPLICATOR,  // Репликатор в правиле HighLife (B36/S23)
        DAY_AND_NIGHT,        // Паттерн для правила "День и ночь" (B3678/S34678)
        SEEDS_EXPLOSION,      // Взрыв в правиле Seeds (B2/S)
        MAZE_GROWTH,          // Рост лабиринта (B3/S12345)
        PATTERN_2X2           // 2x2 паттерн для правила B36/S125
    };
    
    // Создаёт вселенную по указанному пресету
    static Universe create(Preset preset);
    
    // Возвращает список доступных пресетов с их названиями
    static std::vector<std::pair<std::string, Preset>> get_available_presets();
    
    // Показывает меню выбора пресета в консоли
    static void show_preset_menu();
    
private:
    // Приватные методы для создания конкретных пресетов
    
    // Создаёт глайдер (классическая движущаяся структура)
    static Universe create_glider();
    
    // Создаёт планерное ружьё Госпера (бесконечный генератор глайдеров)
    static Universe create_gosper_glider_gun();
    
    // Создаёт пульсар (осциллятор с периодом 3)
    static Universe create_pulsar();
    
    // Создаёт лёгкий космический корабль (движущаяся структура)
    static Universe create_spaceship();
    
    // Создаёт улей (стабильная неподвижная структура)
    static Universe create_hive();
    
    // Создаёт репликатор для правила HighLife
    static Universe create_highlife_replicator();
    
    // Создаёт паттерн для правила "День и ночь"
    static Universe create_day_and_night();
    
    // Создаёт конфигурацию для правила Seeds (быстрорастущая)
    static Universe create_seeds_explosion();
    
    // Создаёт конфигурацию для роста лабиринта
    static Universe create_maze_growth();
    
    // Создаёт 2x2 паттерн для специального правила
    static Universe create_pattern_2x2();
};

#endif // PRESET_UNIVERSES_HPP