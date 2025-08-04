#pragma once

#include "../headers/player.hpp"
#include "camera.hpp"
#include "map.hpp"
#include <raylib.h>

struct Size {
  int height;
  int width;
};

class Game {
private:
  const Size DefaultScreenSize = {700, 1200};

  Player *player;
  CameraM *cam;
  Map *map;

  void Draw();

public:
  Game();
  ~Game();

  void Run();
  void Update();
};
