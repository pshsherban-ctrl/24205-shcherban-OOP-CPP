#!/bin/bash

# build.sh - Скрипт для сборки игры "Жизнь" на Linux

# Компилятор
CXX=g++

# Флаги компиляции
CXXFLAGS="-std=c++17 -Wall -Wextra -O2 -I./include"

# Список исходных файлов
SOURCES="src/rule.cpp \
         src/universe.cpp \
         src/universe_file_handler.cpp \
         src/universe_renderer.cpp \
         src/game_controller.cpp \
         src/command_line_parser.cpp \
         src/preset_universes.cpp \
         main.cpp"

# Имя исполняемого файла
EXECUTABLE="game_of_life"

echo "Компиляция игры 'Жизнь'..."

# Компиляция
$CXX $CXXFLAGS $SOURCES -o $EXECUTABLE

# Проверка успешности компиляции
if [ $? -eq 0 ]; then
    echo "Сборка успешно завершена!"
    echo "Исполняемый файл: $EXECUTABLE"

    # Копируем примеры в текущую папку (если нужно)
    if [ -d "examples" ]; then
        cp -r examples ./
        echo "Примеры файлов скопированы в текущую папку"
    fi
else
    echo "Ошибка компиляции!"
    exit 1
fi
