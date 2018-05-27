cmake_minimum_required(VERSION 3.9)
project(Graphs5)
set(EXECUTABLE_NAME "Graphs5")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

include_directories(include/)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})