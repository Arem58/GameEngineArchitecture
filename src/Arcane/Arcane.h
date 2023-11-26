#pragma once
#include "Game/Game.h"

// Screen dimension contanst
const int SCREEN_WIDTH = 649;
const int SCREEN_HEIGHT = 480;

class Arcane : public Game
{
public:
    Arcane();
    ~Arcane();

private:
    Scene* createGameplayScene();
};