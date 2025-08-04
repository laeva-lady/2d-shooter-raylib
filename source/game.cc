#include "raylib.h"

#include "../headers/game.hpp"
#include "../headers/ui.hpp"
#include "../headers/attacks.hpp"

Game::Game() {
  InitWindow(DefaultScreenSize.width, DefaultScreenSize.height,
             "raylib [core] example - basic window");
  SetTargetFPS(144);

  player = new Player();
  cam = new CameraM();
  map = new Map("assets/map.txt");
  mbullets = new Bullets();
  atk = new Attacks();
  waveAtk = new WaveATKs();

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
  atk->Update(*this);
  mbullets->Update(*player, *map, dt);
  waveAtk->Update();
}

void Game::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);

  map->Draw(cam->get_cam());

  mbullets->Draw(*cam);
  waveAtk->Draw(*cam);
  player->Draw(*cam);
  cam->Draw(player);
  UI::Draw(*this, *player);

  EndDrawing();
}
