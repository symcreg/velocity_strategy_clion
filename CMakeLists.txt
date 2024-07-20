cmake_minimum_required(VERSION 3.27)
project(velocity_strategy)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/include/opencv/install)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)


add_executable(velocity_strategy main.cpp
        velocity.cpp
        velocity.h
        trace.cpp
        trace.h
        drawer.cpp
        drawer.h
        time_sys.cpp
        time_sys.h
)

target_link_libraries(velocity_strategy ${OpenCV_LIBS})
