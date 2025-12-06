#include "BitArray.h"
#include <algorithm>
#include <bitset>

BitArray::BitArray() : num_bits_(0) {}

BitArray::~BitArray() = default;

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

BitArray::BitArray(const BitArray& b) : data_(b.data_), num_bits_(b.num_bits_) {}

void BitArray::swap(BitArray& b) {
    std::swap(data_, b.data_);
    std::swap(num_bits_, b.num_bits_);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        BitArray temp(b);
        swap(temp);
    }
    return *this;
}

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
            set(i, true);
        }
    }
    
    if (num_bits > old_num_bits && value) {
        for (int i = old_num_bits; i < num_bits; ++i) {
            set(i, true);
        }
    }
    
    trim_last_block();
}

void BitArray::clear() {
    data_.clear();
    num_bits_ = 0;
}

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

BitArray& BitArray::operator&=(const BitArray& b) {
    validate_size(b);
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] &= b.data_[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    validate_size(b);
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] |= b.data_[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    validate_size(b);
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] ^= b.data_[i];
    }
    return *this;
}

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
        set(i, (*this)[i - n]);
    }
    
    for (int i = 0; i < n; ++i) {
        set(i, false);
    }
    
    return *this;
}

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
        set(i, (*this)[i + n]);
    }
    
    for (int i = num_bits_ - n; i < num_bits_; ++i) {
        set(i, false);
    }
    
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::set(int n, bool val) {
    validate_index(n);
    int block_index = n / BITS_PER_LONG;
    int bit_index = n % BITS_PER_LONG;
    
    if (val) {
        data_[block_index] |= (1UL << bit_index);
    } else {
        data_[block_index] &= ~(1UL << bit_index);
    }
    return *this;
}

BitArray& BitArray::set() {
    for (auto& block : data_) {
        block = ~0UL;
    }
    trim_last_block();
    return *this;
}

BitArray& BitArray::reset(int n) {
    return set(n, false);
}

BitArray& BitArray::reset() {
    for (auto& block : data_) {
        block = 0UL;
    }
    return *this;
}

bool BitArray::any() const {
    for (auto block : data_) {
        if (block != 0) return true;
    }
    return false;
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray result(*this);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = ~data_[i];
    }
    result.trim_last_block();
    return result;
}

int BitArray::count() const {
    int count = 0;
    for (auto block : data_) {
        count += std::bitset<BITS_PER_LONG>(block).count();
    }
    return count;
}

bool BitArray::operator[](int i) const {
    validate_index(i);
    int block_index = i / BITS_PER_LONG;
    int bit_index = i % BITS_PER_LONG;
    return (data_[block_index] >> bit_index) & 1;
}

int BitArray::size() const {
    return num_bits_;
}

bool BitArray::empty() const {
    return num_bits_ == 0;
}

std::string BitArray::to_string() const {
    std::string result;
    for (int i = 0; i < num_bits_; ++i) {
        result += ((*this)[i] ? '1' : '0');
    }
    return result;
}

void BitArray::validate_index(int n) const {
    if (n < 0 || n >= num_bits_) {
        throw std::out_of_range("Bit index out of range");
    }
}

void BitArray::validate_size(const BitArray& b) const {
    if (num_bits_ != b.num_bits_) {
        throw std::invalid_argument("BitArrays must have the same size");
    }
}

void BitArray::trim_last_block() {
    if (data_.empty()) return;
    
    int bits_in_last_block = num_bits_ % BITS_PER_LONG;
    if (bits_in_last_block != 0) {
        unsigned long mask = (1UL << bits_in_last_block) - 1;
        data_.back() &= mask;
    }
}

bool operator==(const BitArray& a, const BitArray& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result ^= b2;
    return result;
}