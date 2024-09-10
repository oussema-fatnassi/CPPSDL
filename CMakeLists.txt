cmake_minimum_required(VERSION 3.10)

# Define project details
project(MainProject VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Gtest setup
enable_testing()
add_subdirectory(googletest)

# Set the paths for your project
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

# Include directories for your headers
include_directories(${INCLUDE_DIR}/headers ${GOOGLETEST_DIR}/googletest/include)

# Add source files
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

# Create the executable from the source files
add_executable(Main ${SRC_FILES})

# Set the build type to Debug to include debugging symbols
set(CMAKE_BUILD_TYPE Debug)

# Enable Address Sanitizer if desired
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Add Address Sanitizer compiler and linker options
    add_compile_options(-fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()

# Platform-specific settings
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS specific settings

    # Add SDL2, SDL2_image and SDL2_ttf include directories
    include_directories(/opt/homebrew/opt/sdl2/include/SDL2 /opt/homebrew/opt/sdl2_image/include/SDL2 /opt/homebrew/opt/sdl2_ttf/include/SDL2)

    # Link SDL2, SDL2_image and SDL2_ttf libraries
    target_link_libraries(Main /opt/homebrew/opt/sdl2/lib/libSDL2.dylib /opt/homebrew/opt/sdl2_image/lib/libSDL2_image.dylib /opt/homebrew/opt/sdl2_ttf/lib/libSDL2_ttf.dylib googletest)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows specific settings
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    # Add SDL2, SDL2_image, and SDL2_ttf include directories
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

    # Link SDL2, SDL2_image, and SDL2_ttf libraries
    target_link_libraries(Main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} mingw32 SDL2main SDL2 SDL2_image SDL2_ttf googletest)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Specify output directory for binaries directly in the build folder
set_target_properties(Main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Add tests
include(GoogleTest)
gtest_discover_tests(Main)
