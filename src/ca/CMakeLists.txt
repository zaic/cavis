cmake_minimum_required(VERSION 2.8)

project(ca)

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wunused -Wshadow")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -Werror")

aux_source_directory(. SRC)
aux_source_directory(core SRC)
aux_source_directory(hpp SRC)

add_executable(${PROJECT_NAME} ${SRC})

find_package(PNG REQUIRED)
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARY})
