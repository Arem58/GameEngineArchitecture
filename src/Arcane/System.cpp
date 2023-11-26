#include <print.h>
#include <SDL2/SDL.h>
#include <FastNoise.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "System.h"
#include "Components.h"

#include "ECS/Entity.h"
#include "ECS/Componets.h"
#include "Game/Graphics/TextureManager.h"

SpriteSetupSystem::SpriteSetupSystem(SDL_Renderer *renderer)
    : renderer(renderer) {}

SpriteSetupSystem::~SpriteSetupSystem()
{
    auto view = scene->r.view<SpriteComponent>();

    for (auto entity : view)
    {
        const auto spriteComponent = view.get<SpriteComponent>(entity);
        TextureManager::UnloadTexture(spriteComponent.name, spriteComponent.shader.name);
    }
}

void SpriteSetupSystem::run()
{
    auto view = scene->r.view<SpriteComponent>();

    for (auto entity : view)
    {
        const auto spriteComponent = view.get<SpriteComponent>(entity);
        TextureManager::LoadTexture(spriteComponent.name, renderer, spriteComponent.shader);
    }
}

void SpriteRenderSystem::run(SDL_Renderer *renderer)
{
    auto view = scene->r.view<TransformComponent, SpriteComponent>();

    for (auto entity : view)
    {
        const auto spriteComponent = view.get<SpriteComponent>(entity);
        const auto transformComponent = view.get<TransformComponent>(entity);

        Texture *texture = TextureManager::GetTexture(spriteComponent.name, spriteComponent.shader.name);

        SDL_Rect clip = {
            spriteComponent.xIndex * spriteComponent.size,
            spriteComponent.yIndex * spriteComponent.size,
            spriteComponent.size,
            spriteComponent.size};

        int scale = 5;

        texture->render(
            transformComponent.position.x * scale,
            transformComponent.position.y * scale,
            48 * scale,
            48 * scale,
            &clip);
    }
}

void SpriteUpdateSystem::run(double dT)
{
    auto view = scene->r.view<SpriteComponent>();

    Uint32 now = SDL_GetTicks();

    for (auto entity : view)
    {
        auto &spriteComponent = view.get<SpriteComponent>(entity);

        if (spriteComponent.animationFrames > 0)
        {
            float timeSinceLastUpdate = now - spriteComponent.lastUpdate;

            int framesToUpdate = static_cast<int>(
                timeSinceLastUpdate /
                spriteComponent.animationDuration * spriteComponent.animationFrames);

            if (framesToUpdate > 0)
            {
                spriteComponent.xIndex += framesToUpdate;
                spriteComponent.xIndex %= spriteComponent.animationFrames;
                spriteComponent.lastUpdate = now;
            }
        }
    }
}

TilemapSetupSystem::TilemapSetupSystem(SDL_Renderer *renderer)
    : renderer(renderer) {}

TilemapSetupSystem::~TilemapSetupSystem() {}

