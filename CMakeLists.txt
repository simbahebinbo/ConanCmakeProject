cmake_minimum_required(VERSION 3.0)
project(OpenCVTest)

find_package(OpenCV REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(OpenCVTest main.cpp)
target_link_libraries(OpenCVTest ${OpenCV_LIBS} sfml-graphics)