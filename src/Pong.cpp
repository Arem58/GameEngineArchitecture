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

    ball.x = 20;
    ball.y = 20;
    ball.w = 20;
    ball.h = 20;

    paddle.x = (screen_width / 2) - 50;
    paddle.y = screen_height - 20;
    paddle.w = 100;
    paddle.h = 20;

    ball_speed_x = 2;
    ball_speed_y = 2;
};

void Pong::update()
{
    print("pong update");

    if (ball.x <= 0)
    {
        ball_speed_x *= -1;
    }
    if (ball.x >= screen_width - ball.w)
    {
        ball_speed_x *= -1;
    }
    if (ball.y <= 0)
    {
        ball_speed_y *= -1;
    }
    if (ball.y >= screen_height - ball.h)
    {
        ball_speed_y *= -1;
    }

    ball.x += ball_speed_x;
    ball.y += ball_speed_y;
};

void Pong::render()
{
    print("pong render");

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);

    SDL_RenderClear(renderer);

    // draw game
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderFillRect(renderer, &paddle);

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
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                paddle.x -= 20;
                break;
            
            case SDLK_RIGHT:
                paddle.x += 20;
                break;
            }
        }
    }
};