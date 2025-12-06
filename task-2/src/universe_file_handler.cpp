#include "universe_file_handler.hpp"
#include <sstream>
#include <iostream>
#include <set>

// Загружает вселенную из файла формата Life 1.06
Universe UniverseFileHandler::load_from_file(const std::string& filename) {
    // Открываем файл для чтения
    std::ifstream file(filename);
    
    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    // Читаем первую строку - должна быть "Life 1.06"
    std::string first_line;
    std::getline(file, first_line);
    
    // Проверяем формат файла
    if (first_line != "Life 1.06") {
        throw std::runtime_error("Invalid file format. Expected 'Life 1.06'");
    }
    
    // Инициализируем значения по умолчанию
    std::string name = "Unnamed";           // Имя вселенной по умолчанию
    Rule rule = Rule::default_rule();       // Правило по умолчанию
    std::vector<std::pair<int, int>> coordinates;  // Вектор координат живых клеток
    std::set<std::pair<int, int>> coordinate_set;  // Множество для проверки дубликатов
    
    std::string line;
    int line_number = 2;  // Начинаем с 2-й строки (после "Life 1.06")
    
    // Читаем файл построчно
    while (std::getline(file, line)) {
        if (line.empty()) continue;  // Пропускаем пустые строки
        
        if (line[0] == '#') {
            // Строка начинается с '#' - это комментарий или метаданные
            if (line.length() >= 3) {  // Минимальная длина "#X "
                if (line.substr(0, 3) == "#N ") {
                    // #N <name> - имя вселенной
                    name = line.substr(3);  // Извлекаем имя (после "#N ")
                } else if (line.substr(0, 3) == "#R ") {
                    // #R <rule> - правило игры
                    try {
                        rule = Rule(line.substr(3));  // Парсим правило
                    } catch (const std::exception& e) {
                        // Если не удалось распарсить правило, используем правило по умолчанию
                        std::cerr << "Warning: " << e.what() 
                                  << ". Using default rule." << std::endl;
                    }
                }
            }
        } else {
            // Строка с координатами живой клетки (формат: "x y")
            try {
                // Парсим координаты
                auto coord = parse_coordinate(line);
                
                // Проверяем на дубликаты
                if (coordinate_set.find(coord) != coordinate_set.end()) {
                    // Нашли дубликат - выводим предупреждение
                    std::cerr << "Warning: Duplicate coordinate at line " 
                              << line_number << ": " << line << std::endl;
                } else {
                    // Добавляем координату в вектор и множество
                    coordinates.push_back(coord);
                    coordinate_set.insert(coord);
                }
            } catch (const std::exception& e) {
                // Ошибка парсинга координат
                std::cerr << "Error parsing coordinate at line " 
                          << line_number << ": " << e.what() << std::endl;
            }
        }
        ++line_number;  // Увеличиваем номер строки
    }
    
    // Проверяем, есть ли живые клетки
    if (coordinates.empty()) {
        std::cerr << "Warning: No live cells found in file." << std::endl;
    }
    
    // Определяем необходимый размер поля на основе координат
    auto [max_x, max_y] = find_grid_size(coordinates);
    
    // Создаем поле с небольшим запасом вокруг живых клеток
    int width = std::max(max_x + 10, 30);   // Минимум 30 клеток в ширину
    int height = std::max(max_y + 10, 30);  // Минимум 30 клеток в высоту
    
    // Создаем вселенную
    Universe universe(width, height, rule, name);
    
    // Загружаем живые клетки
    universe.load_from_coordinates(coordinates);
    
    return universe;  // Возвращаем созданную вселенную
}

// Сохраняет вселенную в файл формата Life 1.06
void UniverseFileHandler::save_to_file(const Universe& universe, const std::string& filename) {
    // Открываем файл для записи
    std::ofstream file(filename);
    
    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    // Записываем заголовок формата
    file << "Life 1.06\n";
    
    // Записываем имя вселенной
    file << "#N " << universe.get_name() << "\n";
    
    // Записываем правило игры
    file << "#R " << universe.get_rule().to_string() << "\n";
    
    // Записываем координаты всех живых клеток
    for (int x = 0; x < universe.get_width(); ++x) {
        for (int y = 0; y < universe.get_height(); ++y) {
            if (universe.get_cell(x, y)) {
                file << x << " " << y << "\n";
            }
        }
    }
    
    // Выводим сообщение об успешном сохранении
    std::cout << "Universe saved to: " << filename << std::endl;
} 

// Парсит строку координат формата "x y"
std::pair<int, int> UniverseFileHandler::parse_coordinate(const std::string& line) {
    std::istringstream iss(line);
    int x, y;
    
    // Пытаемся извлечь два числа
    if (!(iss >> x >> y)) {
        throw std::runtime_error("Invalid coordinate format: " + line);
    }
    
    // Проверяем, что координаты не отрицательные
    if (x < 0 || y < 0) {
        throw std::runtime_error("Coordinates must be non-negative: " + line);
    }
    
    return {x, y};
}

// Находит минимальные размеры поля для размещения всех координат
std::pair<int, int> UniverseFileHandler::find_grid_size(const std::vector<std::pair<int, int>>& coordinates) {
    int max_x = 0, max_y = 0;
    
    // Находим максимальные координаты
    for (const auto& coord : coordinates) {
        max_x = std::max(max_x, coord.first);
        max_y = std::max(max_y, coord.second);
    }
    
    // Возвращаем размеры с небольшим запасом (+1)
    return {max_x + 1, max_y + 1};
}