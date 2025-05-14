cmake_minimum_required(VERSION 3.16)
project(SFML_Vaclav_Fencl)

set(CMAKE_CXX_STANDARD 17)

# SFML path
set(SFML_DIR "${CMAKE_SOURCE_DIR}/Thirdparty/SFML-2.6.1")

# Source files
file(GLOB_RECURSE SRC
    src/*.cpp
    src/*.h
)

add_executable(${PROJECT_NAME} Main.cpp ${SRC})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/buttons
    src/core
    src/entities
    src/states
    ${SFML_DIR}/include
)

# Link SFML
find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED PATHS ${SFML_DIR}/lib/cmake/SFML)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
