#include <iostream>
#include <raylib.h>
#include <string>

using namespace std;

int main()
{

    const int screenWidth = 900;
    const int screenHeight = 600;
    int ball_x = 450;
    int ball_y = 300;
    int ball_speed_x = 5;
    int ball_speed_y = 5;
    int ball_radius = 8;
    int paddleWidth = 10;
    int paddleHeight = 80;
    int player1_score = 0;
    int player2_score = 0;
    int paddle1_y = 0;
    int paddle2_y = 0;

    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;


        // Ball goes left and right

        if (ball_x + ball_radius >= screenWidth)
        {
            ball_speed_x *= -1;
            player1_score += 1;
            cout << "player1 " << player1_score << endl;
        }
        
        if (ball_x - ball_radius <= 0)
        {
            ball_speed_x *= -1;
            player2_score += 1;
            cout << "player2 " << player2_score << endl;
        }

        // ball goes up and down
        if (ball_y + ball_radius >= screenHeight || ball_y - ball_radius <= 0)
        {
            ball_speed_y *= -1;
        }

        if (IsKeyDown(KEY_DOWN) && paddle2_y < 520)
        {
            paddle2_y += 8;
        }

        if (IsKeyDown(KEY_UP) && paddle2_y > 0)
        {
            paddle2_y -= 8;
        }

        if (IsKeyDown(KEY_S) && paddle1_y < 520)
        {
            paddle1_y += 8;
        }

        if (IsKeyDown(KEY_W) && paddle1_y > 0)
        {
            paddle1_y -= 8;
        }

        DrawCircle(ball_x, ball_y, ball_radius, WHITE);
        DrawRectangle(15, paddle1_y, paddleWidth, paddleHeight, WHITE);
        DrawRectangle(875, paddle2_y, paddleWidth, paddleHeight, WHITE);

        // DrawText();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}