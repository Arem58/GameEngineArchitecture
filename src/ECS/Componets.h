#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "ECS/Entity.h"
#include "Game/Graphics/PixelShader.h"
#include "Game/Graphics/Texture.h"
#include "Game/Graphics/Tile.h"


struct NameComponent
{
    std::string tag;
};

struct TransformComponent
{
    glm::vec2 position;
    // glm::vec2 scale;
    // float rotation;
};

// El transform component siempre se va a mover a traves de este con delta time (pixeles x segundo)
struct SpeedComponent
{
    int x;
    int y;
};

struct SpriteComponent
{
    std::string name;
    int xIndex = 0;
    int yIndex = 0;
    int size = 48;
    int animationFrames = 0;
    int animationDuration = 0;
    PixelShader shader = {nullptr, ""};

    Uint32 lastUpdate = 0;
};

struct TilemapComponent {
  std::vector<Tile> tilemap;
  int width;
  int height;
  int tileSize;
};
