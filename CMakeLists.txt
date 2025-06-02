cmake_minimum_required(VERSION 3.10)
project(QRGenerator)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenCV REQUIRED)

add_executable(qr_handler
        qr_handler.cpp
        qrcodegen/qrcodegen.cpp
)

target_include_directories(qr_handler PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        qrcodegen
)

target_link_libraries(qr_handler PRIVATE ${OpenCV_LIBS})
