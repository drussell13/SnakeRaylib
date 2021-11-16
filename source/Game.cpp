#include "Game.hpp"
#include "DEFINITIONS.hpp"

Game::Game()
{
    screen_width = SCREEN_WIDTH;
    screen_height = SCREEN_HEIGHT;
    tile_size = TILE_SIZE;
    
    Init();
}

void Game::Init()
{
    frames_counter = 0;
    gamestate = GameStates::TITLE;

    snake.Init();
    fruit.Init(snake);
}

void Game::Run()
{
    InitWindow(screen_width, screen_height, "SnakeRaylib");
    SetTargetFPS(10);
    
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    CloseWindow();
}


void Game::Draw()
{
    BeginDrawing();
    switch (gamestate)
    {
        ClearBackground(RAYWHITE);
        case GameStates::LOGO:
            DrawRectangle(0, 0, screen_width, screen_height, RAYWHITE);
            DrawText("Hello, welcome to SnakeRayLib", 190, 200, 20, LIGHTGRAY);
            break;
        case GameStates::TITLE:
            DrawRectangle(0, 0, screen_width, screen_height, GREEN);
            DrawText("Press any key to begin. Use the arrow keys to move.", 190, 200, 20, LIGHTGRAY);
            break;
        case GameStates::GAMEPLAY:
            DrawRectangle(0, 0, screen_width, screen_height, RAYWHITE);
            DrawGrid();
            snake.Draw();
            fruit.Draw();
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


void Game::DrawGrid()
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


void Game::Update()
{
    switch(gamestate)
    {
        case GameStates::LOGO:
            frames_counter++;
            if (frames_counter > 24)
            {
                gamestate = GameStates::TITLE;
            }
            break;
        case GameStates::TITLE:
            if (IsKeyPressed(KEY_ENTER))
            {
                gamestate = GameStates::GAMEPLAY;
            }
            break;
        case GameStates::GAMEPLAY:
            // Update direction
            if (IsKeyDown(KEY_RIGHT)) snake.ChangeDirection(Directions::RIGHT);
            if (IsKeyDown(KEY_LEFT)) snake.ChangeDirection(Directions::LEFT);
            if (IsKeyDown(KEY_UP)) snake.ChangeDirection(Directions::UP);
            if (IsKeyDown(KEY_DOWN)) snake.ChangeDirection(Directions::DOWN);
            // Move snake body
            snake.Update();

            // Collisions should be down here actually.
            if (ObjectOutOfBounds(snake.GetHead())) gamestate = GameStates::ENDING;
            if (snake.CollidesWithTail()) gamestate = GameStates::ENDING;
            
            // Check if fruit eaten
            if (snake.ObjectCollidesWithSnake(fruit.GetPosition()))
            {
                snake.Grow();
                fruit.Init(snake);

            }
            break;
        case GameStates::ENDING:
            if (IsKeyPressed(KEY_ENTER))
            {
                Init();  // Restart game
                gamestate = GameStates::TITLE;
            }
            break;
        default: break;
    }
}


bool Game::ObjectOutOfBounds(Vector2 obj)
{
    bool out_of_bounds = false;
    if (obj.x < 0) out_of_bounds = true;
    if (obj.y < 0) out_of_bounds = true;
    if ((obj.x + tile_size) > screen_width) out_of_bounds = true;
    if ((obj.y + tile_size) > screen_height) out_of_bounds = true;

    return out_of_bounds;
}