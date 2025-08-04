#pragma once

#include "../headers/player.hpp"
#include "bullets.hpp"
#include "camera.hpp"
#include "map.hpp"
#include "waves-atk.hpp"
#include "attacks.hpp"
#include <raylib.h>

struct Size {
  int height;
  int width;
};

class Game {
private:
  const Size DefaultScreenSize = {700, 1200};

public:
  Player *player;
  CameraM *cam;
  Map *map;
  Bullets *mbullets;
  WaveATKs *waveAtk;

  void Draw();

public:
  Attacks *atk;

  Game();
  ~Game();

  void Run();
  void Update();
};
