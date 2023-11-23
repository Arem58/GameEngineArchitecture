#pragma once
#include "Game/Game.h"

class Pong : public Game
{
public:
    Pong(const char *name, int width, int height);
    ~Pong();

    void setup() override;
    void update() override;
    void render() override;
    void handleEvents() override;

private:
    SDL_Rect ball;
    SDL_Rect left_paddle;
    SDL_Rect right_paddle;
    int ball_speed_x;
    int ball_speed_y;
    bool keyState[4];
    enum keys {UP, DOWN, W, S};
};