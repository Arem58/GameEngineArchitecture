cmake_minimum_required(VERSION 3.27)

project(GEA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS off)

file(
    GLOB_RECURSE 
    SOURCES 
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

find_package(SDL2 REQUIRED)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARIES}
)