#include "BitArray.h"
#include <algorithm>
#include <bitset>

// Реализация методов BitProxy

// Конструктор BitProxy (приватный, доступен только для BitArray)
BitArray::BitProxy::BitProxy(BitArray& bit_array, int index) 
    : bit_array_(bit_array), index_(index) {}

// Оператор присваивания bool для BitProxy
BitArray::BitProxy& BitArray::BitProxy::operator=(bool val) {
    bit_array_.set_bit_unchecked(index_, val);  // Устанавливаем бит без проверки
    return *this;
}

// Оператор присваивания BitProxy для BitProxy (позволяет ba[i] = ba[j])
BitArray::BitProxy& BitArray::BitProxy::operator=(const BitProxy& other) {
    bool val = static_cast<bool>(other);  // Получаем значение из другого BitProxy
    bit_array_.set_bit_unchecked(index_, val);  // Устанавливаем это значение
    return *this;
}

// Оператор преобразования BitProxy в bool (для чтения)
BitArray::BitProxy::operator bool() const {
    return bit_array_.get_bit_unchecked(index_);  // Получаем значение бита без проверки
}

// Реализация методов BitArray

// Конструктор по умолчанию
BitArray::BitArray() : num_bits_(0) {}

// Деструктор (используется дефолтная реализация)
BitArray::~BitArray() = default;

// Конструктор с параметрами
BitArray::BitArray(int num_bits, unsigned long value) : num_bits_(num_bits) {
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative");
    }
    
    int blocks_needed = (num_bits + BITS_PER_LONG - 1) / BITS_PER_LONG;
    data_.resize(blocks_needed, 0);
    
    if (blocks_needed > 0) {
        data_[0] = value;
        trim_last_block();
    }
}

// Конструктор копирования
BitArray::BitArray(const BitArray& b) : data_(b.data_), num_bits_(b.num_bits_) {}               //в ImplicitCopyOnInitialization вызывается неявно

// Обмен содержимым двух объектов BitArray
void BitArray::swap(BitArray& b) {
    std::swap(data_, b.data_);
    std::swap(num_bits_, b.num_bits_);
}

// Оператор присваивания (используем идиому copy-and-swap)
BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        BitArray temp(b);                                           //неявное копирование (создается временная копия)
        swap(temp);
    }
    return *this;
}

// Изменение размера массива
void BitArray::resize(int num_bits, bool value) {
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative");
    }
    
    if (num_bits == num_bits_) return;
    
    int old_num_bits = num_bits_;
    int old_blocks = data_.size();                                             
    int new_blocks = (num_bits + BITS_PER_LONG - 1) / BITS_PER_LONG;
    
    std::vector<unsigned long> old_data = data_;
    data_.resize(new_blocks, 0);
    num_bits_ = num_bits;
    
    int bits_to_copy = std::min(old_num_bits, num_bits);
    for (int i = 0; i < bits_to_copy; ++i) {
        int old_block = i / BITS_PER_LONG;
        int old_bit = i % BITS_PER_LONG;
        if (old_block < old_data.size() && (old_data[old_block] & (1UL << old_bit))) {
            set_bit_unchecked(i, true);
        }
    }
    
    if (num_bits > old_num_bits && value) {
        for (int i = old_num_bits; i < num_bits; ++i) {
            set_bit_unchecked(i, true);
        }
    }
    
    trim_last_block();
}

// Очистка массива
void BitArray::clear() {
    data_.clear();
    num_bits_ = 0;
}

// Добавление бита в конец массива
void BitArray::push_back(bool bit) {
    int block_index = num_bits_ / BITS_PER_LONG;
    int bit_index = num_bits_ % BITS_PER_LONG;
    
    if (bit_index == 0) {
        data_.push_back(0);
    }
    
    if (bit) {
        data_[block_index] |= (1UL << bit_index);
    }
    num_bits_++;
}

// Побитовое И с присваиванием
BitArray& BitArray::operator&=(const BitArray& b) {
    validate_size(b);
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] &= b.data_[i];
    }
    return *this;
}

// Побитовое ИЛИ с присваиванием
BitArray& BitArray::operator|=(const BitArray& b) {
    validate_size(b);
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] |= b.data_[i];
    }
    return *this;
}

// Побитовое XOR с присваиванием
BitArray& BitArray::operator^=(const BitArray& b) {
    validate_size(b);
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] ^= b.data_[i];
    }
    return *this;
}

// Битовый сдвиг влево с присваиванием
BitArray& BitArray::operator<<=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Shift amount cannot be negative");
    }
    
    if (n == 0) return *this;
    
    if (n >= num_bits_) {
        reset();
        return *this;
    }
    
    for (int i = num_bits_ - 1; i >= n; --i) {
        set_bit_unchecked(i, (*this)[i - n]);
    }
    
    for (int i = 0; i < n; ++i) {
        set_bit_unchecked(i, false);
    }
    
    return *this;
}

