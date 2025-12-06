#include "BitArray.h"

#include <algorithm>   
#include <bitset>      

// Конструктор по умолчанию
BitArray::BitArray() : num_bits_(0) {}  // Инициализируем количество битов нулем

// Деструктор 
BitArray::~BitArray() = default;

// Конструктор с параметрами
BitArray::BitArray(int num_bits, unsigned long value) : num_bits_(num_bits) {
    // Проверяем, что количество битов неотрицательное
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative");
    }
    
    // Вычисляем количество блоков (unsigned long), необходимых для хранения num_bits битов
    // Добавляем BITS_PER_LONG-1 для округления вверх
    int blocks_needed = (num_bits + BITS_PER_LONG - 1) / BITS_PER_LONG;
    
    // Изменяем размер вектора, инициализируя новые элементы нулями
    data_.resize(blocks_needed, 0);
    
    // Если есть хотя бы один блок, устанавливаем начальное значение
    if (blocks_needed > 0) {
        data_[0] = value;          // Помещаем value в первый блок
        trim_last_block();         // Обрезаем неиспользуемые биты в последнем блоке
    }
}

// Конструктор копирования
BitArray::BitArray(const BitArray& b) : data_(b.data_), num_bits_(b.num_bits_) {
    // Копируем вектор и количество битов из объекта b
}

// Обмен содержимым двух объектов BitArray
void BitArray::swap(BitArray& b) {
    // Используем стандартную функцию swap для векторов
    std::swap(data_, b.data_);
    
    // Обмениваем количество битов
    std::swap(num_bits_, b.num_bits_);
}

// Оператор присваивания (используем идиому copy-and-swap)
BitArray& BitArray::operator=(const BitArray& b) {
    // Проверяем, не присваиваем ли объект самому себе
    if (this != &b) {
        // Создаем временную копию объекта b
        BitArray temp(b);
        
        // Обмениваем содержимое текущего объекта с временной копией
        swap(temp);
        
        // Временная копия уничтожается при выходе из области видимости
    }
    return *this;  // Возвращаем ссылку на текущий объект
}

// Изменение размера массива
void BitArray::resize(int num_bits, bool value) {
    // Проверяем корректность нового размера
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative");
    }
    
    // Если размер не изменился, ничего не делаем
    if (num_bits == num_bits_) return;
    
    // Сохраняем старый размер
    int old_num_bits = num_bits_;
    
    // Вычисляем новый размер в блоках
    int new_blocks = (num_bits + BITS_PER_LONG - 1) / BITS_PER_LONG;
    
    // Сохраняем старые данные
    std::vector<unsigned long> old_data = data_;
    
    // Изменяем размер вектора, инициализируя новые элементы нулями
    data_.resize(new_blocks, 0);
    
    // Устанавливаем новое количество битов
    num_bits_ = num_bits;
    
    // Определяем, сколько битов нужно скопировать из старых данных
    int bits_to_copy = std::min(old_num_bits, num_bits);
    
    // Копируем старые биты в новый массив
    for (int i = 0; i < bits_to_copy; ++i) {
        int old_block = i / BITS_PER_LONG;      // Блок в старом массиве
        int old_bit = i % BITS_PER_LONG;        // Позиция бита в блоке
        
        // Если блок существует и бит установлен в старом массиве
        if (old_block < old_data.size() && (old_data[old_block] & (1UL << old_bit))) {
            set(i, true);  // Устанавливаем бит в новом массиве
        }
    }
    
    // Если новый размер больше старого и нужно установить новые биты
    if (num_bits > old_num_bits && value) {
        for (int i = old_num_bits; i < num_bits; ++i) {
            set(i, true);  // Устанавливаем новые биты в true
        }
    }
    
    // Обрезаем неиспользуемые биты в последнем блоке
    trim_last_block();
}

// Очистка массива
void BitArray::clear() {
    data_.clear();   // Очищаем вектор
    num_bits_ = 0;   // Сбрасываем количество битов
}

// Добавление бита в конец массива
void BitArray::push_back(bool bit) {
    // Вычисляем индекс блока и позицию бита в блоке
    int block_index = num_bits_ / BITS_PER_LONG;
    int bit_index = num_bits_ % BITS_PER_LONG;
    
    // Если добавляем первый бит в новый блок
    if (bit_index == 0) {
        data_.push_back(0);  // Добавляем новый блок, инициализированный нулями
    }
    
    // Если добавляемый бит равен true
    if (bit) {
        // Устанавливаем соответствующий бит в текущем блоке
        data_[block_index] |= (1UL << bit_index);
    }
    
    // Увеличиваем количество битов
    num_bits_++;
}