void TilemapSetupSystem::run()
{
    auto &tilemapComponent = scene->world->get<TilemapComponent>();
    tilemapComponent.width = 50;
    tilemapComponent.height = 38;
    tilemapComponent.tileSize = 16;
    tilemapComponent.tilemap.resize(tilemapComponent.width * tilemapComponent.height);

    // Grama
    Texture *grama = TextureManager::LoadTexture("Sprites/Tiles/grama_001_16.png", renderer);
    Texture *grama2 = TextureManager::LoadTexture("Sprites/Tiles/grama_002_16.png", renderer);
    Texture *grama3 = TextureManager::LoadTexture("Sprites/Tiles/grama_003_16.png", renderer);

    // Tierra
    Texture *tierra = TextureManager::LoadTexture("Sprites/Tiles/jungle_001_16.png", renderer);
    Texture *tierra2 = TextureManager::LoadTexture("Sprites/Tiles/jungle_002_16.png", renderer);
    Texture *tierra3 = TextureManager::LoadTexture("Sprites/Tiles/jungle_003_16.png", renderer);
    Texture *tierra4 = TextureManager::LoadTexture("Sprites/Tiles/jungle_004_16.png", renderer);
    Texture *tierra5 = TextureManager::LoadTexture("Sprites/Tiles/jungle_005_16.png", renderer);
    Texture *tierra6 = TextureManager::LoadTexture("Sprites/Tiles/jungle_006_16.png", renderer);
    Texture *tierra7 = TextureManager::LoadTexture("Sprites/Tiles/jungle_007_16.png", renderer);
    Texture *tierra8 = TextureManager::LoadTexture("Sprites/Tiles/jungle_008_16.png", renderer);
    Texture *tierra9 = TextureManager::LoadTexture("Sprites/Tiles/jungle_009_16.png", renderer);
    Texture *tierra10 = TextureManager::LoadTexture("Sprites/Tiles/jungle_010_16.png", renderer);
    Texture *tierra11 = TextureManager::LoadTexture("Sprites/Tiles/tierra_001_16.png", renderer);

    // pared externa
    Texture *paredEx = TextureManager::LoadTexture("Sprites/Tiles/rockwall_001_16.png", renderer);
    Texture *paredEx2 = TextureManager::LoadTexture("Sprites/Tiles/rockwall_002_16.png", renderer);
    Texture *paredEx3 = TextureManager::LoadTexture("Sprites/Tiles/rockwall_003_16.png", renderer);

    // piso interno
    Texture *piso = TextureManager::LoadTexture("Sprites/Tiles/piso-0001.png", renderer);
    Texture *piso2 = TextureManager::LoadTexture("Sprites/Tiles/piso-0002.png", renderer);
    Texture *piso3 = TextureManager::LoadTexture("Sprites/Tiles/piso-0003.png", renderer);
    Texture *piso4 = TextureManager::LoadTexture("Sprites/Tiles/piso-0004.png", renderer);

    // pared interna 
    Texture *paredIn = TextureManager::LoadTexture("Sprites/Tiles/pared.png", renderer);


    std::ifstream mapFile("assets/Map/map.txt");
    std::string line;
    int y = 0;

    while (std::getline(mapFile, line) && y < tilemapComponent.height)
    {
        for (int x = 0; x < line.length() && x < tilemapComponent.width; x++)
        {
            int index = y * tilemapComponent.width + x;
            Tile &tile = tilemapComponent.tilemap[index];

            switch (line[x])
            {
            case 'A':
                tile.texture = grama;
                break;
            case 'B':
                tile.texture = grama2;
                break;
            case 'C':
                tile.texture = grama3;
                break;
            case 'D':
                tile.texture = tierra;
                break;
            case 'E':
                tile.texture = tierra2;
                break;
            case 'F':
                tile.texture = tierra3;
                break;
            case 'G':
                tile.texture = tierra4;
                break;
            case 'H':
                tile.texture = tierra5;
                break;
            case 'I':
                tile.texture = tierra6;
                break;
            case 'J':
                tile.texture = tierra7;
                break;
            case 'K':
                tile.texture = tierra8;
                break;
            case 'L':
                tile.texture = tierra9;
                break;
            case 'M':
                tile.texture = tierra10;
                break;
            case 'N':
                tile.texture = tierra11;
                break;
            case 'O':
                tile.texture = paredEx;
                break;
            case 'P':
                tile.texture = paredEx2;
                break;
            case 'Q':
                tile.texture = paredEx3;
                break;
            case 'R':
                tile.texture = piso;
                break;
            case 'S':
                tile.texture = piso2;
                break;
            case 'T':
                tile.texture = piso3;
                break;
            case 'U':
                tile.texture = piso4;
                break;
            case 'w':
                tile.texture = paredIn;
                break;
            }
        }
        ++y;
    }
}

void TilemapRenderSystem::run(SDL_Renderer *renderer)
{
    auto &tilemapComponent = scene->world->get<TilemapComponent>();
    int width = tilemapComponent.width;
    int height = tilemapComponent.height;
    int size = tilemapComponent.tileSize;
    int scale = 5;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Tile &tile = tilemapComponent.tilemap[y * width + x];
            if (tile.texture)
            {
                tile.texture->render(
                    x * size * scale,
                    y * size * scale,
                    size * scale,
                    size * scale);
            }
        }
    }
}

// set up con noise
// void TilemapSetupSystem::run()
// {
//     auto &tilemapComponent = scene->world->get<TilemapComponent>();
//     tilemapComponent.width = 50;
//     tilemapComponent.height = 38;
//     tilemapComponent.tileSize = 16;
//     tilemapComponent.tilemap.resize(tilemapComponent.width * tilemapComponent.height);

//     Texture *waterTexture = TextureManager::LoadTexture("Sprites/Tiles/Water.png", renderer);
//     Texture *grassTexture = TextureManager::LoadTexture("Sprites/Tiles/Grass.png", renderer);

//     FastNoiseLite noise;
//     noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

//     std::srand(std::time(nullptr));
//     float offsetX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
//     float offsetY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
//     float zoom = 20.0f;

//     for (int y = 0; y < tilemapComponent.height; y++)
//     {
//         for (int x = 0; x < tilemapComponent.width; x++)
//         {
//             float factor = noise.GetNoise(
//                 static_cast<float>(x + offsetX) * zoom,
//                 static_cast<float>(y + offsetY) * zoom);

//             int index = y * tilemapComponent.width + x;
//             Tile &tile = tilemapComponent.tilemap[index];

//             if (factor < 0.5)
//             {
//                 tile.texture = grassTexture;
//             }
//             else
//             {
//                 tile.texture = waterTexture;
//             }
//         }
//     }
// }