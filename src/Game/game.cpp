#include <SDL2/SDL.h>
#include <print.h>
#include "Game.h"
#include "isDefined.h"

Game::Game(const char *title, int width, int height)
{
    print("Game Constructor");

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title, 0, 0, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 200, 255, 255, 1);
    print("Game Start!");

    int MAX_FPS = 60;
    frameDuration = (1.0f / MAX_FPS) * 1000.0f;

    screen_width = width;
    screen_height = height;

    isRunning = true;

    // initial frame count variables
    frameCount = 0;
    lastFPSUpdateTime = 0;
    FPS = 0;

    frameStartTimestamp = 0;
    frameEndTimestamp = 0;
}

Game::~Game()
{
}

void Game::setup()
{
    isDefined(currentScene, "CurrentScene is not initialized");
    currentScene->setup();
}

void Game::frameStart()
{
    print("---------- Frame: ", frameCount, "----------");
    frameStartTimestamp = SDL_GetTicks();

    if (frameEndTimestamp)
    {
        dT = (frameStartTimestamp - frameEndTimestamp) / 1000.0f;
    }
    else
    {
        dT = 0;
    }
    vprint(dT);
}

void Game::frameEnd()
{
    frameEndTimestamp = SDL_GetTicks();

    // Delay
    float actualFrameDuration = frameEndTimestamp - frameStartTimestamp;
    if (actualFrameDuration < frameDuration)
    {
        SDL_Delay(frameDuration - actualFrameDuration);
    }

    // FPS Calculation
    frameCount++;
    // Update FPS counter every second
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastFPSUpdateTime > 1000)
    {
        FPS = frameCount / ((currentTime - lastFPSUpdateTime) / 1000.0f);
        lastFPSUpdateTime = currentTime;
        frameCount = 0;
    }
    print("=================================");
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        currentScene->processEvents(event);
    }
}

void Game::update()
{
    currentScene->update(dT);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    currentScene->render(renderer);

    SDL_RenderPresent(renderer);
    vprint(FPS);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    print("Game Over");
}

bool Game::running()
{
    return isRunning;
}

void Game::run()
{
    setup();

    while (running())
    {
        frameStart();

        handleEvents();
        update();
        render();

        frameEnd();
    }

    clean();
}

void Game::setScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
}

Scene* Game::getCurrentScene() const {
    return currentScene.get();
}