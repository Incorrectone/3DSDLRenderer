cmake_minimum_required(VERSION 3.22.1)

project(custom)

add_library(${PROJECT_NAME} putPixel.cpp include/putPixel.h include/constants.h)