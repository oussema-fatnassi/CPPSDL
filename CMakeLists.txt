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

# Platform-specific settings
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS specific settings

    # Add SDL2 include directories
    include_directories(/opt/homebrew/opt/sdl2/include/SDL2 /opt/homebrew/opt/sdl2_image/include/SDL2)

    # Link SDL2 and SDL2_image libraries
    target_link_libraries(Main /opt/homebrew/opt/sdl2/lib/libSDL2.dylib /opt/homebrew/opt/sdl2_image/lib/libSDL2_image.dylib)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows specific settings
    # find_package(SDL2 REQUIRED)
    # find_package(SDL2_image REQUIRED)
    # include_directories(C:/Program Files (x86)/SDL2/x86_64-w64-mingw32/include/SDL2 
    # C:/Program Files (x86)/SDL2_image/x86_64-w64-mingw32/include/SDL2)
    # target_link_libraries(Main C:/Program Files (x86)/SDL2/x86_64-w64-mingw32/lib/ 
    # C:/Program Files (x86)/SDL2_image/x86_64-w64-mingw32/lib mingw32 SDL2main SDL2 SDL2_image)

    # Manually specify SDL2 paths if find_package(SDL2) does not work
    set(SDL2_INCLUDE_DIRS "C:/Program Files (x86)/SDL2/x86_64-w64-mingw32/include")
    set(SDL2_IMAGE_INCLUDE_DIRS "C:/Program Files (x86)/SDL2_image/x86_64-w64-mingw32/include")
    set(SDL2_LIBRARIES "C:/Program Files (x86)/SDL2/x86_64-w64-mingw32/bin/SDL2.dll" "C:/Program Files (x86)/SDL2/x86_64-w64-mingw32/lib/libSDL2.a")
    set(SDL2_IMAGE_LIBRARIES "C:/Program Files (x86)/SDL2_image/x86_64-w64-mingw32/bin/SDL2_image.dll" "C:/Program Files (x86)/SDL2_image/x86_64-w64-mingw32/lib/libSDL2_image.a")

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(Main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Specify output directory for binaries directly in the build folder
set_target_properties(Main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
