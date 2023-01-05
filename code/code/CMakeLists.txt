cmake_minimum_required(VERSION 3.0)

project(final7)

include_directories(include)

find_package(OpenCV REQUIRED)

add_executable(task  main.cpp src/detect.cpp)

target_link_libraries(task ${OpenCV_LIBS})