#include "Fruit.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

Fruit::Fruit()
{
    tile_size = TILE_SIZE;
    screen_width = SCREEN_WIDTH;
    screen_height = SCREEN_HEIGHT;
}

void Fruit::Init(Snake snake)
{
    // TODO fix this generation
    
    float x = 0;
    float y = 0;

    while (true)  // generate fruit position until valid one found
    {
        // should optimise this in future...
        int num_tiles_x = (int)(SCREEN_WIDTH / tile_size);
        int num_tiles_y = (int)(SCREEN_HEIGHT / tile_size);

        float rand_x = rand()%(num_tiles_x);
        float rand_y = rand()%(num_tiles_y);

        if (!snake.ObjectCollidesWithSnake((Vector2){rand_x, rand_y}))
        {
            x = rand_x;
            y = rand_y;
            break;
        }
    }
    std::cout << "Generated fruit at " << x << " " << y << std::endl;
    position = (Vector2){x*tile_size, y*tile_size};
}

void Fruit::Update()
{
    // Might be useful if I incorporate art.
}


void Fruit::Draw()
{
    DrawRectangle(position.x, position.y, tile_size, tile_size, RED);
}


Vector2 Fruit::GetPosition()
{
    return position;
}