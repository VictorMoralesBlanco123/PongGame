#include <iostream>
#include <raylib.h>
#include <string>

using namespace std;

int paddle_hit(int ball_x, int ball_y, int ball_radius, int ball_speed_x, int paddleHeight, int paddle_y)
{
    bool within_bounds = ball_y + ball_radius >= paddle_y - 1 && ball_y + ball_radius <= paddle_y + paddleHeight + 1;
    if (ball_x + ball_radius >= 875 && within_bounds)
    {
        ball_speed_x *= -1;
    }

    if (ball_x - ball_radius <= 25 && within_bounds)
    {
        ball_speed_x *= -1;
    }

    return ball_speed_x;
}

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
            ball_x = 450;
            ball_y = 200;
        }

        if (ball_x - ball_radius <= 0)
        {
            ball_speed_x *= -1;
            player2_score += 1;
            ball_x = 450;
            ball_y = 200;
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
        DrawRectangle(15, paddle1_y, paddleWidth, paddleHeight, BLUE);
        DrawRectangle(875, paddle2_y, paddleWidth, paddleHeight, RED);

        ball_speed_x = paddle_hit(ball_x, ball_y, ball_radius, ball_speed_x, paddleHeight, paddle1_y);
        ball_speed_x = paddle_hit(ball_x, ball_y, ball_radius, ball_speed_x, paddleHeight, paddle2_y);

        if (player1_score < 3 || player2_score < 3)
        {
            DrawText(TextFormat("%d : %d", player1_score, player2_score), 400, 300, 40, GREEN);
        }

        if (player1_score == 3 || player2_score == 3)
        {
            if (player1_score == 3)
            {
                DrawText("Blue Wins", 350, 100, 40, BLUE);
            }
            else
            {
                DrawText("Red Wins", 350, 100, 40, RED);
            }
            DrawText("Press SPACE to restart game", 150, 400, 40, GREEN);
            ball_speed_x = 0;
            ball_speed_y = 0;
        }

        if (IsKeyDown(KEY_SPACE))
        {
            player1_score = 0;
            player2_score = 0;
            ball_speed_x = 5;
            ball_speed_y = 5;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}