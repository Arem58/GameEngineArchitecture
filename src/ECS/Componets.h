#pragma once
#include <glm/glm.hpp>
#include <string>

struct NameComponent
{
    std::string name;
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
