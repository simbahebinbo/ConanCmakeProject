cmake_minimum_required(VERSION 3.15)

project(OpenCVTest LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
find_package(SFML COMPONENTS graphics REQUIRED)

add_executable(OpenCVTest
        src/main.cpp
)
target_link_libraries(OpenCVTest PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
)
