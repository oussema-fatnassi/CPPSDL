cmake_minimum_required(VERSION 3.10)

project(MainProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Main main.cpp)

# Platform-specific settings
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS specific settings
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

    target_link_libraries(Main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows specific settings
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

    # Add mingw32 for Windows (if using MinGW)
    target_link_libraries(Main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} mingw32 SDL2main SDL2 SDL2_image)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()
