Set Up Project:

- install python3-jinja2, vcpkg, cmake, and glew.
- cd into the dir with the vcpkg executable.
- run "./vcpkg install sdl2:64-linux"

Build Process:

- cd into your build directory.
- run "cmake .. --preset debug"
- run "cmake --build ."

Remember:
when referencing filepaths in your code, remember that the executable's location is the POV for the compiler.
All filepaths should be relative to that executable, wherever you decide to put it - most likely the build directory.
