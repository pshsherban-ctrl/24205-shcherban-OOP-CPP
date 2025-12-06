#include <gtest/gtest.h>
#include "BitArray.h"
#include <string>
#include <stdexcept>

TEST(BitArrayTest, DefaultConstructor) {
    BitArray b;
    EXPECT_TRUE(b.empty());
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.none());
}

TEST(BitArrayTest, ConstructorWithSize) {
    BitArray b(10);
    EXPECT_FALSE(b.empty());
    EXPECT_EQ(b.size(), 10);
    EXPECT_TRUE(b.none());
}

TEST(BitArrayTest, ConstructorWithSizeAndValue) {
    BitArray b(10, 0xFFFFFFFF);
    EXPECT_EQ(b.size(), 10);
    EXPECT_TRUE(b.any());
}

TEST(BitArrayTest, ConstructorWithInvalidSize) {
    EXPECT_THROW(BitArray(-5), std::invalid_argument);
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray original(10);
    original.set(5);
    BitArray copy(original);
    
    EXPECT_EQ(original.size(), copy.size());
    for (int i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], copy[i]);
    }
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray original(10);
    original.set(3);
    original.set(7);
    
    BitArray assigned;
    assigned = original;
    
    EXPECT_EQ(original.size(), assigned.size());
    EXPECT_EQ(original[3], assigned[3]);
    EXPECT_EQ(original[7], assigned[7]);
}

TEST(BitArrayTest, SelfAssignment) {
    BitArray b(5);
    b.set(2);
    b = b;
    EXPECT_EQ(b.size(), 5);
    EXPECT_TRUE(b[2]);
}

TEST(BitArrayTest, Swap) {
    BitArray a(5);
    a.set(0);
    BitArray b(10);
    b.set(5);
    
    int a_size = a.size();
    int b_size = b.size();
    bool a_bit0 = a[0];
    bool b_bit5 = b[5];
    
    a.swap(b);
    
    EXPECT_EQ(a.size(), b_size);
    EXPECT_EQ(b.size(), a_size);
    EXPECT_EQ(a[5], b_bit5);
    EXPECT_EQ(b[0], a_bit0);
}

TEST(BitArrayTest, OperatorBracket) {
    BitArray b(10);
    b.set(3);
    
    EXPECT_FALSE(b[0]);
    EXPECT_TRUE(b[3]);
    EXPECT_FALSE(b[9]);
}

TEST(BitArrayTest, OperatorBracketOutOfRange) {
    BitArray b(5);
    EXPECT_THROW(b[-1], std::out_of_range);
    EXPECT_THROW(b[5], std::out_of_range);
    EXPECT_THROW(b[100], std::out_of_range);
}

TEST(BitArrayTest, SetSingleBit) {
    BitArray b(10);
    b.set(5);
    EXPECT_TRUE(b[5]);
    EXPECT_FALSE(b[4]);
    EXPECT_FALSE(b[6]);
}

TEST(BitArrayTest, SetSingleBitWithValue) {
    BitArray b(10);
    b.set(5, true);
    EXPECT_TRUE(b[5]);
    b.set(5, false);
    EXPECT_FALSE(b[5]);
}

TEST(BitArrayTest, SetAllBits) {
    BitArray b(10);
    b.set();
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(b[i]);
    }
    EXPECT_TRUE(b.any());
    EXPECT_FALSE(b.none());
}

TEST(BitArrayTest, ResetSingleBit) {
    BitArray b(10);
    b.set();
    b.reset(5);
    EXPECT_FALSE(b[5]);
    for (int i = 0; i < 10; ++i) {
        if (i != 5) {
            EXPECT_TRUE(b[i]);
        }
    }
}

TEST(BitArrayTest, ResetAllBits) {
    BitArray b(10);
    b.set();
    b.reset();
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(b[i]);
    }
    EXPECT_TRUE(b.none());
    EXPECT_FALSE(b.any());
}

