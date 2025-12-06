cmake_minimum_required(VERSION 3.10)
project(BitArrayProject)

set(CMAKE_CXX_STANDARD 11)

# Подключаем Google Test
find_package(GTest REQUIRED)

# Основная библиотека
add_library(BitArray src/BitArray.cpp include/BitArray.h)

# Тесты
add_executable(BitArrayTests tests/BitArrayTests.cpp)
target_link_libraries(BitArrayTests GTest::gtest GTest::gtest_main BitArray)

# Включение тестов
enable_testing()
add_test(NAME BitArrayTests COMMAND BitArrayTests)
