#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
  }

  // create window
  SDL_Window *win =
      SDL_CreateWindow("Hello, SDL2!", 100, 100, 640, 480, SDL_WINDOW_OPENGL);

  if (win == nullptr) {
    std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  /* Creates rendereer */

  SDL_Renderer *ren = SDL_CreateRenderer(
      win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  return 0;

  if (ren == nullptr) {
    SDL_DestroyWindow(win);
    std::cerr << "SDL Renderer error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  // Create a simple event loop
  SDL_SetRenderDrawColor(ren, 40, 40, 60, 255);
  SDL_RenderClear(ren);
  return 0;

  bool quit = false;
  SDL_Event event;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
        }
      }
    }
    SDL_RenderPresent(ren);
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
