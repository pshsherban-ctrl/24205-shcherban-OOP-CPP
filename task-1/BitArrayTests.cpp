#include <gtest/gtest.h>

#include "BitArray.h"

#include <string>
#include <stdexcept>

// Тест конструктора по умолчанию
TEST(BitArrayTest, DefaultConstructor) {
    BitArray b;                       // Создаем объект с конструктором по умолчанию
    EXPECT_TRUE(b.empty());           // Проверяем, что массив пуст
    EXPECT_EQ(b.size(), 0);           // Проверяем, что размер равен 0
    EXPECT_TRUE(b.none());            // Проверяем, что все биты false
}

// Тест конструктора с размером
TEST(BitArrayTest, ConstructorWithSize) {
    BitArray b(10);                   // Создаем массив из 10 битов
    EXPECT_FALSE(b.empty());          // Проверяем, что массив не пуст
    EXPECT_EQ(b.size(), 10);          // Проверяем, что размер равен 10
    EXPECT_TRUE(b.none());            // Проверяем, что все биты false (по умолчанию)
}

// Тест конструктора с размером и начальным значением
TEST(BitArrayTest, ConstructorWithSizeAndValue) {
    BitArray b(10, 0xFFFFFFFF);       // Создаем массив из 10 битов со значением 0xFFFFFFFF
    EXPECT_EQ(b.size(), 10);          // Проверяем размер
    EXPECT_TRUE(b.any());             // Проверяем, что есть хотя бы один true
}

// Тест конструктора с некорректным размером (отрицательным)
TEST(BitArrayTest, ConstructorWithInvalidSize) {
    EXPECT_THROW(BitArray(-5), std::invalid_argument);  // Ожидаем исключение
}

// Тест конструктора копирования
TEST(BitArrayTest, CopyConstructor) {
    BitArray original(10);            // Создаем оригинальный массив
    original.set(5);                  // Устанавливаем бит с индексом 5
    
    BitArray copy(original);          // Создаем копию
    
    EXPECT_EQ(original.size(), copy.size());  // Проверяем совпадение размеров
    
    // Проверяем, что все биты совпадают
    for (int i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], copy[i]);
    }
}

// Тест оператора присваивания
TEST(BitArrayTest, AssignmentOperator) {
    BitArray original(10);            // Создаем оригинальный массив
    original.set(3);                  // Устанавливаем биты
    original.set(7);
    
    BitArray assigned;                // Создаем пустой массив
    assigned = original;              // Присваиваем
    
    EXPECT_EQ(original.size(), assigned.size());  // Проверяем совпадение размеров
    EXPECT_EQ(original[3], assigned[3]);          // Проверяем совпадение битов
    EXPECT_EQ(original[7], assigned[7]);
}

// Тест самоприсваивания
TEST(BitArrayTest, SelfAssignment) {
    BitArray b(5);                    // Создаем массив
    b.set(2);                         // Устанавливаем бит
    b = b;                            // Самоприсваивание
    
    EXPECT_EQ(b.size(), 5);           // Проверяем, что размер не изменился
    EXPECT_TRUE(b[2]);                // Проверяем, что бит остался установленным
}

// Тест метода swap
TEST(BitArrayTest, Swap) {
    BitArray a(5);                    // Создаем первый массив
    a.set(0);                         // Устанавливаем бит 0
    
    BitArray b(10);                   // Создаем второй массив
    b.set(5);                         // Устанавливаем бит 5
    
    int a_size = a.size();            // Сохраняем размеры
    int b_size = b.size();
    bool a_bit0 = a[0];               // Сохраняем значения битов
    bool b_bit5 = b[5];
    
    a.swap(b);                        // Обмениваем массивы
    
    EXPECT_EQ(a.size(), b_size);      // Проверяем обмен размеров
    EXPECT_EQ(b.size(), a_size);
    EXPECT_EQ(a[5], b_bit5);          // Проверяем обмен содержимого
    EXPECT_EQ(b[0], a_bit0);
}

// Тест оператора [] (доступ к битам)
TEST(BitArrayTest, OperatorBracket) {
    BitArray b(10);                   // Создаем массив
    b.set(3);                         // Устанавливаем бит 3
    
    EXPECT_FALSE(b[0]);               // Проверяем, что бит 0 не установлен
    EXPECT_TRUE(b[3]);                // Проверяем, что бит 3 установлен
    EXPECT_FALSE(b[9]);               // Проверяем, что бит 9 не установлен
}

