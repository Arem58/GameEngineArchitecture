#pragma once
#include "Game/Game.h"

// Screen dimension contanst
const int SCREEN_WIDTH = 649;
const int SCREEN_HEIGHT = 480;

class Pong : public Game
{
public:
    Pong();
    ~Pong();

private:
    Scene* createGameplayScene();
};