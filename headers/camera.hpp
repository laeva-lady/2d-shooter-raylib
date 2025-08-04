#pragma once

#include "raylib.h"
#include "rlgl.h"

class Player;

class CameraM {
  Camera2D camera = {0};

public:
  CameraM() {
    camera.zoom = 1.0f;
    camera.target =
        GetScreenToWorld2D({-(float)GetScreenWidth() / 2, -(float)GetScreenHeight() / 2}, camera);
  }

  Camera2D get_cam() { return camera; }

  void Update();
  void Draw(Player *p);
};
