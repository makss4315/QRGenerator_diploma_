cmake_minimum_required(VERSION 3.16)
project(QRGenerator_diploma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_TOOLCHAIN_FILE "X:/Git_Repo/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

set(Qt6_DIR "X:/QT/6.10.1/mingw_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${Qt6_DIR})

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
find_package(OpenCV REQUIRED)

add_executable(QRGenerator
        UI/main.cpp
        UI/mainwindow.cpp
        UI/mainwindow.h
        UI/mainwindow.ui

        core/qr_handler.cpp
        core/qrcodegen/qrcodegen.cpp
        core/qrcodegen/UserInputs.cpp
)

target_include_directories(QRGenerator PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        core
        core/qrcodegen
        UI
)

target_link_libraries(QRGenerator PRIVATE
        Qt6::Widgets
)

