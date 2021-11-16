#pragma once

#include "raylib.h"
#include <vector>
#include "Snake.hpp"

class Fruit 
{
public:
    Fruit();
    void Init(Snake snake);
    void Update();
    void Draw();
    Vector2 GetPosition();

private:
    int tile_size;
    int screen_width;
    int screen_height;

    Vector2 position;
};