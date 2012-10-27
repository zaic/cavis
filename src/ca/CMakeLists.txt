cmake_minimum_required(VERSION 2.8)

project(ca)

add_definitions(-std=c11)

aux_source_directory(. SRC)
aux_source_directory(core SRC)
aux_source_directory(hpp SRC)
aux_source_directory(sys SRC)

add_executable(${PROJECT_NAME} ${SRC})

find_package(PNG REQUIRED)
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARY})
