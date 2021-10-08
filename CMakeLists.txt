project(main)
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(main src/main.c src/utils.c)