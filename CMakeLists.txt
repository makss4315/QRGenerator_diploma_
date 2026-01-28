cmake_minimum_required(VERSION 3.16)
project(QRGenerator_diploma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ---------- Qt ----------
set(Qt6_DIR "X:/QT/6.10.1/mingw_64/lib/cmake/Qt6")
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

# ---------- OpenCV ----------
set(OpenCV_ROOT "X:/Git_Repo/OpenCV-MinGW")
set(OpenCV_INCLUDE_DIR "${OpenCV_ROOT}/include")
set(OpenCV_LIB_DIR     "${OpenCV_ROOT}/x64/mingw/lib")

# ---------- Executable ----------
add_executable(QRGenerator  WIN32
        UI/main.cpp
        UI/mainwindow.cpp
        UI/mainwindow.h
        UI/mainwindow.ui

        core/qr_handler.cpp
        core/qr_handler.h
        core/qrcodegen/qrcodegen.cpp
)

target_include_directories(QRGenerator PRIVATE
        ${OpenCV_INCLUDE_DIR}
        UI
        core
        core/qrcodegen
)

target_link_libraries(QRGenerator PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::Core

        ${OpenCV_LIB_DIR}/libopencv_highgui455.dll.a
        ${OpenCV_LIB_DIR}/libopencv_imgcodecs455.dll.a
        ${OpenCV_LIB_DIR}/libopencv_imgproc455.dll.a
        ${OpenCV_LIB_DIR}/libopencv_objdetect455.dll.a
        ${OpenCV_LIB_DIR}/libopencv_core455.dll.a
)