// Тест оператора [] с некорректными индексами
TEST(BitArrayTest, OperatorBracketOutOfRange) {
    BitArray b(5);                    // Создаем массив из 5 битов
    
    EXPECT_THROW(b[-1], std::out_of_range);   // Отрицательный индекс - исключение
    EXPECT_THROW(b[5], std::out_of_range);    // Индекс равен размеру - исключение
    EXPECT_THROW(b[100], std::out_of_range);  // Индекс больше размера - исключение
}

// Тест установки одиночного бита
TEST(BitArrayTest, SetSingleBit) {
    BitArray b(10);                   // Создаем массив
    b.set(5);                         // Устанавливаем бит 5
    
    EXPECT_TRUE(b[5]);                // Проверяем, что бит 5 установлен
    EXPECT_FALSE(b[4]);               // Проверяем соседние биты
    EXPECT_FALSE(b[6]);
}

// Тест установки одиночного бита с явным значением
TEST(BitArrayTest, SetSingleBitWithValue) {
    BitArray b(10);                   // Создаем массив
    b.set(5, true);                   // Устанавливаем бит 5 в true
    EXPECT_TRUE(b[5]);                // Проверяем
    
    b.set(5, false);                  // Устанавливаем бит 5 в false
    EXPECT_FALSE(b[5]);               // Проверяем
}

// Тест установки всех битов
TEST(BitArrayTest, SetAllBits) {
    BitArray b(10);                   // Создаем массив
    b.set();                          // Устанавливаем все биты в true
    
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(b[i]);            // Проверяем каждый бит
    }
    
    EXPECT_TRUE(b.any());             // Проверяем any()
    EXPECT_FALSE(b.none());           // Проверяем none()
}

// Тест сброса одиночного бита
TEST(BitArrayTest, ResetSingleBit) {
    BitArray b(10);                   // Создаем массив
    b.set();                          // Устанавливаем все биты
    b.reset(5);                       // Сбрасываем бит 5
    
    EXPECT_FALSE(b[5]);               // Проверяем, что бит 5 сброшен
    
    for (int i = 0; i < 10; ++i) {
        if (i != 5) {
            EXPECT_TRUE(b[i]);        // Проверяем, что остальные биты остались установленными
        }
    }
}

// Тест сброса всех битов
TEST(BitArrayTest, ResetAllBits) {
    BitArray b(10);                   // Создаем массив
    b.set();                          // Устанавливаем все биты
    b.reset();                        // Сбрасываем все биты
    
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(b[i]);           // Проверяем каждый бит
    }
    
    EXPECT_TRUE(b.none());            // Проверяем none()
    EXPECT_FALSE(b.any());            // Проверяем any()
}

// Тест побитового И
TEST(BitArrayTest, BitwiseAND) {
    BitArray a(5);                    // Создаем первый массив
    a.set(0);                         // 00001 (бит 0)
    a.set(1);                         // 00011 (биты 0,1)
    a.set(4);                         // 10011 (биты 0,1,4)
    
    BitArray b(5);                    // Создаем второй массив
    b.set(0);                         // 00001 (бит 0)
    b.set(2);                         // 00101 (биты 0,2)
    b.set(3);                         // 01101 (биты 0,2,3)
    
    a &= b;                           // Применяем операцию И
    
    // 10011 & 01101 = 00001 (только бит 0)
    EXPECT_TRUE(a[0]);                // Бит 0 должен быть true
    EXPECT_FALSE(a[1]);               // Остальные биты должны быть false
    EXPECT_FALSE(a[2]);
    EXPECT_FALSE(a[3]);
    EXPECT_FALSE(a[4]);
}

// Тест побитового ИЛИ
TEST(BitArrayTest, BitwiseOR) {
    BitArray a(5);                    // Создаем первый массив
    a.set(0);                         // Бит 0
    a.set(4);                         // Бит 4
    
    BitArray b(5);                    // Создаем второй массив
    b.set(1);                         // Бит 1
    b.set(2);                         // Бит 2
    
    a |= b;                           // Применяем операцию ИЛИ
    
    // Должны быть установлены биты 0,1,2,4
    EXPECT_TRUE(a[0]);
    EXPECT_TRUE(a[1]);
    EXPECT_TRUE(a[2]);
    EXPECT_FALSE(a[3]);               // Бит 3 не установлен
    EXPECT_TRUE(a[4]);
}

