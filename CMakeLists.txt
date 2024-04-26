cmake_minimum_required(VERSION 3.28)
project(client_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(client_server main.cpp
        server.cpp
        client.cpp
)
