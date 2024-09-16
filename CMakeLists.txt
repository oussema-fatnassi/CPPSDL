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

# Include directories for your headers
include_directories(${INCLUDE_DIR}/headers)

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

# Platform-specific settings
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS specific settings

    # Add SDL2, SDL2_image and SDL2_ttf include directories
    include_directories(/opt/homebrew/opt/sdl2/include/SDL2 /opt/homebrew/opt/sdl2_image/include/SDL2 /opt/homebrew/opt/sdl2_ttf/include/SDL2)

    # Link SDL2, SDL2_image and SDL2_ttf libraries
    target_link_libraries(Main /opt/homebrew/opt/sdl2/lib/libSDL2.dylib /opt/homebrew/opt/sdl2_image/lib/libSDL2_image.dylib /opt/homebrew/opt/sdl2_ttf/lib/libSDL2_ttf.dylib)

    find_package(GTest REQUIRED)

    include_directories(${GTEST_INCLUDE_DIRS})

    # Ajouter le fichier source de test
    add_executable(test testing/test_main.cpp)

    # Lier GoogleTest et pthread
    target_link_libraries(test ${GTEST_LIBRARIES} pthread)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows specific settings

    # Set the path to GoogleTest
    set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/googletest")
    set(GTEST_LIBRARIES "${GTEST_ROOT}/build/lib/libgtest.a")
    set(GTEST_INCLUDE_DIRS "${GTEST_ROOT}/googletest/include")

    # Add the GTest include directory
    include_directories(${GTEST_INCLUDE_DIRS})

    add_library(gtest STATIC IMPORTED)
    set_target_properties(gtest PROPERTIES IMPORTED_LOCATION ${GTEST_LIBRARIES})

    add_library(gtest_main STATIC IMPORTED)
    set_target_properties(gtest_main PROPERTIES IMPORTED_LOCATION "${GTEST_ROOT}/build/lib/libgtest_main.a")

    # Do NOT link gtest and gtest_main with Main
    # target_link_libraries(Main gtest gtest_main)

    # Disable Address Sanitizer for Windows
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "AddressSanitizer is not supported on Windows. Skipping sanitization.")
    endif()

    # Disable unsupported C++11 functions on Windows
    add_compile_definitions(_GLIBCXX_USE_C99_QUICK_EXIT=0 _GLIBCXX_USE_C99_TIMESPEC_GET=0)

    # Add SDL2, SDL2_image, and SDL2_ttf include directories
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

    # Link SDL2, SDL2_image, and SDL2_ttf libraries
    target_link_libraries(Main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)
    add_executable(test testing/test_main.cpp)
    
    # Link GoogleTest libraries to the test executable
    target_link_libraries(test gtest gtest_main)

else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Specify output directory for binaries directly in the build folder
set_target_properties(Main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Add the test executable

# Specify output directory for binaries directly in the build folder
set_target_properties(Main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

