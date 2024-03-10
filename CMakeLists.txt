cmake_minimum_required(VERSION 3.23)
project(delve)

# Set the path to Vcpkg's CMake toolchain file
set(CMAKE_TOOLCHAIN_FILE /opt/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Set the path to your game engine directory
set(ROGUE_ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rogue_engine)

# Add the .cpp files to source
set(SOURCES
    src/main.cpp
    src/MainGame.cpp
)

# Add the source files from the game engine directory
file(GLOB_RECURSE ROGUE_ENGINE_SOURCES ${ROGUE_ENGINE_DIR}/*.cpp)

# Add the executable and specify source files
add_executable(delve ${SOURCES} ${ROGUE_ENGINE_SOURCES})


# Add shader files to be copied to build directory
file(COPY Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Find SDL2 Package
find_package(SDL2 CONFIG REQUIRED)

# Find GLEW package
find_package(GLEW REQUIRED)

# add opengl math library
find_package(glm CONFIG REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include directories for the game engine
target_include_directories(delve PRIVATE ${ROGUE_ENGINE_DIR}/include)

# Link SDL2, GLEW, and OpenGL to delve
target_link_libraries(delve PRIVATE SDL2::SDL2 SDL2::SDL2main
                                    GLEW::GLEW OpenGL::GL glm::glm-header-only)
