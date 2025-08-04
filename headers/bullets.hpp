#pragma once

#include "map.hpp"
#include "player.hpp"
#include <raylib.h>
#include <vector>

const float c_default_speed_bullet = 2000;

struct Bullet {
  Vector2 _pos;
  Vector2 _velocity;
  float _damage;
  float _radius;
  float _speed;
  int _bounces_left;
  Color _color;
};

Bullet new_bullet(Vector2 _pos, Vector2 _velocity, float _damage, float _radius,
                  float _speed, int _bounces_left, Color _color);

class Bullets {
private:
  std::vector<Bullet> bullets;
  void SpawnBullet(Player &player, CameraM &cam);

public:
  Bullets() {}
  void Update(Player &player, const Map &map, CameraM &cam, float deltaTime);
  void Draw(CameraM &cam);
};
