#pragma once

#include "raylib.h"
#include "../headers/japanese.hpp"
#include "../headers/player.hpp"

namespace UI {
void Init();
void Draw(Player *p);
void Cleanup();
};
