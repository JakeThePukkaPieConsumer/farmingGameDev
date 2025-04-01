cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build directory
set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build")
file(MAKE_DIRECTORY ${BUILD_DIR})

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/raylib/include)

# Source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Link raylib static library
set(RAYLIB_LIB "${CMAKE_SOURCE_DIR}/libs/raylib/lib/libraylib.a")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against raylib and necessary system libraries
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB} winmm gdi32 opengl32)
