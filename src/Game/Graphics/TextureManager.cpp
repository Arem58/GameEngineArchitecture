#include "TextureManager.h"
#include <iostream>
#include <print.h>

std::map<std::string, Texture *> TextureManager::textures;

Texture *TextureManager::LoadTexture(const std::string &filename, SDL_Renderer *renderer, PixelShader shader)
{
    if (textures.count(filename + shader.name) > 0)
    {
        return textures[filename + shader.name];
    }

    Texture *tex = new Texture(renderer);
    tex->load("assets/" + filename, shader);

    textures[filename + shader.name] = tex;
    return tex;
}
void TextureManager::UnloadTexture(const std::string &filename, const std::string &shaderName)
{
    if (textures.count(filename + shaderName) > 0)
    {
        delete textures[filename + shaderName];
        textures.erase(filename + shaderName);
    }
}
Texture *TextureManager::GetTexture(const std::string &filename, const std::string &shaderName)
{
    if (textures.count(filename + shaderName) > 0)
    {
        return textures[filename + shaderName];
    }
    return nullptr;
}