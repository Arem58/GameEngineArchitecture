#include <print.h>
#include "Pong.h"

Pong::Pong(const char *name, int width, int height)
    : Game(name, width, height){

      };

Pong::~Pong(){

};

void Pong::setup()
{
    print("pong setup");

    for (int i = 0; i < 4; i++)
    {
        keyState[i] = false;
    }

    // Pelota
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.w = 20;
    ball.h = 20;

    // Paddle derecha
    right_paddle.x = screen_width - 20;
    right_paddle.y = (screen_height / 2) - 50;
    right_paddle.w = 20;
    right_paddle.h = 100;

    // Paddle izquierda
    left_paddle.x = 0;
    left_paddle.y = (screen_height / 2) - 50;
    left_paddle.w = 20;
    left_paddle.h = 100;

    ball_speed_x = 2;
    ball_speed_y = 2;
};

void Pong::update()
{
    print("pong update");

    // Rebote horizontal
    // Lado izquierdo
    if (ball.x <= left_paddle.x + left_paddle.w)
    {
        if (ball.y + ball.h >= left_paddle.y && ball.y <= left_paddle.y + left_paddle.h)
        {
            ball_speed_x *= -1;

            ball_speed_x *= 1.5f;
            ball_speed_y *= 1.5f;
        }
        else
        {
            print("Jugador 2 gana!!!");
            isRunning = false;
        }
    }
    // Lado derecho
    if (ball.x >= right_paddle.x - ball.w)
    {
        if (ball.y + ball.h >= right_paddle.y && ball.y <= right_paddle.y + right_paddle.h)
        {
            ball_speed_x *= -1;

            ball_speed_x *= 1.5f;
            ball_speed_y *= 1.5f;
        }
        else
        {
            print("Jugador 1 gana!!!");
            isRunning = false;
        }
    }

    // Rebote vertical
    if (ball.y <= 0)
    {
        ball_speed_y *= -1;

        ball_speed_x *= 1.5f;
        ball_speed_y *= 1.5f;
    }
    if (ball.y >= screen_height - ball.h)
    {
        ball_speed_y *= -1;

        ball_speed_x *= 1.5f;
        ball_speed_y *= 1.5f;
    }

    ball.x += ball_speed_x;
    ball.y += ball_speed_y;

    // Movimiento de paddle
    // PLAYER 1
    if (keyState[UP])
        right_paddle.y -= 5;
    if (keyState[DOWN])
        right_paddle.y += 5;
    // PLAYER 2
    if (keyState[W])
        left_paddle.y -= 5;
    if (keyState[S])
        left_paddle.y += 5;
};

void Pong::render()
{
    print("pong render");

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);

    SDL_RenderClear(renderer);

    // draw game
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderFillRect(renderer, &right_paddle);
    SDL_RenderFillRect(renderer, &left_paddle);

    SDL_RenderPresent(renderer);
};

void Pong::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            bool pressed = event.type == SDL_KEYDOWN;
            switch (event.key.keysym.sym)
            {
            case SDLK_i:
                keyState[UP] = pressed;
                break;

            case SDLK_k:
                keyState[DOWN] = pressed;
                break;

            case SDLK_w:
                keyState[W] = pressed;
                break;

            case SDLK_s:
                keyState[S] = pressed;
                break;
            }
        }
    }
};