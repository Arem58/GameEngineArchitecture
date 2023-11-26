#pragma once

#include <print.h>
#include "ECS/System.h"

class HelloSystem : public SetupSystem
{
public:
    HelloSystem();
    HelloSystem(const HelloSystem &other);
    ~HelloSystem();

    void run() override;
};

class RectRenderSystem : public RenderSystem
{
public:
    void run(SDL_Renderer *renderer);
};

class MovementUpdateSystem : public UpdateSystem
{
public:
    void run(double dT) override;
};

class PlayerInputEventSystem : public EventSystem
{
public:
    void run(SDL_Event even);
};

class CollisionDetectionUpdateSystem : public UpdateSystem
{
public:
    void run(double dT);
};

class BounceUpdateSystem : public UpdateSystem
{
public:
    void run(double dT);
};

class SpriteSetupSystem : public SetupSystem
{
public:
    SpriteSetupSystem(SDL_Renderer *renderer);
    ~SpriteSetupSystem();

    void run() override;

private:
    SDL_Renderer *renderer;
};

class SpriteUpdateSystem : public UpdateSystem
{
public:
    void run(double dT) override;
};

class SpriteRenderSystem : public RenderSystem
{
public:
    void run(SDL_Renderer *renderer) override;
};

class TilemapSetupSystem : public SetupSystem
{
public:
    TilemapSetupSystem(SDL_Renderer *renderer);
    ~TilemapSetupSystem();

    void run() override;

private:
    SDL_Renderer *renderer;
};

class TilemapRenderSystem : public RenderSystem
{
public:
    void run(SDL_Renderer *renderer) override;
};

class AutoTilingSetupSystem : SetupSystem
{
public:
    void run() override;
};

class PlayerSpriteUpdateSystem : public UpdateSystem
{
public:
    void run(double dT) override;
};

class CameraFollowUpdateSystem : public UpdateSystem
{
public:
    void run(double dT) override;
};

class BoxColliderRenderSystem : public RenderSystem
{
public:
    void run(SDL_Renderer *renderer) override;
};