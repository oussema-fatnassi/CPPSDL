cmake_minimum_required(VERSION 3.5)

# Project name
project(2048)

# Set standards
set(CMAKE_CXX_STANDARD 14)

# Exécutables
add_executable(main Main.cpp Grid.cpp NumberGrid.cpp InputHandler.cpp)