// Тест побитового XOR
TEST(BitArrayTest, BitwiseXOR) {
    BitArray a(5);                    // Создаем первый массив
    a.set(0);                         // Бит 0
    a.set(2);                         // Бит 2
    a.set(4);                         // Бит 4
    
    BitArray b(5);                    // Создаем второй массив
    b.set(0);                         // Бит 0
    b.set(1);                         // Бит 1
    b.set(4);                         // Бит 4
    
    a ^= b;                           // Применяем операцию XOR
    
    // XOR: биты, которые разные в a и b, становятся 1
    // a: 10101 (биты 0,2,4)
    // b: 10011 (биты 0,1,4)
    // a^b: 00110 (биты 1,2)
    EXPECT_FALSE(a[0]);               // 1 ^ 1 = 0
    EXPECT_TRUE(a[1]);                // 0 ^ 1 = 1
    EXPECT_TRUE(a[2]);                // 1 ^ 0 = 1
    EXPECT_FALSE(a[3]);               // 0 ^ 0 = 0
    EXPECT_FALSE(a[4]);               // 1 ^ 1 = 0
}

// Тест побитовых операций с разными размерами (должны выбрасывать исключение)
TEST(BitArrayTest, BitwiseOperationsSizeMismatch) {
    BitArray a(5);                    // Массив из 5 битов
    BitArray b(10);                   // Массив из 10 битов
    
    EXPECT_THROW(a &= b, std::invalid_argument);  // Ожидаем исключение
    EXPECT_THROW(a |= b, std::invalid_argument);
    EXPECT_THROW(a ^= b, std::invalid_argument);
}

// Тест сдвига влево
TEST(BitArrayTest, LeftShift) {
    BitArray b(5);                    // Создаем массив из 5 битов
    b.set(0);                         // Устанавливаем бит 0
    b.set(2);                         // Устанавливаем бит 2
    
    b <<= 1;                          // Сдвигаем влево на 1 позицию
    
    // Было: 00101 (биты 0,2)
    // После сдвига влево: 01010 (биты 1,3)
    EXPECT_FALSE(b[0]);
    EXPECT_TRUE(b[1]);
    EXPECT_FALSE(b[2]);
    EXPECT_TRUE(b[3]);
    EXPECT_FALSE(b[4]);
}

// Тест сдвига вправо
TEST(BitArrayTest, RightShift) {
    BitArray b(5);                    // Создаем массив из 5 битов
    b.set(4);                         // Устанавливаем бит 4 (старший)
    b.set(2);                         // Устанавливаем бит 2
    
    b >>= 1;                          // Сдвигаем вправо на 1 позицию
    
    // Было: 10100 (биты 2,4)
    // После сдвига вправо: 01010 (биты 1,3)
    EXPECT_FALSE(b[0]);
    EXPECT_TRUE(b[1]);
    EXPECT_FALSE(b[2]);
    EXPECT_TRUE(b[3]);
    EXPECT_FALSE(b[4]);
}

// Тест большого сдвига (больше размера массива)
TEST(BitArrayTest, LargeShift) {
    BitArray b(5);                    // Создаем массив из 5 битов
    b.set();                          // Устанавливаем все биты
    
    b <<= 10;                         // Сдвигаем влево на 10 позиций (больше размера)
    EXPECT_TRUE(b.none());            // Все биты должны быть сброшены
    
    b.set();                          // Снова устанавливаем все биты
    b >>= 10;                         // Сдвигаем вправо на 10 позиций
    EXPECT_TRUE(b.none());            // Все биты должны быть сброшены
}

// Тест сдвига с отрицательным аргументом (должен выбрасывать исключение)
TEST(BitArrayTest, ShiftWithNegative) {
    BitArray b(5);                    // Создаем массив
    
    EXPECT_THROW(b <<= -1, std::invalid_argument);  // Ожидаем исключение
    EXPECT_THROW(b >>= -1, std::invalid_argument);
}

// Тест подсчета единичных битов
TEST(BitArrayTest, Count) {
    BitArray b(10);                   // Создаем массив из 10 битов
    EXPECT_EQ(b.count(), 0);          // Изначально все биты 0, count=0
    
    b.set(0);                         // Устанавливаем биты
    b.set(3);
    b.set(7);
    b.set(9);
    
    EXPECT_EQ(b.count(), 4);          // Должно быть 4 установленных бита
}

