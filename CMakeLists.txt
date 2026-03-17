cmake_minimum_required(VERSION 3.31)
project(TreadPool)

set(CMAKE_CXX_STANDARD 20)

add_executable(TreadPool main.cpp
        ThreadPool.cpp
        ThreadPool.h)
