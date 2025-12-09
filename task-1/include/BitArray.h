#ifndef BITARRAY_H
#define BITARRAY_H

#include <string>
#include <vector>
#include <stdexcept>

class BitArray {
public:
    // Конструктор по умолчанию - создает пустой массив
    BitArray();
    
    // Деструктор
    ~BitArray();

    // Конструктор с параметрами
    // num_bits - количество битов
    // value - начальное значение
    explicit BitArray(int num_bits, unsigned long value = 0);
    
    // Конструктор копирования
    BitArray(const BitArray& b);
    
    // Обмен содержимым с другим BitArray
    void swap(BitArray& b);
    
    // Оператор присваивания
    BitArray& operator=(const BitArray& b);
    
    // Изменение размера массива
    void resize(int num_bits, bool value = false);
    
    // Очистка массива
    void clear();
    
    // Добавление бита в конец
    void push_back(bool bit);
    
    // Побитовое И с присваиванием
    BitArray& operator&=(const BitArray& b);
    
    // Побитовое ИЛИ с присваиванием
    BitArray& operator|=(const BitArray& b);
    
    // Побитовое XOR с присваиванием
    BitArray& operator^=(const BitArray& b);
    
    // Битовый сдвиг влево с присваиванием
    BitArray& operator<<=(int n);
    
    // Битовый сдвиг вправо с присваиванием
    BitArray& operator>>=(int n);
    
    // Битовый сдвиг влево (создает копию)
    BitArray operator<<(int n) const;
    
    // Битовый сдвиг вправо (создает копию)
    BitArray operator>>(int n) const;
    
    // Установка бита по индексу
    BitArray& set(int n, bool val = true);
    
    // Установка всех битов в true
    BitArray& set();
    
    // Сброс конкретного бита в false
    BitArray& reset(int n);
    
    // Сброс всех битов в false
    BitArray& reset();
    
    // Проверка, есть ли хотя бы один true
    bool any() const;
    
    // Проверка, все ли биты false
    bool none() const;
    
    // Побитовая инверсия
    BitArray operator~() const;
    
    // Подсчет единичных битов
    int count() const;
    
    // Доступ к биту по индексу (ТОЛЬКО ДЛЯ ЧТЕНИЯ)
    bool operator[](int i) const;
    
    // Доступ к биту по индексу (ДЛЯ ЧТЕНИЯ И ЗАПИСИ)
    // Возвращает специальный прокси-объект, позволяющий изменять бит
    class BitProxy; // Предварительное объявление
    BitProxy operator[](int i);
    
    // Получение количества битов
    int size() const;
    
    // Проверка на пустоту
    bool empty() const;
    
    // Преобразование в строку
    std::string to_string() const;
    
    // Прокси-класс для оператора [] с возможностью записи
    class BitProxy {
    public:
        // Оператор присваивания для bool
        BitProxy& operator=(bool val);
        
        // Оператор присваивания для другого BitProxy
        BitProxy& operator=(const BitProxy& other);
        
        // Неявное преобразование к bool (для чтения)
        operator bool() const;
        
    private:
        // Только BitArray может создавать BitProxy
        BitProxy(BitArray& bit_array, int index);
        
        BitArray& bit_array_;  // Ссылка на BitArray
        int index_;            // Индекс бита
        
        // BitArray - дружественный класс, чтобы иметь доступ к конструктору
        friend class BitArray;
    };

private:
    // Внутреннее хранилище - биты упакованы в unsigned long
    std::vector<unsigned long> data_;
    
    // Количество битов в массиве
    int num_bits_;
    
    // Константа: количество битов в одном unsigned long
    static const int BITS_PER_LONG = sizeof(unsigned long) * 8;
    
    // Проверка корректности индекса
    void validate_index(int n) const;
    
    // Проверка совпадения размеров
    void validate_size(const BitArray& b) const;
    
    // Обрезание неиспользуемых битов в последнем блоке
    void trim_last_block();
    
    // Установка бита без проверки индекса (для внутреннего использования)
    void set_bit_unchecked(int n, bool val);
    
    // Получение бита без проверки индекса (для внутреннего использования)
    bool get_bit_unchecked(int n) const;
};

// Оператор сравнения на равенство
bool operator==(const BitArray& a, const BitArray& b);

// Оператор сравнения на неравенство
bool operator!=(const BitArray& a, const BitArray& b);

// Побитовое И (создает новый объект)
BitArray operator&(const BitArray& b1, const BitArray& b2);

// Побитовое ИЛИ (создает новый объект)
BitArray operator|(const BitArray& b1, const BitArray& b2);

// Побитовое XOR (создает новый объект)
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif