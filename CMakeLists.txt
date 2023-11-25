cmake_minimum_required(VERSION 3.27)

project(GAME VERSION 1.0)

# Enable C++20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(Lua REQUIRED)

file(
    GLOB_RECURSE 
    SOURCES 
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)


add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${LUA_LIBRARIES}
)