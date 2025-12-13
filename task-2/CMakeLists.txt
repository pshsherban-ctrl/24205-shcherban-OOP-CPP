# Минимальная требуемая версия CMake (необходима для некоторых функций)
cmake_minimum_required(VERSION 3.10)

# Имя проекта (используется при генерации файлов сборки)
project(GameOfLife)

# Устанавливаем стандарт языка C++ (требуется C++17 для некоторых возможностей)
set(CMAKE_CXX_STANDARD 17)
# Требуем соблюдения указанного стандарта (если компилятор не поддерживает - ошибка)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список исходных файлов проекта
# Каждый .cpp файл должен быть указан здесь
set(SOURCES
    src/rule.cpp                       # Реализация правил игры
    src/universe.cpp                   # Реализация игровой вселенной
    src/universe_file_handler.cpp      # Загрузка и сохранение файлов
    src/universe_renderer.cpp          # Отрисовка в консоли
    src/game_controller.cpp            # Управление игровым процессом
    src/command_line_parser.cpp        # Парсинг аргументов командной строки
    src/preset_universes.cpp           # Предустановленные вселенные
    main.cpp                           # Точка входа в программу
)

# Создание исполняемого файла из указанных исходных файлов
# Имя исполняемого файла: game_of_life (на Windows: game_of_life.exe)
add_executable(game_of_life ${SOURCES})

# Указываем директории, где находятся заголовочные файлы (.hpp)
# PRIVATE означает, что эти пути используются только для компиляции этого target
target_include_directories(game_of_life PRIVATE include)

# Платформозависимые настройки
if(WIN32)
    # Для Windows: отключаем предупреждения безопасности CRT
    # Это необходимо, чтобы не было предупреждений при использовании функций типа sscanf
    target_compile_definitions(game_of_life PRIVATE _CRT_SECURE_NO_WARNINGS)

    # Для Windows: указываем линковщику использовать консольную подсистему
    # Это нужно для того, чтобы при запуске программы открывалось консольное окно
    target_link_options(game_of_life PRIVATE -mconsole)
endif()

# Копируем директорию с примерами файлов в директорию сборки
# Это позволяет использовать примеры без копирования вручную
file(COPY examples DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
