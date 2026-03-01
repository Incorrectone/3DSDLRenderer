cmake_minimum_required(VERSION 3.22.1)

project(Renderer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -fsanitize=address")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

find_package(OpenMP REQUIRED)

find_package(SDL2 REQUIRED)

set(HEADER_DIR include)
file(GLOB headers "${HEADER_DIR}/*.h")
file(GLOB sources "src/*.cpp")
add_library(custom STATIC ${sources} ${headers})

target_include_directories(custom PUBLIC "${HEADER_DIR}" ${SDL2_INCLUDE_DIRS})

set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_BUILD_DEST_DIR "${CMAKE_BINARY_DIR}/assets")
file(COPY "${ASSETS_SOURCE_DIR}/" DESTINATION "${ASSETS_BUILD_DEST_DIR}")

if(OpenMP_CXX_FOUND)
    target_link_libraries(custom PUBLIC OpenMP::OpenMP_CXX)
endif()

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} custom OpenMP::OpenMP_CXX ${SDL2_LIBRARIES})