cmake_minimum_required(VERSION 3.10)
project(QRGenerator)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_TOOLCHAIN_FILE "X:/Git_Repo/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")



find_package(OpenCV REQUIRED)

add_executable(qr_handler
        core/qr_handler.cpp
        core/qrcodegen/qrcodegen.cpp
)

target_include_directories(qr_handler PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        core/qrcodegen
)

target_link_libraries(qr_handler PRIVATE ${OpenCV_LIBS})

add_subdirectory(UI)