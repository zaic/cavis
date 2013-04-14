project(visualizer)
cmake_minimum_required(VERSION 2.8.8)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

include_directories("/home/zaic/nsu/libca/include")

#message(${Qt5Widgets_LIBRARIES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})


#set(BOOST_COMPONENTS
#    system)
#find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
find_package(Threads)
#include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/home/zaic/nsu/cavis/src/cmake/")
find_package(root REQUIRED)
include_directories(${ROOT_INCLUDE_DIR} "${ROOT_INCLUDE_DIR}/root")
link_directories("${ROOT_LIBRARY_DIR}/root") # TODO: fix

#set(CMAKE_BUILD_TYPE distribution) do nothing :(
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -Wshadow -Wfloat-equal -O0 -D_DEBUG -g -ldl ")
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Wold-style-cast -Wfloat-equal -Woverloaded-virtual -O0 -D_DEBUG -g")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Woverloaded-virtual -O0 -D_DEBUG -DBUFFER_OPENGL -g ")


aux_source_directory(. SRC_LIST)

add_subdirectory(./buffer)
aux_source_directory(./buffer SRC_LIST)
aux_source_directory(./buffer/qt_buffer SRC_LIST)

add_subdirectory(./renderer)
aux_source_directory(./renderer SRC_LIST)
aux_source_directory(./renderer/hpp-loupe SRC_LIST)
aux_source_directory(./renderer/grayscale SRC_LIST)
aux_source_directory(./renderer/projection SRC_LIST)
aux_source_directory(./renderer/wave SRC_LIST)

add_subdirectory(./layer)
aux_source_directory(./layer SRC_LIST)
aux_source_directory(./layer/arrow SRC_LIST)
aux_source_directory(./layer/ruler SRC_LIST)

add_subdirectory(./config)
aux_source_directory(./config SRC_LIST)
aux_source_directory(./config/file SRC_LIST)
#aux_source_directory(./config/network-tcp SRC_LIST)
aux_source_directory(./config/stub SRC_LIST)
aux_source_directory(./config/local SRC_LIST)
aux_source_directory(./config/dll SRC_LIST)

add_subdirectory(./workspace)
aux_source_directory(./workspace SRC_LIST)

set(MOC_HEADERS
    window.h
    windowevent.h
    buffercontainer.h

    workspace/view.h

    buffer/qt_buffer/renderarea.h
	buffer/qt_buffer/openglarea.h

    config/config.h
    config/dll/dllconfig.h
    config/local/localfileconfig.h
    config/stub/stubconfig.h

    renderer/renderer.h
    renderer/gui.h
    renderer/hpp-loupe/hpploupe.h
    renderer/hpp-loupe/gui.h
    renderer/grayscale/grayscale.h
    renderer/grayscale/gui.h
    renderer/projection/projection.h
    renderer/projection/gui.h
    renderer/wave/wave.h
    renderer/wave/gui.h
)
qt5_wrap_cpp(MOC_SRC ${MOC_HEADERS})
qt5_add_resources(RESOURCES_SRC "../data/icons.qrc")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${MOC_SRC} ${RESOURCES_SRC})
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES}  ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} "/usr/lib64/root/libMathMore.so" "/home/zaic/nsu/libca/libca.so")
file(COPY examples DESTINATION .)
file(COPY images DESTINATION .)
