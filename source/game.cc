#include "raylib.h"

#include "../headers/game.hpp"
#include "../headers/ui.hpp"

Game::Game() {
  InitWindow(DefaultScreenSize.width, DefaultScreenSize.height,
             "raylib [core] example - basic window");
  SetTargetFPS(144);

  player = new Player();
  cam = new CameraM();
  map = new Map("assets/map.txt");
  mbullets = new Bullets();

  UI::Init();
}

Game::~Game() {
  UI::Cleanup();
  CloseWindow();
}

void Game::Run() {
  while (!WindowShouldClose()) {
    Update();
    Draw();
  }
}

void Game::Update() {
  float dt = GetFrameTime();

  player->Update(*map);
  cam->Update();
  mbullets->Update(*player, *map, *cam, dt);
}

void Game::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);

  map->Draw(cam->get_cam());

  player->Draw(*cam);
  cam->Draw(player);
  mbullets->Draw(*cam);
  UI::Draw(player);

  EndDrawing();
}

