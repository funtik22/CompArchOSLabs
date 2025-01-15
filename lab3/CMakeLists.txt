cmake_minimum_required(VERSION 3.5)
project(BUFFER)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SRC main.cpp Image.cpp Time.cpp)

set(HEADERS Image.hpp Buffer.hpp)

   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(Buffer ${SRC} ${HEADERS})

target_link_libraries( Buffer ${OpenCV_LIBS} )