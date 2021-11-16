#include "Snake.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

Snake::Snake()
{
    tile_size = TILE_SIZE;
}


void Snake::Init()
{
    int initial_x_tile = (int)(SCREEN_WIDTH/2) / tile_size;
    int initial_y_tile = (int)(SCREEN_HEIGHT/2) / tile_size;

    float initial_x_pos = initial_x_tile * tile_size;
    float initial_y_pos = initial_y_tile * tile_size;

    body.clear();
    int initial_length = 5;
    for (int i=0; i<initial_length; i++)
    {
        body.push_back((Vector2){initial_x_pos - tile_size*i, initial_y_pos});
    }

    current_dir = Directions::RIGHT;
}


Vector2 Snake::GetHead()
{
    return body.at(0);
}


void Snake::ChangeDirection(Directions dir)
{
    std::cout << "Changing direction" << std::endl;

    switch (dir)
    {
        case Directions::RIGHT:
            if (current_dir != Directions::LEFT) current_dir = dir;  // Snake cannot do a 180
            break;
        case Directions::LEFT:
            if (current_dir != Directions::RIGHT) current_dir = dir;
            break;
        case Directions::UP:
            if (current_dir != Directions::DOWN) current_dir = dir;
            break;
        case Directions::DOWN:
            if (current_dir != Directions::UP) current_dir = dir;
            break;
    }

    
}


void Snake::Update()
{
    int delta_x = 0;
    int delta_y = 0;
    switch (current_dir)
    {
        case Directions::RIGHT:
            delta_x = 1;
            break;
        case Directions::LEFT:
            delta_x = -1;
            break;
        case Directions::DOWN:
            delta_y = 1;
            break;
        case Directions::UP:
            delta_y = -1;
            break;
    }

    // Update body
    std::vector<Vector2> prev_body = body;
    for (int i=1; i<body.size(); i++)
    {
        Vector2& piece = body.at(i);
        Vector2& prev_piece = prev_body.at(i-1);
        piece.x = prev_piece.x;
        piece.y = prev_piece.y;
    }
    
    //Update head
    Vector2& head = body.at(0);
    head.x += delta_x * tile_size;
    head.y += delta_y * tile_size;
}


void Snake::Grow()
{
    body.push_back((Vector2){0, 0}); // co-ords don't matter, they will be set in Update()
}


void Snake::Draw()
{
    for (int i=0; i<body.size(); i++)
    {
        Vector2 snake_tile = body.at(i);
        DrawRectangle(snake_tile.x, snake_tile.y, tile_size, tile_size, BLACK);
    }
}


bool Snake::CollidesWithTail()
{
    Vector2& head = body.at(0);
    
    for (int i=1; i<body.size(); i++)
    {
        Vector2& piece = body.at(i);

        bool same_x = piece.x == head.x;
        bool same_y = piece.y == head.y;

        if (same_x && same_y)
        {
            return true;
        }
    }

    return false;
}


bool Snake::ObjectCollidesWithSnake(Vector2 obj)
{
    for (int i=0; i<body.size(); i++)
    {
        Vector2& piece = body.at(i);

        bool same_x = piece.x == obj.x;
        bool same_y = piece.y == obj.y;

        if (same_x && same_y)
        {
            return true;
        }
    }

    return false;
}