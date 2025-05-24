cmake_minimum_required(VERSION 3.16)
project(SFML_Vaclav_Fencl)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC
    src/*.cpp
    src/*.h
)

add_executable(${PROJECT_NAME} Main.cpp ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/buttons
    src/core
    src/entities
    src/states
)

find_package(SFML 2.6 COMPONENTS graphics window system audio network QUIET)

if (NOT SFML_FOUND)
    message(STATUS "System SFML not found, using local SFML from Thirdparty/")
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/Thirdparty/SFML-2.6.1/lib/cmake/SFML")
    find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Thirdparty/SFML-2.6.1/include")
else()
    message(STATUS "Using system-installed SFML")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
)
