cmake_minimum_required(VERSION 3.3)
project(02)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ChatClient.cpp
    ChatServer.cpp
    ClientSocket.cpp
    ClientSocket.h
    ServerSocket.cpp
    ServerSocket.h
    Socket.cpp
    Socket.h
    SocketException.h
    ThreadReadWriteLock.h)

add_executable(02 ${SOURCE_FILES})