TEST(BitArrayTest, BitwiseAND) {
    BitArray a(5);
    a.set(0); // 00001
    a.set(1); // 00011  
    a.set(4); // 10011
    
    BitArray b(5);
    b.set(0); // 00001
    b.set(2); // 00101
    b.set(3); // 01101
    
    a &= b;
    
    // 10011 & 01101 = 00001
    EXPECT_TRUE(a[0]);   // бит 0
    EXPECT_FALSE(a[1]);  // бит 1
    EXPECT_FALSE(a[2]);  // бит 2
    EXPECT_FALSE(a[3]);  // бит 3
    EXPECT_FALSE(a[4]);  // бит 4
}

TEST(BitArrayTest, BitwiseOR) {
    BitArray a(5);
    a.set(0);
    a.set(4);
    
    BitArray b(5);
    b.set(1);
    b.set(2);
    
    a |= b;
    
    EXPECT_TRUE(a[0]);
    EXPECT_TRUE(a[1]);
    EXPECT_TRUE(a[2]);
    EXPECT_FALSE(a[3]);
    EXPECT_TRUE(a[4]);
}

TEST(BitArrayTest, BitwiseXOR) {
    BitArray a(5);
    a.set(0);
    a.set(2);
    a.set(4);
    
    BitArray b(5);
    b.set(0);
    b.set(1);
    b.set(4);
    
    a ^= b;
    
    EXPECT_FALSE(a[0]);  // 1 ^ 1 = 0
    EXPECT_TRUE(a[1]);   // 0 ^ 1 = 1
    EXPECT_TRUE(a[2]);   // 1 ^ 0 = 1
    EXPECT_FALSE(a[3]);  // 0 ^ 0 = 0
    EXPECT_FALSE(a[4]);  // 1 ^ 1 = 0
}

TEST(BitArrayTest, BitwiseOperationsSizeMismatch) {
    BitArray a(5);
    BitArray b(10);
    EXPECT_THROW(a &= b, std::invalid_argument);
    EXPECT_THROW(a |= b, std::invalid_argument);
    EXPECT_THROW(a ^= b, std::invalid_argument);
}

TEST(BitArrayTest, LeftShift) {
    BitArray b(5);
    b.set(0);
    b.set(2);
    
    b <<= 1;
    
    EXPECT_FALSE(b[0]);
    EXPECT_TRUE(b[1]);
    EXPECT_FALSE(b[2]);
    EXPECT_TRUE(b[3]);
    EXPECT_FALSE(b[4]);
}

TEST(BitArrayTest, RightShift) {
    BitArray b(5);
    b.set(4);
    b.set(2);
    
    b >>= 1;
    
    EXPECT_FALSE(b[0]);
    EXPECT_TRUE(b[1]);
    EXPECT_FALSE(b[2]);
    EXPECT_TRUE(b[3]);
    EXPECT_FALSE(b[4]);
}

TEST(BitArrayTest, LargeShift) {
    BitArray b(5);
    b.set();
    b <<= 10;
    EXPECT_TRUE(b.none());
    
    b.set();
    b >>= 10;
    EXPECT_TRUE(b.none());
}

TEST(BitArrayTest, ShiftWithNegative) {
    BitArray b(5);
    EXPECT_THROW(b <<= -1, std::invalid_argument);
    EXPECT_THROW(b >>= -1, std::invalid_argument);
}

TEST(BitArrayTest, Count) {
    BitArray b(10);
    EXPECT_EQ(b.count(), 0);
    
    b.set(0);
    b.set(3);
    b.set(7);
    b.set(9);
    EXPECT_EQ(b.count(), 4);
}

TEST(BitArrayTest, AnyNone) {
    BitArray empty(5);
    EXPECT_TRUE(empty.none());
    EXPECT_FALSE(empty.any());
    
    BitArray some(5);
    some.set(2);
    EXPECT_FALSE(some.none());
    EXPECT_TRUE(some.any());
    
    BitArray full(5);
    full.set();
    EXPECT_FALSE(full.none());
    EXPECT_TRUE(full.any());
}

TEST(BitArrayTest, BitwiseNOT) {
    BitArray b(5);
    b.set(0);
    b.set(2);
    b.set(4);
    
    BitArray not_b = ~b;
    
    EXPECT_FALSE(not_b[0]);
    EXPECT_TRUE(not_b[1]);
    EXPECT_FALSE(not_b[2]);
    EXPECT_TRUE(not_b[3]);
    EXPECT_FALSE(not_b[4]);
}

