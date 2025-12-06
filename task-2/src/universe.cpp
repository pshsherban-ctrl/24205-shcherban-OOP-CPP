#include "universe.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>

//создает вселенную заданного размера с указанными правилами и именем
Universe::Universe(int w, int h, const Rule& r, const std::string& n)
    : width(w), height(h), rule(r), name(n), generation(0) {  // Инициализация полей
    // Проверка корректности размеров
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Width and height must be positive");
    }
    // Создаем двумерный массив width x height, инициализируя все клетки как мёртвые (false)
    grid.resize(width, std::vector<bool>(height, false));
}

// Подсчет живых соседей для клетки (x, y) с учётом тороидальной геометрии (тор)
int Universe::count_live_neighbors(int x, int y) const {
    int count = 0;  // Счетчик живых соседей
    
    // Проверяем всех 8 соседей (dx, dy от -1 до 1)
    for (int dx = -1; dx <= 1; ++dx) {       // dx: смещение по горизонтали
        for (int dy = -1; dy <= 1; ++dy) {   // dy: смещение по вертикали
            if (dx == 0 && dy == 0) continue;  // Пропускаем саму клетку
            
            // Вычисляем координаты соседа с учётом тороидальной геометрии:
            // (x+dx+width) % width - обеспечивает зацикливание по горизонтали
            // (y+dy+height) % height - обеспечивает зацикливание по вертикали
            int nx = (x + dx + width) % width;    // Нормализованная координата X
            int ny = (y + dy + height) % height;  // Нормализованная координата Y
            
            // Если сосед живой, увеличиваем счетчик
            if (grid[nx][ny]) {
                ++count;
            }
        }
    }
    
    return count;  // Возвращаем общее количество живых соседей
}

// Выполняет одну итерацию игры (переход к следующему поколению)
void Universe::tick(int n) {
    // Выполняем n итераций
    for (int i = 0; i < n; ++i) {
        // Создаем копию текущего состояния для вычисления следующего поколения
        std::vector<std::vector<bool>> new_grid = grid;
        
        // Проходим по всем клеткам поля
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                // Подсчитываем количество живых соседей для текущей клетки
                int live_neighbors = count_live_neighbors(x, y);
                bool is_alive = grid[x][y];  // Текущее состояние клетки
                
                if (is_alive) {
                    // Клетка живая: проверяем условия выживания
                    if (!rule.should_survive(live_neighbors)) {
                        // Условия выживания не выполнены - клетка умирает
                        new_grid[x][y] = false;
                    }
                    // Если условия выживания выполнены, клетка остается живой (значение уже true)
                } else {
                    // Клетка мертвая: проверяем условия рождения
                    if (rule.should_birth(live_neighbors)) {
                        // Условия рождения выполнены - клетка рождается
                        new_grid[x][y] = true;
                    }
                }
            }
        }
        
        // Заменяем старое состояние на новое
        grid = std::move(new_grid);
        // Увеличиваем счетчик поколений
        ++generation;
    }
} 
bool Universe::get_cell(int x, int y) const {
    // Проверяем границы и возвращаем состояние клетки
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[x][y];
    }
    return false;
}

void Universe::load_from_coordinates(const std::vector<std::pair<int, int>>& coords) {
    clear();  // Очищаем поле
    
    // Устанавливаем живые клетки по координатам
    for (const auto& coord : coords) {
        int x = coord.first;
        int y = coord.second;
        
        // Проверяем границы
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[x][y] = true;
        } else {
            std::cerr << "Warning: Coordinate (" << x << ", " << y 
                      << ") out of bounds. Ignoring." << std::endl;
        }
    }
    generation = 0;  // Сбрасываем счетчик поколений
}

// Очищает поле (все клетки становятся мёртвыми) и сбрасывает счётчик поколений
void Universe::clear() {
    // Проходим по всем клеткам и устанавливаем их в состояние "мёртвая" (false)
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            grid[x][y] = false;
        }
    }
    generation = 0;  // Сбрасываем счётчик поколений в 0
}