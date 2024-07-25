cmake_minimum_required(VERSION 3.22.1)

project(Renderer)

add_subdirectory(external/SDL2)
include_directories(external/SDL2/include)

set(HEADER_DIR include)
file(GLOB headers "${HEADER_DIR}/*.h")
file(GLOB sources "src/*.cpp")
add_library(custom STATIC ${sources} ${headers})
target_include_directories(custom PUBLIC "${HEADER_DIR}")

add_executable(${CMAKE_PROJECT_NAME} main.cpp ${sources})

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2 custom)