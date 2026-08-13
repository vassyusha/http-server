cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME http-server)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/main.cpp src/net/tcp_server.cpp src/http/parser.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE src/net src/http)