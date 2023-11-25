#include "ECS/Componets.h"

struct SizeComponent 
{
    int w;
    int h;
};

struct ColliderComponent
{
    bool triggered;
};

struct PlayerComponent
{
    short moveSpeed;
    char playerNumber; // 2 es para IA (1, player 1 , 2, player 2)
};


