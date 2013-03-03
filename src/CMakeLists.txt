project(visualizer)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}) # wtf? TODO


set (BOOST_COMPONENTS
    system)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
find_package(Threads)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/home/zaic/nsu/cavis/src/cmake/")
find_package(root REQUIRED)
include_directories(${ROOT_INCLUDE_DIR} "${ROOT_INCLUDE_DIR}/root")
link_directories("${ROOT_LIBRARY_DIR}/root") # TODO: fix

#set(CMAKE_BUILD_TYPE distribution) do nothing :(
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -O0 -D_DEBUG -g")


aux_source_directory(. SRC_LIST)

add_subdirectory(./buffer)
aux_source_directory(./buffer SRC_LIST)
aux_source_directory(./buffer/qt_buffer SRC_LIST)

add_subdirectory(./renderer)
aux_source_directory(./renderer SRC_LIST)
aux_source_directory(./renderer/hpp-loupe SRC_LIST)
aux_source_directory(./renderer/grayscale SRC_LIST)
aux_source_directory(./renderer/projection SRC_LIST)

add_subdirectory(./layer)
aux_source_directory(./layer SRC_LIST)

add_subdirectory(./config)
aux_source_directory(./config SRC_LIST)
aux_source_directory(./config/file SRC_LIST)
aux_source_directory(./config/network-tcp SRC_LIST)
aux_source_directory(./config/stub SRC_LIST)
aux_source_directory(./config/local SRC_LIST)

set(MOC_HEADERS
	window.h
    windowevent.h
    buffer/qt_buffer/renderarea.h
    renderer/gui.h
    renderer/hpp-loupe/gui.h
    renderer/grayscale/gui.h
    renderer/projection/gui.h
)
qt4_wrap_cpp(MOC_SRC ${MOC_HEADERS})
qt4_add_resources(RESOURCES_SRC "../data/icons.qrc")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${MOC_SRC} ${RESOURCES_SRC})
target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} "/usr/lib64/root/libMathMore.so")
file(COPY examples DESTINATION .)
file(COPY images DESTINATION .)
