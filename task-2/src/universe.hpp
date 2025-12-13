#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>
#include <string>
#include "rule.hpp"

// Класс, представляющий игровую вселенную (поле игры)
class Universe {
private:
    int width;                         // Ширина игрового поля (количество столбцов)
    int height;                        // Высота игрового поля (количество строк)
    Rule rule;                         // Правила перехода клеток
    std::string name;                  // Имя вселенной (для отображения)
    std::vector<std::vector<bool>> grid;  // Двумерный массив клеток: true = живая, false = мёртвая
    int generation;                    // Текущее поколение (номер итерации)
    
    // Подсчитывает количество живых соседей для клетки (x, y) с учётом тороидальной геометрии
    int count_live_neighbors(int x, int y) const;
    
public:
    // Конструктор вселенной с заданными размерами, правилами и именем
    Universe(int w, int h, const Rule& r = Rule::default_rule(), 
             const std::string& n = "Unnamed Universe");
    
    // Изменяет размеры вселенной (сохраняет существующие клетки, если возможно)
    void resize(int w, int h);
    
    // Устанавливает состояние клетки (живая/мёртвая)
    void set_cell(int x, int y, bool alive);
    
    // Возвращает состояние клетки (живая/мёртвая)
    bool get_cell(int x, int y) const;
    
    // Выполняет n итераций игры (по умолчанию 1)
    void tick(int n = 1);
    
    // Очищает поле (все клетки становятся мёртвыми, поколение сбрасывается в 0)
    void clear();
    
    // Инициализирует поле случайными значениями с заданной вероятностью жизни клетки
    void random_init(double alive_probability = 0.3);
    
    // Загружает вселенную из списка координат живых клеток
    void load_from_coordinates(const std::vector<std::pair<int, int>>& coords);
    
    // --- Геттеры (методы для получения значений приватных полей) ---
    int get_width() const { return width; }
    int get_height() const { return height; }
    const Rule& get_rule() const { return rule; }
    const std::string& get_name() const { return name; }
    int get_generation() const { return generation; }
    
    // --- Сеттеры (методы для изменения значений приватных полей) ---
    void set_name(const std::string& n) { name = n; }
    void set_rule(const Rule& r) { rule = r; }
    
    // Для корректного копирования объектов
    Universe(const Universe& other) = default;
    Universe& operator=(const Universe& other) = default;
};

#endif 