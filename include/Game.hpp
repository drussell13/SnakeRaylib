#pragma once

#include "raylib.h"
#include "Snake.hpp"
// #include "Fruit.hpp"

enum GameStates {
    LOGO,
    TITLE,
    GAMEPLAY,
    ENDING
};

class Game
{
public:
    Game();
    void Run();

private:
    void Draw();
    void DrawGrid();
    void Update();
    bool ObjectOutOfBounds(Vector2 obj);

private:
    int screen_width;
    int screen_height;

    int tile_size;

    int frames_counter;

    GameStates gamestate;

    Snake snake;
    // Fruit fruit;
    
};