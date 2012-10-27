cmake_minimum_required(VERSION 2.8)

project(ca)

add_definitions(-std=c11)
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -Wall -Wextra -Wunused -Wshadow -DNDEBUG")

aux_source_directory(. SRC)
aux_source_directory(core SRC)
aux_source_directory(hpp SRC)

add_executable(${PROJECT_NAME} ${SRC})

find_package(PNG REQUIRED)
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARY})
