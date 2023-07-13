# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(messaging-client)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the source files
add_executable(messaging-client src/main.cpp src/Client.cpp src/Message.cpp src/Utils.cpp)
target_link_libraries(messaging-client pthread)
