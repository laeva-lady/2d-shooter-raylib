#include "../headers/player.hpp"
#include "../headers/camera.hpp"
#include "../headers/collisions.h"

void Player::Draw(CameraM cam) {
  BeginMode2D(cam.get_cam());

  for (size_t i = 0; i < _trace.size(); ++i) {
    float alpha = 0.5f * (static_cast<float>(i) / _trace.size());
    DrawCircleV({_trace[i].x, _trace[i].y}, _size - _size / 4,
                Fade(DARKGRAY, alpha));
  }

  DrawCircleV({_pos.x, _pos.y}, _size, MAROON);

  auto out = GetScreenToWorld2D(GetMousePosition(), cam.get_cam());
  Vector2 line_vector = {out.x - _pos.x, out.y - _pos.y};
  float length = Vector2Length(line_vector);

  const float min_length = 50.0f;
  const float max_length = 200.0f;

  if (length > 0.0f) {
    float clamped_length = fmaxf(min_length, fminf(length, max_length));
    Vector2 line_end = Vector2Add(
        _pos, Vector2Scale(Vector2Normalize(line_vector), clamped_length));
    DrawLineV(_pos, line_end, GREEN);
  }

  EndMode2D();
}

void Player::Update(const Map &map) {
  _trace.push_back(_pos);
  if (_trace.size() > _trace_length) {
    _trace.pop_front();
  }
  Vector2 newpos = {0, 0};

  float speed = _speed;
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    speed *= _run_speed_modifier;
  }

  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    newpos.x += speed;
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    newpos.x -= speed;
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    newpos.y -= speed;
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    newpos.y += speed;

  float length = sqrt(pow(newpos.x, 2) + pow(newpos.y, 2));
  if (length > 0) {
    newpos.x /= length;
    newpos.y /= length;

    newpos.x *= speed;
    newpos.y *= speed;
  }

  Vector2 player_pos = {_pos.x, _pos.y};

  Vector2 future_player_pos = {player_pos.x + newpos.x,
                               player_pos.y + newpos.y};

  bool is_colliding = false;
  for (const auto &obs : map.get_obstacles()) {
    if (is_circle_colliding_with_rect(future_player_pos, _size, obs.rect)) {
      is_colliding = true;
      break;
    }
  }

  if (is_colliding) {
    // Collision detected, check X and Y axes separately to allow sliding
    Vector2 future_player_pos_x = {player_pos.x + newpos.x, player_pos.y};
    for (const auto &obs : map.get_obstacles()) {
      if (is_circle_colliding_with_rect(future_player_pos_x, _size, obs.rect)) {
        newpos.x = 0; // Block X movement
        break;
      }
    }

    Vector2 future_player_pos_y = {player_pos.x, player_pos.y + newpos.y};
    for (const auto &obs : map.get_obstacles()) {
      if (is_circle_colliding_with_rect(future_player_pos_y, _size, obs.rect)) {
        newpos.y = 0; // Block Y movement
        break;
      }
    }
  }

  _pos.x += newpos.x;
  _pos.y += newpos.y;
  _velocity = newpos;
}
const Vector2 Player::get_pos() { return _pos; }

const Vector2 Player::get_velocity() { return _velocity; }

float Player::get_angle(CameraM &cam) {
  auto out = GetScreenToWorld2D(GetMousePosition(), cam.get_cam());
  return atan2(out.y - _pos.y, out.x - _pos.x);
}
