Set Up Project:
- install python3-jinja2, vcpkg, cmake, and glew.
- cd into the dir with the vcpkg executable.
- run "./vcpkg install sdl2:64-linux"
- create a symlink between the engine and the game dir:
  "ln -s /path/to/engine /path/to/game/engine"


Build Process:
- cd into your build directory.
- run "cmake .. --preset debug"
- run "cmake --build ."