// Побитовое И с присваиванием
BitArray& BitArray::operator&=(const BitArray& b) {
    // Проверяем совпадение размеров массивов
    validate_size(b);
    
    // Применяем операцию И к каждому блоку
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] &= b.data_[i];
    }
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Побитовое ИЛИ с присваиванием
BitArray& BitArray::operator|=(const BitArray& b) {
    // Проверяем совпадение размеров массивов
    validate_size(b);
    
    // Применяем операцию ИЛИ к каждому блоку
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] |= b.data_[i];
    }
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Побитовое XOR с присваиванием
BitArray& BitArray::operator^=(const BitArray& b) {
    // Проверяем совпадение размеров массивов
    validate_size(b);
    
    // Применяем операцию XOR к каждому блоку
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] ^= b.data_[i];
    }
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Битовый сдвиг влево с присваиванием
BitArray& BitArray::operator<<=(int n) {
    // Проверяем корректность величины сдвига
    if (n < 0) {
        throw std::invalid_argument("Shift amount cannot be negative");
    }
    
    // Если сдвиг на 0, ничего не делаем
    if (n == 0) return *this;
    
    // Если сдвиг больше или равен размеру массива, сбрасываем все биты
    if (n >= num_bits_) {
        reset();  // Сбрасываем все биты
        return *this;
    }
    
    // Выполняем сдвиг, начиная со старших битов
    for (int i = num_bits_ - 1; i >= n; --i) {
        set(i, (*this)[i - n]);  // Копируем бит из позиции i-n в позицию i
    }
    
    // Заполняем младшие n битов нулями
    for (int i = 0; i < n; ++i) {
        set(i, false);
    }
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Битовый сдвиг вправо с присваиванием
BitArray& BitArray::operator>>=(int n) {
    // Проверяем корректность величины сдвига
    if (n < 0) {
        throw std::invalid_argument("Shift amount cannot be negative");
    }
    
    // Если сдвиг на 0, ничего не делаем
    if (n == 0) return *this;
    
    // Если сдвиг больше или равен размеру массива, сбрасываем все биты
    if (n >= num_bits_) {
        reset();  // Сбрасываем все биты
        return *this;
    }
    
    // Выполняем сдвиг, начиная с младших битов
    for (int i = 0; i < num_bits_ - n; ++i) {
        set(i, (*this)[i + n]);  // Копируем бит из позиции i+n в позицию i
    }
    
    // Заполняем старшие n битов нулями
    for (int i = num_bits_ - n; i < num_bits_; ++i) {
        set(i, false);
    }
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Битовый сдвиг влево (создает новый объект)
BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);  // Создаем копию текущего объекта
    result <<= n;            // Применяем сдвиг к копии
    return result;           // Возвращаем результат
}

// Битовый сдвиг вправо (создает новый объект)
BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);  // Создаем копию текущего объекта
    result >>= n;            // Применяем сдвиг к копии
    return result;           // Возвращаем результат
}

