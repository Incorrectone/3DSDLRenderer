cmake_minimum_required(VERSION 3.22.1)

project(custom)

add_library(${PROJECT_NAME} 
            include/constants.h
            include/vectors.h 
            include/shapes.h
            shader.cpp include/shader.h
            putPixel.cpp include/putPixel.h 
            viewport.cpp include/viewport.h
            )