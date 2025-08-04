#include "raylib.h"
#include "raymath.h"

#include "../headers/camera.hpp"
#include "../headers/player.hpp"

void CameraM::Update() {

  // Translate based on mouse right click
  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f / camera.zoom);
    camera.target = Vector2Add(camera.target, delta);
  }

  // Zoom based on mouse wheel
  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    // Get the world point that is under the mouse
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

    // Set the offset to where the mouse is
    camera.offset = GetMousePosition();

    // Set the target to match, so that the camera maps the world space
    // point under the cursor to the screen space point under the cursor at
    // any zoom
    camera.target = mouseWorldPos;

    // Zoom increment
    // Uses log scaling to provide consistent zoom speed
    float scale = 0.2f * wheel;
    camera.zoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f);
  }
}
void CameraM::Draw(Player *p) {
  Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

  DrawCircleV(GetWorldToScreen2D(mouseWorldPos, camera), 2, GREEN);
  auto diff_vec = mouseWorldPos - p->get_pos();

  DrawTextEx(GetFontDefault(),
             TextFormat("[%.1f, %.1f]", diff_vec.x, diff_vec.y),
             Vector2Add(GetMousePosition(), (Vector2){-44, -24}), 20, 2, WHITE);
}
