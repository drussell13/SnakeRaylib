#pragma once

#include "raylib.h"
#include <vector>

enum Directions 
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake
{
public:
    Snake();

    void Init();
    Vector2 GetHead();
    void Draw();
    void Update();
    void ChangeDirection(Directions dir);
    void Grow();
    
    bool CollidesWithTail();
    bool ObjectCollidesWithSnake(Vector2 obj);

private:
    int tile_size;
    Directions current_dir;
    std::vector<Vector2> body;
};