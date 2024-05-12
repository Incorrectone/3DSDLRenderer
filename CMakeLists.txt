cmake_minimum_required(VERSION 3.22.1)

project(Renderer)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

add_subdirectory(external/SDL2)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC external/SDL2/include
)

target_link_directories(${CMAKE_PROJECT_NAME}
    PRIVATE external/SDL2/src
)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2)