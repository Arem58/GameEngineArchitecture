#pragma once
#include <string>
#include <functional>
#include <SDL.h>

enum class ShaderType {
    Red, 
    Negative,
    Sepia
};

struct PixelShader {
    std::function<Uint32(Uint32)> func;
    std::string name;
};

PixelShader getShader(ShaderType type);