// Тесты методов any() и none()
TEST(BitArrayTest, AnyNone) {
    BitArray empty(5);                // Создаем пустой массив (все биты 0)
    EXPECT_TRUE(empty.none());        // none() должен вернуть true
    EXPECT_FALSE(empty.any());        // any() должен вернуть false
    
    BitArray some(5);                 // Создаем массив
    some.set(2);                      // Устанавливаем один бит
    EXPECT_FALSE(some.none());        // none() должен вернуть false
    EXPECT_TRUE(some.any());          // any() должен вернуть true
    
    BitArray full(5);                 // Создаем массив
    full.set();                       // Устанавливаем все биты
    EXPECT_FALSE(full.none());        // none() должен вернуть false
    EXPECT_TRUE(full.any());          // any() должен вернуть true
}

// Тест побитовой инверсии
TEST(BitArrayTest, BitwiseNOT) {
    BitArray b(5);                    // Создаем массив
    b.set(0);                         // Устанавливаем биты 0,2,4
    b.set(2);
    b.set(4);
    
    BitArray not_b = ~b;              // Инвертируем
    
    // Исходный: 10101 (биты 0,2,4)
    // Инвертированный: 01010 (биты 1,3)
    EXPECT_FALSE(not_b[0]);
    EXPECT_TRUE(not_b[1]);
    EXPECT_FALSE(not_b[2]);
    EXPECT_TRUE(not_b[3]);
    EXPECT_FALSE(not_b[4]);
}

// Тест увеличения размера массива
TEST(BitArrayTest, ResizeLarger) {
    BitArray b(5);                    // Создаем массив из 5 битов
    b.set(0);                         // Устанавливаем бит 0
    b.set(4);                         // Устанавливаем бит 4
    
    b.resize(10, true);               // Увеличиваем размер до 10, новые биты = true
    
    EXPECT_EQ(b.size(), 10);          // Проверяем новый размер
    EXPECT_TRUE(b[0]);                // Старые биты должны сохраниться
    EXPECT_TRUE(b[4]);
    EXPECT_TRUE(b[5]);                // Новые биты должны быть true
    EXPECT_TRUE(b[9]);
}

// Тест уменьшения размера массива
TEST(BitArrayTest, ResizeSmaller) {
    BitArray b(10);                   // Создаем массив из 10 битов
    b.set(0);                         // Устанавливаем биты
    b.set(5);
    b.set(9);
    
    b.resize(5);                      // Уменьшаем размер до 5
    
    EXPECT_EQ(b.size(), 5);           // Проверяем новый размер
    EXPECT_TRUE(b[0]);                // Бит 0 должен сохраниться
    
    // Биты 5 и 9 теперь за пределами массива - должен быть исключение
    EXPECT_THROW(b[5], std::out_of_range);
    EXPECT_THROW(b[9], std::out_of_range);
}

// Тест изменения размера с некорректным аргументом
TEST(BitArrayTest, ResizeInvalid) {
    BitArray b(5);                    // Создаем массив
    
    EXPECT_THROW(b.resize(-1), std::invalid_argument);  // Ожидаем исключение
}

// Тест добавления битов в конец
TEST(BitArrayTest, PushBack) {
    BitArray b;                       // Создаем пустой массив
    
    b.push_back(true);                // Добавляем true
    EXPECT_EQ(b.size(), 1);           // Размер должен стать 1
    EXPECT_TRUE(b[0]);                // Бит 0 должен быть true
    
    b.push_back(false);               // Добавляем false
    EXPECT_EQ(b.size(), 2);           // Размер должен стать 2
    EXPECT_TRUE(b[0]);                // Бит 0 должен остаться true
    EXPECT_FALSE(b[1]);               // Бит 1 должен быть false
    
    b.push_back(true);                // Добавляем true
    EXPECT_EQ(b.size(), 3);           // Размер должен стать 3
    EXPECT_TRUE(b[2]);                // Бит 2 должен быть true
}

// Тест очистки массива
TEST(BitArrayTest, Clear) {
    BitArray b(10);                   // Создаем массив
    b.set();                          // Устанавливаем все биты
    b.clear();                        // Очищаем
    
    EXPECT_TRUE(b.empty());           // Массив должен быть пустым
    EXPECT_EQ(b.size(), 0);           // Размер должен быть 0
}

// Тест преобразования в строку
TEST(BitArrayTest, ToString) {
    BitArray b(5);                    // Создаем массив из 5 битов
    b.set(0);                         // Устанавливаем биты 0,2,4
    b.set(2);
    b.set(4);
    
    // Должно получиться "10101" (бит 0 - младший, идет первым в строке)
    EXPECT_EQ(b.to_string(), "10101");
}

