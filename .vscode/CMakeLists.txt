cmake_minimum_required(VERSION 3.10)
project(OpenGLTest)

# Add the directory containing FindAssimp.cmake to the CMake module path
list(APPEND CMAKE_MODULE_PATH "/usr/local/Cellar/assimp/5.4.0/lib/cmake/assimp-5.4")
# list(APPEND CMAKE_MODULE_PATH "/usr/local/Cellar/freetype/2.13.2")

# Find the Assimp package
find_package(assimp REQUIRED)
find_package(Freetype REQUIRED)

# Add your source files
set(SOURCES
    src/main
    # Add your other source files here
)

# Add an executable target
add_executable(OpenGLTest /Users/a5520/Desktop/OpenGLTest/src/main.cpp)

# Link Assimp with your executable
target_link_libraries(OpenGLTest assimp::assimp)

#target_include_directories(OpenGLTest PRIVATE ${FREETYPE_INCLUDE_DIRS})