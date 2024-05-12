cmake_minimum_required(VERSION 3.22.1)

project(Renderer)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

add_subdirectory(external/SDL2)
add_subdirectory(custom)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC external/SDL2/include
    PUBLIC custom/include
)

target_link_directories(${CMAKE_PROJECT_NAME}
    PRIVATE external/SDL2/src
    PRIVATE custom
)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2 custom)
