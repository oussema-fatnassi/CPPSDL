# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MyTerminalGame VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# Add source files from src directory
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(Main ${SOURCES})