// Тест внешних операторов (и, или, xor)
TEST(BitArrayTest, ExternalOperators) {
    BitArray a(5);                    // Создаем первый массив
    a.set(0);                         // Бит 0
    a.set(1);                         // Бит 1
    a.set(4);                         // Бит 4
    
    BitArray b(5);                    // Создаем второй массив
    b.set(0);                         // Бит 0
    b.set(2);                         // Бит 2
    b.set(3);                         // Бит 3
    
    // Тестируем оператор & (И)
    BitArray and_result = a & b;
    // a: 10011, b: 01101 => a&b: 00001 (только бит 0)
    EXPECT_TRUE(and_result[0]);
    EXPECT_FALSE(and_result[1]);
    EXPECT_FALSE(and_result[2]);
    EXPECT_FALSE(and_result[3]);
    EXPECT_FALSE(and_result[4]);
    
    // Тестируем оператор | (ИЛИ)
    BitArray or_result = a | b;
    // a: 10011, b: 01101 => a|b: 11111 (все биты)
    EXPECT_TRUE(or_result[0]);
    EXPECT_TRUE(or_result[1]);
    EXPECT_TRUE(or_result[2]);
    EXPECT_TRUE(or_result[3]);
    EXPECT_TRUE(or_result[4]);
    
    // Тестируем оператор ^ (XOR)
    BitArray xor_result = a ^ b;
    // a: 10011, b: 01101 => a^b: 11110 (биты 1,2,3,4)
    EXPECT_FALSE(xor_result[0]);      // 1 ^ 1 = 0
    EXPECT_TRUE(xor_result[1]);       // 1 ^ 0 = 1
    EXPECT_TRUE(xor_result[2]);       // 0 ^ 1 = 1
    EXPECT_TRUE(xor_result[3]);       // 0 ^ 1 = 1
    EXPECT_TRUE(xor_result[4]);       // 1 ^ 0 = 1
}

// Тест операторов сравнения
TEST(BitArrayTest, EqualityOperators) {
    BitArray a(5);                    // Создаем первый массив
    a.set(1);
    a.set(3);
    
    BitArray b(5);                    // Второй массив с такими же битами
    b.set(1);
    b.set(3);
    
    BitArray c(5);                    // Третий массив с другими битами
    c.set(1);
    c.set(2);
    
    BitArray d(10);                   // Четвертый массив другого размера
    d.set(1);
    d.set(3);
    
    EXPECT_TRUE(a == b);              // a и b должны быть равны
    EXPECT_FALSE(a == c);             // a и c не равны
    EXPECT_FALSE(a == d);             // a и d разного размера, не равны
    
    EXPECT_FALSE(a != b);             // a != b должно быть false
    EXPECT_TRUE(a != c);              // a != c должно быть true
    EXPECT_TRUE(a != d);              // a != d должно быть true
}

// Тест с большим массивом (проверка производительности и корректности)
TEST(BitArrayTest, LargeArray) {
    const int SIZE = 10000;           // Большой размер
    
    BitArray large(SIZE);             // Создаем большой массив
    
    // Устанавливаем каждый 10-й бит
    for (int i = 0; i < SIZE; i += 10) {
        large.set(i);
    }
    
    // Должно быть SIZE/10 установленных битов
    EXPECT_EQ(large.count(), SIZE / 10);
    EXPECT_TRUE(large.any());         // Должен быть хотя бы один установленный бит
    
    // Сдвигаем на 5 позиций
    large <<= 5;
    
    // Количество установленных битов не должно измениться
    EXPECT_EQ(large.count(), SIZE / 10);
}

TEST(BitArrayTest, EdgeCases) {
    BitArray empty;                   // Пустой массив
    EXPECT_NO_THROW(empty.resize(0)); // Изменение размера на 0 не должно вызывать исключение
    EXPECT_NO_THROW(empty.clear());   // Очистка пустого массива не должна вызывать исключение
    
    BitArray single(1);               // Массив из одного бита
    single.set(0);                    // Устанавливаем единственный бит
    EXPECT_TRUE(single[0]);           // Проверяем
    single.reset(0);                  // Сбрасываем
    EXPECT_FALSE(single[0]);          // Проверяем
    
    BitArray boundary(1);             // Массив из одного бита
    boundary.push_back(true);         // Добавляем бит
    EXPECT_EQ(boundary.size(), 2);    // Размер должен стать 2
    EXPECT_TRUE(boundary[1]);         // Второй бит должен быть установлен
}

// Основная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Инициализация Google Test
    return RUN_ALL_TESTS();                   // Запуск всех тестов
}