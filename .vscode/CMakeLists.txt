cmake_minimum_required(VERSION 3.10)
project(OpenGLTest)

# Add the directory containing FindAssimp.cmake to the CMake module path
list(APPEND CMAKE_MODULE_PATH "/usr/local/Cellar/assimp/5.4.0/lib/cmake/assimp-5.4")

# Find the Assimp package
find_package(assimp REQUIRED)

# Add your source files
set(SOURCES
    src/main
    # Add your other source files here
)

# Add an executable target
add_executable(OpenGLTest /Users/a5520/Desktop/OpenGLTest/src/main.cpp)

# Link Assimp with your executable
target_link_libraries(OpenGLTest assimp::assimp)