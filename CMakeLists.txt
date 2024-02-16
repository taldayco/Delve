cmake_minimum_required(VERSION 3.23)


project(delve)


add-executables(delve src/main.cpp)


# Find SDL2 Package
find_package(SDL2 CONFIG REQUIRED)

#Link SDL2 to delve
target_link_libraries(delve PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
