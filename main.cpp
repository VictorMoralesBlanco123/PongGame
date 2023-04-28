#include <iostream>
#include <raylib.h>
#include <ctime>

using namespace std;

const int screenWidth = 900;
const int screenHeight = 600;
int ball_x = 443;
int ball_y = 300;
int ball_speed_x = 0;
int ball_speed_y = 0;
int ball_radius = 8;
int paddleWidth = 10;
int paddleHeight = 90;
int player1_score = 0;
int player2_score = 0;
int paddle1_y = 280;
int paddle2_y = 280;
int random_start[] = {1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1};

// This function puts the ball in motion and chooses the direction based on the time and an array of random numbers.
void startGame()
{
    time_t now = time(0);
    int num_rand_x = random_start[now % 60];
    int num_rand_y = random_start[now % 60];
    if (num_rand_x)
    {
        ball_speed_x = 5;
    }
    else
    {
        ball_speed_x = -5;
    };
    if (num_rand_y)
    {
        ball_speed_y = 5;
    }
    else
    {
        ball_speed_y = -5;
    };
}

// This resets the game to the beginning positions
void resetGame()
{
    ball_x = 443;
    ball_y = 300;
    player1_score = 0;
    player2_score = 0;
    paddle1_y = 220;
    paddle2_y = 220;
    startGame();
}

// This bounces the ball when it hits the either of the paddles
int paddleHit(int paddle_y)
{
    bool within_bounds = ball_y - ball_radius >= paddle_y && ball_y + ball_radius <= paddle_y + paddleHeight;
    if (ball_x + ball_radius >= 875 && within_bounds && ball_speed_x > 0)
    {
        ball_speed_x *= -1;
    }

    if (ball_x - ball_radius <= 25 && within_bounds && ball_speed_x < 0)
    {
        ball_speed_x *= -1;
    }

    return ball_speed_x;
}

int main()
{

    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

    int count = 0;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        if (count == 0)
        {
            DrawText("Press SPACE to start game", 150, 400, 40, GREEN);
            if (IsKeyDown(KEY_SPACE))
            {
                startGame();
                count++;
            }
        }

        // Player 1's score counter
        if (ball_x + ball_radius >= screenWidth)
        {
            ball_speed_x *= -1;
            player1_score += 1;
            ball_x = 450;
            ball_y = 200;
        }

        // Player 2's score counter
        if (ball_x - ball_radius <= 0)
        {
            ball_speed_x *= -1;
            player2_score += 1;
            ball_x = 450;
            ball_y = 200;
        }

        // Makes the bounce off the top and bottom of screen.
        if (ball_y + ball_radius >= screenHeight || ball_y - ball_radius <= 0)
        {
            ball_speed_y *= -1;
        }

        // Moves paddle 2 down
        if (IsKeyDown(KEY_DOWN) && paddle2_y < 520)
        {
            paddle2_y += 8;
        }

        // Moves paddle 2 up
        if (IsKeyDown(KEY_UP) && paddle2_y > 0)
        {
            paddle2_y -= 8;
        }

        // Moves paddle 1 down
        if (IsKeyDown(KEY_S) && paddle1_y < 520)
        {
            paddle1_y += 8;
        }

        // Moves paddle 1 up
        if (IsKeyDown(KEY_W) && paddle1_y > 0)
        {
            paddle1_y -= 8;
        }

        // Constructs objects
        DrawCircle(ball_x, ball_y, ball_radius, WHITE);
        DrawRectangle(15, paddle1_y, paddleWidth, paddleHeight, BLUE);
        DrawRectangle(875, paddle2_y, paddleWidth, paddleHeight, RED);

        ball_speed_x = paddleHit(paddle1_y);
        ball_speed_x = paddleHit(paddle2_y);

        // These two lines move the ball
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        // This is the scoreboard
        if (player1_score < 3 || player2_score < 3)
        {
            DrawText(TextFormat("%d : %d", player1_score, player2_score), 400, 300, 40, GREEN);
        }

        // Determines the winner and prints it on the screen
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
            if (IsKeyDown(KEY_SPACE))
            {
                resetGame();
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}