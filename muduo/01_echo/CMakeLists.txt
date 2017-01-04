cmake_minimum_required(VERSION 3.3)
project(01_echo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    echo.cc
    echo.h
    main.cc)

add_executable(01_echo ${SOURCE_FILES})