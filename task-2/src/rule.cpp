#include "rule.hpp"
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iostream>

// Конструктор, принимающий строку с правилом формата "Bx/Sy"
Rule::Rule(const std::string& rule_str) {
    // Поиск позиций символов 'B', '/' и 'S' в строке правила
    size_t b_pos = rule_str.find('B');      // Позиция начала условий рождения
    size_t slash_pos = rule_str.find('/');  // Позиция разделителя
    size_t s_pos = rule_str.find('S');      // Позиция начала условий выживания
    
    // Проверка корректности формата строки правила
    if (b_pos == std::string::npos || slash_pos == std::string::npos || s_pos == std::string::npos) {
        // Если формат некорректный, выводим предупреждение и используем правило по умолчанию
        std::cerr << "Warning: Invalid rule format '" << rule_str 
                  << "'. Using default B3/S23." << std::endl;
        *this = default_rule();  // Используем правило по умолчанию
        return;                  // Выходим из конструктора
    }
    
    // Извлекаем подстроки с условиями рождения и выживания
    // birth_str - часть строки между 'B' и '/'
    std::string birth_str = rule_str.substr(b_pos + 1, slash_pos - b_pos - 1);
    // survive_str - часть строки после 'S'
    std::string survive_str = rule_str.substr(s_pos + 1);
    
    // Парсим условия рождения: каждый символ должен быть цифрой 0-8
    for (char c : birth_str) {
        if (c >= '0' && c <= '8') {                // Проверяем, что символ - цифра 0-8
            birth_conditions.insert(c - '0');      // Преобразуем символ в число и добавляем в множество
        } else {
            // Некорректный символ - выводим предупреждение
            std::cerr << "Warning: Invalid character '" << c 
                      << "' in birth condition. Ignoring." << std::endl;
        }
    }
    
    // Парсим условия выживания: каждый символ должен быть цифрой 0-8
    for (char c : survive_str) {
        if (c >= '0' && c <= '8') {                // Проверяем, что символ - цифра 0-8
            survive_conditions.insert(c - '0');    // Преобразуем символ в число и добавляем в множество
        } else {
            // Некорректный символ - выводим предупреждение
            std::cerr << "Warning: Invalid character '" << c 
                      << "' in survive condition. Ignoring." << std::endl;
        }
    }
    
    // Проверяем, что условия рождения не пустые
    if (birth_conditions.empty()) {
        std::cerr << "Warning: No valid birth conditions. Using default." << std::endl;
        birth_conditions = {3};  // Используем значение по умолчанию для рождения
    }
    
    // Проверяем, что условия выживания не пустые
    if (survive_conditions.empty()) {
        std::cerr << "Warning: No valid survive conditions. Using default." << std::endl;
        survive_conditions = {2, 3};  // Используем значения по умолчанию для выживания
    }
}

// Проверяет, должна ли мёртвая клетка родиться при заданном количестве живых соседей
bool Rule::should_birth(int live_neighbors) const {
    // Ищем количество соседей в множестве условий рождения
    return birth_conditions.find(live_neighbors) != birth_conditions.end();
}

// Проверяет, должна ли живая клетка выжить при заданном количестве живых соседей
bool Rule::should_survive(int live_neighbors) const {
    // Ищем количество соседей в множестве условий выживания
    return survive_conditions.find(live_neighbors) != survive_conditions.end();
}

// Преобразует правило в строковый формат "Bx/Sy"
std::string Rule::to_string() const {
    std::ostringstream oss;  // Поток для формирования строки
    oss << "B";              // Начинаем с символа рождения
    
    // Добавляем все условия рождения
    for (int cond : birth_conditions) {
        oss << cond;
    }
    
    oss << "/S";  // Добавляем разделитель и символ выживания
    
    // Добавляем все условия выживания
    for (int cond : survive_conditions) {
        oss << cond;
    }
    
    return oss.str();  // Возвращаем сформированную строку
} 
