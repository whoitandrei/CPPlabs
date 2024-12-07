cmake_minimum_required(VERSION 3.10)

# задаем используемый стандарт С++
set(CMAKE_CXX_STANDARD 17)

# TODO: переименовать проект
project(SoundProcessor)

# задаем имя исполняемого файла основной программы
set(exe_name ${PROJECT_NAME})

# Включаем отслеживание всех предупреждений (warnings) и запрещаем компиляцию при наличии предупреждений.
# Считается хорошим тоном, когда программа собирается без предупрреждений.
# Но вы можете убрать /WX и -Werror (разрешив компиляцию с предупреждениями), если сможете разумно объяснить своё решение.
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# описываем основную библиотеку, т.е. библиотеку, содержащую все cpp-файлы, кроме main.cpp
# TODO: отредактировать список cpp-файлов

# описываем исполняемый файл основной программы: это main.cpp + основная библиотека
add_executable(${exe_name} src/main.cpp src/Converter.cpp src/DATA.cpp src/SoundProcessor.cpp src/WAV.cpp src/consoleColor.cpp)