TEST(BitArrayTest, ResizeLarger) {
    BitArray b(5);
    b.set(0);
    b.set(4);
    
    b.resize(10, true);
    
    EXPECT_EQ(b.size(), 10);
    EXPECT_TRUE(b[0]);
    EXPECT_TRUE(b[4]);
    EXPECT_TRUE(b[5]);
    EXPECT_TRUE(b[9]);
}

TEST(BitArrayTest, ResizeSmaller) {
    BitArray b(10);
    b.set(0);
    b.set(5);
    b.set(9);
    
    b.resize(5);
    
    EXPECT_EQ(b.size(), 5);
    EXPECT_TRUE(b[0]);
    EXPECT_THROW(b[5], std::out_of_range);
    EXPECT_THROW(b[9], std::out_of_range);
}

TEST(BitArrayTest, ResizeInvalid) {
    BitArray b(5);
    EXPECT_THROW(b.resize(-1), std::invalid_argument);
}

TEST(BitArrayTest, PushBack) {
    BitArray b;
    b.push_back(true);
    EXPECT_EQ(b.size(), 1);
    EXPECT_TRUE(b[0]);
    
    b.push_back(false);
    EXPECT_EQ(b.size(), 2);
    EXPECT_TRUE(b[0]);
    EXPECT_FALSE(b[1]);
    
    b.push_back(true);
    EXPECT_EQ(b.size(), 3);
    EXPECT_TRUE(b[2]);
}

TEST(BitArrayTest, Clear) {
    BitArray b(10);
    b.set();
    b.clear();
    EXPECT_TRUE(b.empty());
    EXPECT_EQ(b.size(), 0);
}

TEST(BitArrayTest, ToString) {
    BitArray b(5);
    b.set(0);
    b.set(2);
    b.set(4);
    EXPECT_EQ(b.to_string(), "10101");
}

TEST(BitArrayTest, ExternalOperators) {
    BitArray a(5);
    a.set(0);
    a.set(1);
    a.set(4);
    
    BitArray b(5);
    b.set(0);
    b.set(2);
    b.set(3);
    
    BitArray and_result = a & b;
    EXPECT_TRUE(and_result[0]);
    EXPECT_FALSE(and_result[1]);
    EXPECT_FALSE(and_result[2]);
    EXPECT_FALSE(and_result[3]);
    EXPECT_FALSE(and_result[4]);
    
    BitArray or_result = a | b;
    EXPECT_TRUE(or_result[0]);
    EXPECT_TRUE(or_result[1]);
    EXPECT_TRUE(or_result[2]);
    EXPECT_TRUE(or_result[3]);
    EXPECT_TRUE(or_result[4]);
    
    BitArray xor_result = a ^ b;
    EXPECT_FALSE(xor_result[0]);
    EXPECT_TRUE(xor_result[1]);
    EXPECT_TRUE(xor_result[2]);
    EXPECT_TRUE(xor_result[3]);
    EXPECT_TRUE(xor_result[4]);
}

TEST(BitArrayTest, EqualityOperators) {
    BitArray a(5);
    a.set(1);
    a.set(3);
    
    BitArray b(5);
    b.set(1);
    b.set(3);
    
    BitArray c(5);
    c.set(1);
    c.set(2);
    
    BitArray d(10);
    d.set(1);
    d.set(3);
    
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a != d);
}

TEST(BitArrayTest, LargeArray) {
    const int SIZE = 10000;
    BitArray large(SIZE);
    
    for (int i = 0; i < SIZE; i += 10) {
        large.set(i);
    }
    
    EXPECT_EQ(large.count(), SIZE / 10);
    EXPECT_TRUE(large.any());
    
    large <<= 5;
    EXPECT_EQ(large.count(), SIZE / 10);
}

TEST(BitArrayTest, EdgeCases) {
    BitArray empty;
    EXPECT_NO_THROW(empty.resize(0));
    EXPECT_NO_THROW(empty.clear());
    
    BitArray single(1);
    single.set(0);
    EXPECT_TRUE(single[0]);
    single.reset(0);
    EXPECT_FALSE(single[0]);
    
    BitArray boundary(1);
    boundary.push_back(true);
    EXPECT_EQ(boundary.size(), 2);
    EXPECT_TRUE(boundary[1]);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}