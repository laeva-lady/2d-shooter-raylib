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
  int _bounces_left;
  Color _color;
};

Bullet new_bullet(Vector2 _pos, Vector2 _velocity, float _damage, float _radius,
                  float _speed, int _bounces_left, Color _color);

class Bullets {
private:
  std::vector<Bullet> bullets;

public:
  float time_since_last_bullet = 0;

  Bullets() {}
  void SpawnBullet(Player &player, CameraM &cam);
  void Update(Player &player, const Map &map, float deltaTime);
  void Draw(CameraM &cam);
};
