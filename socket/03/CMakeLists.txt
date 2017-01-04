cmake_minimum_required(VERSION 3.3)
project(03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ChatClient.cpp
    ChatServer.cpp
    ClientSocket.cpp
    ClientSocket.h
    Epoll.cpp
    Epoll.h
    EpollServerSocket.cpp
    EpollServerSocket.h
    ServerSocket.cpp
    ServerSocket.h
    Socket.cpp
    Socket.h
    SocketException.h
    ThreadReadWriteLock.h)

add_executable(03 ${SOURCE_FILES})