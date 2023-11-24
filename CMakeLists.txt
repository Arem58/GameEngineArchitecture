cmake_minimum_required(VERSION 3.27)

project(GAME VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS off)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(
    GLOB_RECURSE 
    SOURCES 
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)


add_executable(
    src/main.cpp
    ${SOURCES}
)

target_include_directories(
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
    ${SDL2_LIBRARIES}
)