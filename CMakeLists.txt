cmake_minimum_required(VERSION 3.10)

# Define project details
project(MainProject VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the paths for your project
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/headers")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/testing")
include_directories(${INCLUDE_DIR})

# Add source files
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

# Create the main executable from the source files
add_executable(Main ${SRC_FILES})

# Set the build type to Debug to include debugging symbols
set(CMAKE_BUILD_TYPE Debug)

# Enable Address Sanitizer if desired
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Add Address Sanitizer compiler and linker options
    add_compile_options(-fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()

# Find and link SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Link SFML libraries
target_link_libraries(Main sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Platform-specific settings
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS specific settings (optional, adjust if needed)

    # For Homebrew installations of SFML
    include_directories(/opt/homebrew/include)
    target_link_libraries(Main /opt/homebrew/lib/libsfml-system.dylib /opt/homebrew/lib/libsfml-window.dylib /opt/homebrew/lib/libsfml-graphics.dylib /opt/homebrew/lib/libsfml-audio.dylib /opt/homebrew/lib/libsfml-network.dylib)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows specific settings (assumes SFML is installed and in PATH)
    find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

    # Add SFML include directories
    include_directories(${SFML_INCLUDE_DIR})

    # Link SFML libraries
    target_link_libraries(Main ${SFML_LIBRARIES})
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Specify output directory for binaries directly in the build folder
set_target_properties(Main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test source file
add_executable(test ${TEST_DIR}/test_main.cpp)

# Link GoogleTest and pthread
target_link_libraries(test ${GTEST_LIBRARIES} pthread)
