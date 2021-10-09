cmake_minimum_required(VERSION 3.17)
project(HW1)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror --coverage")

set(SOURCES src/utils.c )

add_library(utils STATIC ${SOURCES})
target_include_directories(utils PUBLIC include)


add_executable(IW_1 src/main.c src/run.c)
target_link_libraries(IW_1 utils)

enable_testing()
find_package(GTest REQUIRED)
add_executable(gtests tests/test.cpp)
target_link_libraries(gtests ${GTEST_LIBRARIES} utils)

#include_directories(include)

#add_executable(main src/main.c src/utils.c tests/test.cpp tests/test.h)

