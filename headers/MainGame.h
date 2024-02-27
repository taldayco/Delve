#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>

enum class GameState { PLAY, EXIT };

class MainGame {
public:
  MainGame();
  ~MainGame();

  void run();

private:
  void initSystems();
  void gameLoop();
  void processInput();
  void drawGame();

  SDL_Window *_window;
  int _screenWidth;
  int _screenHeight;

  GameState _gameState;
};
