cmake_minimum_required(VERSION 3.23)
project(delve)

# Set the path to Vcpkg's CMake toolchain file
set(CMAKE_TOOLCHAIN_FILE /opt/vcpkg/scripts/buildsystems/vcpkg.cmake)

#add the .cpp files to source 
set(SOURCES
  src/main.cpp
  src/Errors.cpp
  src/MainGame.cpp
  src/Sprite.cpp
  src/GLSLProgram.cpp
)

# Add shader files to be copied to build directory
file(COPY Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add the add_executable and specify souce files
add_executable(delve ${SOURCES})

# Find SDL2 Package
find_package(SDL2 CONFIG REQUIRED)

# Find GLEW package
find_package(GLEW REQUIRED)

#Find OpenGL
find_package(OpenGL REQUIRED)

# Link SDL2 to delve
target_link_libraries(delve PRIVATE SDL2::SDL2 SDL2::SDL2main GLEW::GLEW OpenGL::GL)

# Fixing Xorg Dependencies Warning
message(WARNING "You will need to install Xorg dependencies to use feature x11:
  sudo apt install libx11-dev libxft-dev libxext-dev")

# Fixing Wayland Dependencies Warning
message(WARNING "You will need to install Wayland dependencies to use feature wayland:
  sudo apt install libwayland-dev libxkbcommon-dev libegl1-mesa-dev")

# Fixing ibus Dependencies Warning
message(WARNING "You will need to install ibus dependencies to use feature ibus:
  sudo apt install libibus-1.0-dev")