// Установка бита по индексу
BitArray& BitArray::set(int n, bool val) {
    // Проверяем корректность индекса
    validate_index(n);
    
    // Вычисляем индекс блока и позицию бита в блоке
    int block_index = n / BITS_PER_LONG;
    int bit_index = n % BITS_PER_LONG;
    
    // Если нужно установить бит в true
    if (val) {
        // Устанавливаем бит с помощью операции ИЛИ
        data_[block_index] |= (1UL << bit_index);
    } else {
        // Сбрасываем бит с помощью операции И с инвертированной маской
        data_[block_index] &= ~(1UL << bit_index);
    }
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Установка всех битов в true
BitArray& BitArray::set() {
    // Для каждого блока устанавливаем все биты в 1
    for (auto& block : data_) {
        block = ~0UL;  // ~0UL дает все единицы для unsigned long
    }
    
    // Обрезаем неиспользуемые биты в последнем блоке
    trim_last_block();
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Сброс конкретного бита в false
BitArray& BitArray::reset(int n) {
    return set(n, false);  // Используем метод set с значением false
}

// Сброс всех битов в false
BitArray& BitArray::reset() {
    // Для каждого блока устанавливаем все биты в 0
    for (auto& block : data_) {
        block = 0UL;
    }
    
    return *this;  // Возвращаем ссылку на текущий объект
}

// Проверка, есть ли хотя бы один бит true
bool BitArray::any() const {
    // Проверяем каждый блок
    for (auto block : data_) {
        if (block != 0) return true;  // Если блок не нулевой, есть хотя бы один true
    }
    return false;  // Все блоки нулевые
}

// Проверка, все ли биты false
bool BitArray::none() const {
    return !any();  // Обратное к any()
}

// Побитовая инверсия
BitArray BitArray::operator~() const {
    BitArray result(*this);  // Создаем копию текущего объекта
    
    // Инвертируем каждый блок
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = ~data_[i];
    }
    
    // Обрезаем неиспользуемые биты в последнем блоке
    result.trim_last_block();
    
    return result;  // Возвращаем инвертированную копию
}

// Подсчет единичных битов
int BitArray::count() const {
    int count = 0;  // Инициализируем счетчик
    
    // Для каждого блока используем std::bitset для подсчета единиц
    for (auto block : data_) {
        // std::bitset<BITS_PER_LONG>(block) создает битсет из блока,
        // .count() возвращает количество единичных битов
        count += std::bitset<BITS_PER_LONG>(block).count();
    }
    
    return count;  // Возвращаем общее количество
}

// Доступ к биту по индексу (только чтение)
bool BitArray::operator[](int i) const {
    // Проверяем корректность индекса
    validate_index(i);
    
    // Вычисляем индекс блока и позицию бита в блоке
    int block_index = i / BITS_PER_LONG;
    int bit_index = i % BITS_PER_LONG;
    
    // Извлекаем бит: сдвигаем блок вправо на bit_index позиций и берем младший бит
    return (data_[block_index] >> bit_index) & 1;
}

// Получение количества битов
int BitArray::size() const {
    return num_bits_;  // Возвращаем количество битов
}

// Проверка на пустоту
bool BitArray::empty() const {
    return num_bits_ == 0;  // Массив пуст, если количество битов равно 0
}

// Преобразование в строку
std::string BitArray::to_string() const {
    std::string result;  // Создаем пустую строку
    
    // Для каждого бита добавляем '0' или '1' в строку
    for (int i = 0; i < num_bits_; ++i) {
        result += ((*this)[i] ? '1' : '0');
    }
    
    return result;  // Возвращаем строковое представление
}

// Проверка корректности индекса
void BitArray::validate_index(int n) const {
    // Если индекс отрицательный или больше/равен размеру, выбрасываем исключение
    if (n < 0 || n >= num_bits_) {
        throw std::out_of_range("Bit index out of range");
    }
}

// Проверка совпадения размеров массивов
void BitArray::validate_size(const BitArray& b) const {
    // Если размеры не совпадают, выбрасываем исключение
    if (num_bits_ != b.num_bits_) {
        throw std::invalid_argument("BitArrays must have the same size");
    }
}

// Обрезание неиспользуемых битов в последнем блоке
void BitArray::trim_last_block() {
    // Если вектор пуст, ничего не делаем
    if (data_.empty()) return;
    
    // Вычисляем количество используемых битов в последнем блоке
    int bits_in_last_block = num_bits_ % BITS_PER_LONG;
    
    // Если последний блок используется не полностью
    if (bits_in_last_block != 0) {
        // Создаем маску для используемых битов: (1 << bits_in_last_block) - 1
        // Например, для 5 битов: 00011111
        unsigned long mask = (1UL << bits_in_last_block) - 1;
        
        // Применяем маску к последнему блоку
        data_.back() &= mask;
    }
}

// Оператор сравнения на равенство 
bool operator==(const BitArray& a, const BitArray& b) {
    // Если размеры не совпадают, массивы не равны
    if (a.size() != b.size()) return false;
    
    // Проверяем каждый бит
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;  // Если биты различаются, массивы не равны
    }
    
    return true;  // Все биты совпадают
}

// Оператор сравнения на неравенство 
bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);  // Обратное к равенству
}

// Побитовое И
BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);  // Создаем копию первого операнда
    result &= b2;         // Применяем операцию И с присваиванием
    return result;     
}

// Побитовое ИЛИ 
BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);  
    result |= b2;         // Применяем операцию ИЛИ с присваиванием
    return result;       
}

// Побитовое XOR 
BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1); ы
    result ^= b2;         // Применяем операцию XOR с присваиванием
    return result;       
}