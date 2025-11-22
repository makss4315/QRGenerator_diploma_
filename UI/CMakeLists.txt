cmake_minimum_required(VERSION 3.24)
project(QRGenerator)

set(CMAKE_CXX_STANDARD 17)


set(Qt6_DIR "X:/QT/6.10.1/mingw_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${Qt6_DIR})

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(QRGenerator
       mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

target_link_libraries(QRGenerator PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
