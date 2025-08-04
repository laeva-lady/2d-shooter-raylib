#pragma once

#include <raylib.h>
bool is_rects_colliding(Rectangle rect1, Rectangle rect2);
bool is_circle_colliding_with_rect(Vector2 circle_pos, float circle_radius,
                                   Rectangle rect);
