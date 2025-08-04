#pragma once

#include "map.hpp"
#include <deque>
#include <raylib.h>
#include <raymath.h>

class CameraM;

class Player {

private:
  Vector2 _pos;
  Vector2 _velocity;
  float _size;
  std::deque<Vector2> _trace;
  int _trace_length = 50;
  float _speed;
  float _run_speed_modifier;


public:
  Player(Vector2 init_pos = {0, 0}, float init_speed = 1,
         float init_run_modifier = 2.5, float size = 25) {
    _pos = init_pos;
    _speed = init_speed;
    _run_speed_modifier = init_run_modifier;
    _size = size;
  }

  void Draw(CameraM cam);
  void Update(const Map &map);
  const Vector2 get_pos();
  float get_angle(CameraM &cam);
  const Vector2 get_velocity();
};
