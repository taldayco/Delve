cmake_minimum_required(VERSION 3.23)
project(delve)

#add the .cpp files to source 
set(SOURCES
  src/main.cpp
  src/MainGame.cpp
)

#add the add_executable and specify souce files
add_executable(delve ${SOURCES})

# Find SDL2 Package
find_package(SDL2 CONFIG REQUIRED)

# Link SDL2 to delve
target_link_libraries(delve PRIVATE SDL2::SDL2 SDL2::SDL2main)
