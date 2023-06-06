cmake_minimum_required(VERSION 3.10)
project(messaging-server)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the source files
add_executable(messaging-server src/main.cpp src/server.cpp)

# link against the mysqlclient library
target_link_libraries(messaging-server mysqlclient)