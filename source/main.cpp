#include "raylib.h"
#include "Game.hpp"
#include <iostream>
#include <vector>

/**
 * Enums + Classes
 */

enum GameStates {
    LOGO,
    TITLE,
    GAMEPLAY,
    ENDING
};

class Snake
{
public:
    std::vector<Vector2> body_positions;

    Snake()
    {
        body_positions = {(Vector2){30, 30}};
    }

    Vector2 GetHead()
    {
        return body_positions[0];
    }

    void ChangePosition(int x, int y)
    {
        body_positions[0] = (Vector2){body_positions[0].x + x, body_positions[0].y + y};
    }
};

class Fruit
{
public:
    Fruit()
    {

    }
};

/**
 * Global Variables
 */
int screen_width;
int screen_height;
int tile_size;
int frames_counter;

Vector2 ball_pos;

GameStates gamestate;

Snake snake;
Fruit fruit;

/**
 * Functions
 */
void InitGame();
void UpdateGame();
void UpdateSnake(int dx, int dy);

void DrawGame();
void DrawGrid();
void DrawSnake();
void DrawFruit();

int main()
{
    InitGame();
    InitWindow(screen_width, screen_height, "SnakeRaylib");
    SetTargetFPS(10);
    
    while (!WindowShouldClose())
    {
        UpdateGame();
        DrawGame();
    }

    CloseWindow();
    return 0;
}

void InitGame()
{
    screen_width = 800;
    screen_height = 600;
    tile_size = 15;
    frames_counter = 0;

    ball_pos = {(float) screen_width/2, (float) screen_height/2};

    gamestate = GameStates::GAMEPLAY;
    // snake = new Snake();
    // fruit = new Fruit;
}

void UpdateGame()
{
    switch(gamestate)
    {
        case GameStates::LOGO:
            frames_counter++;
            if (frames_counter > 12)
            {
                gamestate = GameStates::TITLE;
                std::cout << "going to title" << std::endl;
            }
            break;
        case GameStates::TITLE:
            if (IsKeyPressed(KEY_ENTER))
            {
                gamestate = GameStates::GAMEPLAY;
                std::cout << "going to gameplay" << std::endl;
            }
            break;
        case GameStates::GAMEPLAY:
            if (IsKeyDown(KEY_RIGHT)) UpdateSnake(1, 0);
            if (IsKeyDown(KEY_LEFT)) UpdateSnake(-1, 0);
            if (IsKeyDown(KEY_UP)) UpdateSnake(0, -1);
            if (IsKeyDown(KEY_DOWN)) UpdateSnake(0, 1);
            break;
        case GameStates::ENDING:
            if (IsKeyPressed(KEY_ENTER))
            {
                gamestate = GameStates::TITLE;
                std::cout << "going to title" << std::endl;
            }
            break;
        default: break;
    }
}

void UpdateSnake(int dx, int dy)
{
    snake.ChangePosition(dx*tile_size, dy*tile_size);
}

void DrawGame()
{
    BeginDrawing();
    switch (gamestate)
    {
        ClearBackground(RAYWHITE);
        case GameStates::LOGO:
            ClearBackground(RAYWHITE);
            DrawText("1Welcome to SnakeRaylib, Press any key to begin", 190, 200, 20, LIGHTGRAY);
            break;
        case GameStates::TITLE:
            DrawRectangle(0, 0, screen_width, screen_height, GREEN);
            DrawText("2Welcome to SnakeRaylib, Press any key to begin", 190, 200, 20, LIGHTGRAY);
            break;
        case GameStates::GAMEPLAY:
            DrawRectangle(0, 0, screen_width, screen_height, RAYWHITE);
            DrawGrid();
            DrawSnake();
            DrawFruit();
            break;
        case GameStates::ENDING:
            DrawRectangle(0, 0, screen_width, screen_height, YELLOW);
            DrawText("4Welcome to SnakeRaylib, Press any key to begin", 190, 200, 20, LIGHTGRAY);
            break;
        default:
            DrawText("We22lcome to SnakeRaylib, Press any key to begin", 190, 200, 20, LIGHTGRAY);
    }
    EndDrawing();
}

void DrawGrid()
{
    for (int i=0; i < screen_width/tile_size; i++)
    {
        float x_pos = tile_size*i;
        DrawLineV((Vector2){x_pos, 0}, (Vector2){x_pos, (float) screen_height}, LIGHTGRAY);
    }

    for (int i=0; i < screen_height/tile_size; i++)
    {
        float y_pos = tile_size*i;
        DrawLineV((Vector2){0, y_pos}, (Vector2){(float) screen_width, y_pos}, LIGHTGRAY);
    }
}

void DrawSnake()
{
    Vector2 snake_pos = snake.GetHead();
    DrawRectangle(snake_pos.x, snake_pos.y, snake_pos.x + tile_size, snake_pos.y + tile_size, BLACK);
}

void DrawFruit()
{

}