cmake_minimum_required(VERSION 3.16)

project(QRGeneratorUI)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets Gui Core REQUIRED)

qt_wrap_ui(UI_HEADERS mainwindow.ui)

add_executable(QRGenerator
        qr_handler.cpp
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

target_link_libraries(QRGenerator PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::Core
        core
)
