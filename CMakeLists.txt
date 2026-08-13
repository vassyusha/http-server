cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME http-server)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(src src/net)

add_executable(main.cpp tcp_server.cpp)
