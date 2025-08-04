#pragma once

#include "map.hpp"
#include "player.hpp"
#include <raylib.h>
#include <vector>

struct Bullet {
  Vector2 _pos;
  Vector2 _velocity;
  float _damage;
  float _radius;
  float _speed;
};

class Bullets {
private:
  std::vector<Bullet> bullets;
  void SpawnBullet(Player &player, CameraM &cam);

public:
  Bullets() {}
  void Update(Player &player, const Map &map, CameraM &cam);
  void Draw(CameraM &cam);
};
