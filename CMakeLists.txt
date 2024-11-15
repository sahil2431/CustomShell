# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyCLI VERSION 1.0 LANGUAGES CXX)

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /Zi")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
endif()

# Set directories for source files, headers, and build output
set(SRC_DIR "source")
set(HEADER_DIR "headers")
set(OBJ_DIR "build")

# Collect all the source files in the source directory
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

# Define the target executable
add_executable(my_cli ${SOURCES})

# Specify include directories (header files)
target_include_directories(my_cli PRIVATE "${HEADER_DIR}")

# Set the output directory for the executable to the root of the project directory
set_target_properties(my_cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}  # Place the executable in the project root directory
)

# Clean up build artifacts (optional; usually handled by 'cmake --build' or 'make clean')
add_custom_target(clean_build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${OBJ_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/my_cli
    COMMENT "Cleaning build artifacts"
)
