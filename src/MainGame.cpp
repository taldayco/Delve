#include "../headers/MainGame.h"
#include "../rogue_engine/headers/rogue_engine.h"

#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

MainGame::MainGame()
    // init list
    : _screenWidth(1024), _screenHeight(768), _time(0),
      _gameState(GameState::PLAY), _maxFPS(60.0f) {
  _camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() {}

void MainGame::run() {
  initSystems();
  // init sprites
  _sprites.push_back(new rogue_engine::Sprite());
  _sprites.back()->init(
      0.0f, 0.0f, _screenWidth / 2.0, _screenHeight / 2.0,
      "../assets/0x72_DungeonTilesetII_v1.6/frames/wizzard_m_idle_anim_f0.png");

  _sprites.push_back(new rogue_engine::Sprite());
  _sprites.back()->init(
      _screenWidth / 2.0, 0.0f, _screenWidth / 2.0, _screenHeight / 2.0,
      "../assets/0x72_DungeonTilesetII_v1.6/frames/wizzard_m_idle_anim_f0.png");

  gameLoop();
}

// ensure the SDL systems we need are ready for use.
void MainGame::initSystems() {

  rogue_engine::init();
  _window.create("Game Engine", _screenWidth, _screenHeight, 0);

  initShaders();
}

void MainGame::initShaders() {
  _colorProgram.compileShaders("../Shaders/colorShading.vert",
                               "../Shaders/colorShading.frag");
  _colorProgram.addAttribute("vertexPosition");
  _colorProgram.addAttribute("vertexColor");
  _colorProgram.addAttribute("vertexUV");
  _colorProgram.linkShaders();
}

// Declares what should happen in the game.
void MainGame::gameLoop() {
  while (_gameState != GameState::EXIT) {

    // used for frame time measuring
    float startTicks = SDL_GetTicks();

    processInput();
    _time += 0.01;

    _camera.update();

    drawGame();

    calculateFPS();

    // print once every ten frames
    static int frameCounter = 0;
    frameCounter++;
    if (frameCounter == 10) {
      std::cout << _fps << std::endl;
      frameCounter = 0;
    }

    // limit the FPS to the max fps
    float frameTicks = SDL_GetTicks() - startTicks;
    if (1000.0f / _maxFPS > frameTicks) {
      SDL_Delay((1000.0f / _maxFPS) - frameTicks);
    }
  }
};

// Monitors input in events in SDL,
void MainGame::processInput() {
  SDL_Event evnt;

  const float CAMERA_SPEED = 20.0f;
  const float SCALE_SPEED = 0.1f;

  // while the user is making inputs:
  while (SDL_PollEvent(&evnt) == true) {
    // figure out what kind of event it is
    switch (evnt.type) {
    // if the event is SDL_QUIT,
    // return 0 from GameState
    case SDL_QUIT:
      _gameState = GameState::EXIT;

    // track the position of the mouse in SDL.
    case SDL_MOUSEMOTION:
      // std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
      break;
    case SDL_KEYDOWN:
      switch (evnt.key.keysym.sym) {
      case SDLK_w:
        _camera.setPosition(_camera.getPosition() +
                            glm::vec2(0.0, CAMERA_SPEED));
        break;
      case SDLK_s:
        _camera.setPosition(_camera.getPosition() +
                            glm::vec2(0.0, -CAMERA_SPEED));
        break;
      case SDLK_a:
        _camera.setPosition(_camera.getPosition() +
                            glm::vec2(-CAMERA_SPEED, 0.0));
        break;
      case SDLK_d:
        _camera.setPosition(_camera.getPosition() +
                            glm::vec2(CAMERA_SPEED, 0.0));
        break;
      case SDLK_q:
        _camera.setScale(_camera.getScale() + SCALE_SPEED);
        break;
      case SDLK_e:
        _camera.setScale(_camera.getScale() - SCALE_SPEED);
        break;
      }
      break;
    }
  };
};

void MainGame::drawGame() {
  // make sure the screen is clear before drawing
  glClearDepth(1.0);
  // clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // enable shader
  _colorProgram.use();

  // use texture unit 0
  glActiveTexture(GL_TEXTURE0);
  // bind texture to texture unit 0
  GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
  // tell shader that texture is in texture unit 0
  glUniform1i(textureLocation, 0);

  // set time variable
  GLuint timeLocation = _colorProgram.getUniformLocation("time");
  glUniform1f(timeLocation, _time);

  // set the camera matrix
  GLint pLocation = _colorProgram.getUniformLocation("P");
  glm::mat4 cameraMatrix = _camera.getCameraMatrix();

  glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

  // draw sprites
  for (int i = 0; i < _sprites.size(); i++) {
    _sprites[i]->draw();
  }

  // unbind
  glBindTexture(GL_TEXTURE_2D, 0);
  _colorProgram.unUse();

  // swap our buffer before drawing
  _window.swapBuffer();
};

// fps counter
void MainGame::calculateFPS() {
  static const int NUM_SAMPLES = 10;
  static float frameTimes[NUM_SAMPLES];
  static int currentFrame = 0;

  static float prevTicks = SDL_GetTicks();
  float currentTicks;
  currentTicks = SDL_GetTicks();

  _frameTime = currentTicks - prevTicks;
  frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

  prevTicks = currentTicks;

  int count;

  currentFrame++;
  if (currentFrame < NUM_SAMPLES) {
    count = currentFrame;
  } else {
    count = NUM_SAMPLES;
  }

  float frameTimeAverage = 0;
  for (int i = 0; i < count; i++) {
    frameTimeAverage += frameTimes[i];
  }
  frameTimeAverage /= count;

  if (frameTimeAverage > 0) {
    _fps = 1000.0f / frameTimeAverage;
  } else {
    _fps = 60.0f;
  }
}
