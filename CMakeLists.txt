cmake_minimum_required(VERSION 3.10)

# Define project details
project(MainProject VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the paths for your project
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

# Include directories for your headers
include_directories(${INCLUDE_DIR}/headers)

# Add source files
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

# Create the executable from the source files
add_executable(Main ${SRC_FILES})

# Specify output directory for binaries
set_target_properties(Main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

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
