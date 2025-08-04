#include "../headers/collisions.h"
#include <raylib.h>

bool is_rects_colliding(Rectangle rect1, Rectangle rect2) {

  auto r1x = rect1.x;
  auto r1w = rect1.width;
  auto r1y = rect1.y;
  auto r1h = rect1.height;

  auto r2x = rect2.x;
  auto r2w = rect2.width;
  auto r2y = rect2.y;
  auto r2h = rect2.height;

  if (r1x + r1w >= r2x && // r1 right edge past r2 left
      r1x <= r2x + r2w && // r1 left edge past r2 right
      r1y + r1h >= r2y && // r1 top edge past r2 bottom
      r1y <= r2y + r2h) { // r1 bottom edge past r2 top
    return true;
  }
  return false;
}

bool is_circle_colliding_with_rect(Vector2 circle_pos, float circle_radius,
                                   Rectangle rect) {
  return CheckCollisionCircleRec(circle_pos, circle_radius, rect);
}
