cmake_minimum_required(VERSION 3.10)
project(QRGenerator)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_TOOLCHAIN_FILE "X:/Git_Repo/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(Qt6_DIR "X:/QT/6.10.1/mingw_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${Qt6_DIR})


find_package(Qt6 REQUIRED COMPONENTS Widgets)
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