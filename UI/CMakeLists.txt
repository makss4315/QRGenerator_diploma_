cmake_minimum_required(VERSION 3.16)
project(QRGenerator)

set(CMAKE_CXX_STANDARD 17)

# Пусть CMake знает где искать Qt6
set(Qt6_DIR "X:/QT/6.10.1/mingw_64/lib/cmake/Qt6")

# Подключаем нужные компоненты Qt
find_package(Qt6 COMPONENTS Widgets Gui Core REQUIRED)

# Создаём исполняемый файл
add_executable(QRGenerator
        mainwindow.ui
        mainwindow.cpp
        mainwindow.h
)

# Линкуем Qt
target_link_libraries(QRGenerator PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)