// Битовый сдвиг вправо с присваиванием
BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Shift amount cannot be negative");
    }
    
    if (n == 0) return *this;
    
    if (n >= num_bits_) {
        reset();
        return *this;
    }
    
    for (int i = 0; i < num_bits_ - n; ++i) {
        set_bit_unchecked(i, (*this)[i + n]);
    }
    
    for (int i = num_bits_ - n; i < num_bits_; ++i) {
        set_bit_unchecked(i, false);
    }
    
    return *this;
}

// Битовый сдвиг влево (создает новый объект)
BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);                             //неявное копирование при возврате (создается полная копи всего объекта, копируетс вектор данных и все метаданные)
    result <<= n;
    return result;
}

// Битовый сдвиг вправо (создает новый объект)
BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);                            
    result >>= n;
    return result;                                      
}

// Установка бита по индексу
BitArray& BitArray::set(int n, bool val) {
    validate_index(n);
    set_bit_unchecked(n, val);
    return *this;
}

// Установка всех битов в true
BitArray& BitArray::set() {
    for (auto& block : data_) {
        block = ~0UL;
    }
    trim_last_block();
    return *this;
}

// Сброс конкретного бита в false
BitArray& BitArray::reset(int n) {
    return set(n, false);
}

// Сброс всех битов в false
BitArray& BitArray::reset() {
    for (auto& block : data_) {
        block = 0UL;
    }
    return *this;
}

// Проверка, есть ли хотя бы один бит true
bool BitArray::any() const {
    for (auto block : data_) {
        if (block != 0) return true;
    }
    return false;
}

// Проверка, все ли биты false
bool BitArray::none() const {
    return !any();
}

// Побитовая инверсия
BitArray BitArray::operator~() const {
    BitArray result(*this);                                                
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = ~data_[i];
    }
    result.trim_last_block();
    return result;
}

// Подсчет единичных битов
int BitArray::count() const {
    int count = 0;
    for (auto block : data_) {
        count += std::bitset<BITS_PER_LONG>(block).count();                 // неявное копирование (создается временный объект std::bitset для каждого блока, что является неявным копированием данных)
    }
    return count;
}

// Доступ к биту по индексу (ТОЛЬКО ДЛЯ ЧТЕНИЯ)
bool BitArray::operator[](int i) const {
    validate_index(i);
    return get_bit_unchecked(i);
}

// Доступ к биту по индексу (ДЛЯ ЧТЕНИЯ И ЗАПИСИ)
BitArray::BitProxy BitArray::operator[](int i) {
    validate_index(i);
    return BitProxy(*this, i);
}

// Получение количества битов
int BitArray::size() const {
    return num_bits_;
}

// Проверка на пустоту
bool BitArray::empty() const {
    return num_bits_ == 0;
}

// Преобразование в строку
std::string BitArray::to_string() const {
    std::string result;
    for (int i = 0; i < num_bits_; ++i) {
        result += ((*this)[i] ? '1' : '0');
    }
    return result;
}

// Проверка корректности индекса
void BitArray::validate_index(int n) const {
    if (n < 0 || n >= num_bits_) {
        throw std::out_of_range("Bit index out of range");
    }
}

// Проверка совпадения размеров массивов
void BitArray::validate_size(const BitArray& b) const {
    if (num_bits_ != b.num_bits_) {
        throw std::invalid_argument("BitArrays must have the same size");
    }
}

// Обрезание неиспользуемых битов в последнем блоке
void BitArray::trim_last_block() {
    if (data_.empty()) return;
    
    int bits_in_last_block = num_bits_ % BITS_PER_LONG;
    if (bits_in_last_block != 0) {
        unsigned long mask = (1UL << bits_in_last_block) - 1;
        data_.back() &= mask;
    }
}

// Установка бита без проверки индекса
void BitArray::set_bit_unchecked(int n, bool val) {
    int block_index = n / BITS_PER_LONG;
    int bit_index = n % BITS_PER_LONG;
    
    if (val) {
        data_[block_index] |= (1UL << bit_index);
    } else {
        data_[block_index] &= ~(1UL << bit_index);
    }
}

// Получение бита без проверки индекса
bool BitArray::get_bit_unchecked(int n) const {
    int block_index = n / BITS_PER_LONG;
    int bit_index = n % BITS_PER_LONG;
    return (data_[block_index] >> bit_index) & 1;
}

// Оператор сравнения на равенство (внешняя функция)
bool operator==(const BitArray& a, const BitArray& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// Оператор сравнения на неравенство (внешняя функция)
bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

// Побитовое И (внешняя функция)
BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);                                                        //неявное копирование при возврате (создаетсяполная копи всего объекта, копируетс вектор данных и все метаданные)
    result &= b2;
    return result;
}

// Побитовое ИЛИ (внешняя функция)
BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);                                                    
    result |= b2;
    return result;
}

// Побитовое XOR (внешняя функция)
BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);                                                    
    result ^= b2;
    return result;
}