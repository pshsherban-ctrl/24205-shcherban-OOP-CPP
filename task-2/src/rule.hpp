#ifndef RULE_HPP
#define RULE_HPP

#include <set>
#include <string>
#include <stdexcept>

// Класс для представления правил клеточного автомата
// Формат: Bx/Sy, где x и y - наборы цифр 0-8
class Rule {
private:
    // Условия рождения: клетка становится живой, если у неё N живых соседей, где N ∈ birth_conditions
    std::set<int> birth_conditions;
    
    // Условия выживания: живая клетка остаётся живой, если у неё N живых соседей, где N ∈ survive_conditions
    std::set<int> survive_conditions;
    
public:
    // Конструктор по умолчанию
    Rule() = default;
    
    // Конструктор из строки формата "Bx/Sy"
    explicit Rule(const std::string& rule_str);
    
    // Проверяет, должна ли мёртвая клетка родиться при заданном количестве соседей
    bool should_birth(int live_neighbors) const;
    
    // Проверяет, должна ли живая клетка выжить при заданном количестве соседей
    bool should_survive(int live_neighbors) const;
    
    // Преобразует правило обратно в строковый формат
    std::string to_string() const;
    
    // Возвращает правило по умолчанию (классическая игра "Жизнь")
    static Rule default_rule() { return Rule("B3/S23"); }
};

#endif 