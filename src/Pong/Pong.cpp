#include <print.h>
#include "Pong.h"
#include "System.h"
#include "Components.h"

#include "ECS/Entity.h"

Pong::Pong() : Game("Pong", SCREEN_WIDTH, SCREEN_HEIGHT) {
  Scene* gameplayScene = createGameplayScene();
  setScene(gameplayScene);
}

Pong::~Pong() {
    // destructor implementation
}

Scene* Pong::createGameplayScene()
{
  Scene* scene = new Scene("GAMEPLAY SCENE");

  Entity white = scene->createEntity("cat1", 0, 0);
  auto& s = white.addComponent<SpriteComponent>(
    "Sprites/Cat/Sprite-0002.png",
    0, 0,
    48,
    0,
    0, 
    getShader(ShaderType::Sepia)
  );
  s.lastUpdate = SDL_GetTicks();

  Entity black = scene->createEntity("cat2", 20, 0);
  black.addComponent<SpriteComponent>(
    "Sprites/Cat/SpriteSheet.png", 
    0, 0,
    48,
    8,
    1000,
    getShader(ShaderType::Negative),
    SDL_GetTicks()
  );

  scene->addSetupSystem<SpriteSetupSystem>(renderer);
  scene->addRenderSystem<SpriteRenderSystem>();
  // scene->addUpdateSystem<SpriteUpdateSystem>();

  return scene;
}

