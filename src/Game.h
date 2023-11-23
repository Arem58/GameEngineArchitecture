#pragma once
#include <SDL2/SDL.h>
#include <string>

class Game
{
public:
    Game(const char *name, int width, int height);
    ~Game();

    virtual void setup() = 0;
    void frameStart();
    void frameEnd();
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    bool running();

    void run();

protected:
    bool isRunning;
    int width;
    int height;

    SDL_Window *window;
    SDL_Renderer *renderer;

    int screen_width;
    int screen_height;

    // FPS
    double FPS;
    float frameDuration;
    int frameCount;
    int frameCountPerSecond;
    Uint32 frameStartTimestamp;
    Uint32 frameEndTimestamp;
    Uint32 lastFPSUpdate;

    //delta time
    float dT;
};