project(visualizer)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})


set (BOOST_COMPONENTS
    system)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
find_package (Threads)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -O2 -w")


aux_source_directory(. SRC_LIST)

add_subdirectory(./buffer)
aux_source_directory(./buffer SRC_LIST)
aux_source_directory(./buffer/qt_buffer SRC_LIST)

add_subdirectory(./cut)
aux_source_directory(./cut SRC_LIST)
aux_source_directory(./cut/life SRC_LIST)
aux_source_directory(./cut/hpp-loupe SRC_LIST)

add_subdirectory(./config)
aux_source_directory(./config SRC_LIST)
aux_source_directory(./config/file SRC_LIST)
aux_source_directory(./config/network-tcp SRC_LIST)
aux_source_directory(./config/stub SRC_LIST)

set(MOC_HEADERS
    buffer/qt_buffer/window.h
    buffer/qt_buffer/renderarea.h
)
qt4_wrap_cpp(MOC_SRC ${MOC_HEADERS})

add_executable(${PROJECT_NAME} ${SRC_LIST} ${MOC_SRC})
target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
file(COPY examples DESTINATION .)
file(COPY images DESTINATION .)
