cmake_minimum_required(VERSION 3.16)
project(QRGenerator_diploma)

# ================= C++ =================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ================= Qt ==================
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Qt6_DIR "X:/QT/6.10.1/mingw_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${Qt6_DIR})

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)



set(OpenCV_ROOT "X:/Git_Repo/OpenCV-MinGW")

set(OpenCV_INCLUDE_DIR "${OpenCV_ROOT}/include")
set(OpenCV_LIB_DIR     "${OpenCV_ROOT}/x64/mingw/lib")



add_executable(QRGenerator
        UI/main.cpp
        UI/mainwindow.cpp
        UI/mainwindow.h
        UI/mainwindow.ui

        core/qr_handler.cpp
        core/qr_handler.h

        core/qrcodegen/qrcodegen.cpp
        core/qrcodegen/UserInputs.cpp
)


target_include_directories(QRGenerator PRIVATE
        UI
        core
        core/qrcodegen
        ${OpenCV_INCLUDE_DIR}
)


target_link_libraries(QRGenerator PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::Core

        ${OpenCV_LIB_DIR}/libopencv_core455.dll.a
        ${OpenCV_LIB_DIR}/libopencv_imgproc455.dll.a
        ${OpenCV_LIB_DIR}/libopencv_imgcodecs455.dll.a
)

