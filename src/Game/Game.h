#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Scene/Scene.h"

class Game
{
public:
    Game(const char *name, int width, int height);
    ~Game();

    void setup();
    void frameStart();
    void frameEnd();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

    void run();

    void setScene(Scene* newScene);
    Scene* getCurrentScene() const;

protected:
    bool isRunning;

    SDL_Window* window;
    SDL_Renderer* renderer;

    int screen_width;
    int screen_height;

    // FPS
    Uint32 frameStartTimestamp;
    Uint32 frameEndTimestamp;
    float frameDuration;

    int frameCount;
    Uint32 lastFPSUpdateTime;
    float FPS;

    // delta time 
    float dT;

    // scene logic
    Scene* currentScene;
};