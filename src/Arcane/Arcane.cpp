#include <print.h>
#include "Arcane.h"
#include "System.h"
#include "Components.h"

#include "ECS/Entity.h"

Arcane::Arcane() : Game("Arcane", SCREEN_WIDTH, SCREEN_HEIGHT)
{
  Scene *gameplayScene = createGameplayScene();
  setScene(gameplayScene);
}

Arcane::~Arcane()
{
  // destructor implementation
}

Scene *Arcane::createGameplayScene()
{
  Scene *scene = new Scene("GAMEPLAY SCENE");

  Entity white = scene->createEntity("cat1", 0, 0);
  auto &s = white.addComponent<SpriteComponent>(
      "Sprites/Cat/SpriteSheet.png",
      0, 0,
      48,
      8,
      1000);
  s.lastUpdate = SDL_GetTicks();

  Entity black = scene->createEntity("cat2", 20, 0);
  black.addComponent<SpriteComponent>(
      "Sprites/Cat/SpriteSheet.png",
      0, 0,
      48,
      8,
      1000,
      PixelShader{
          [](Uint32 color) -> Uint32
          { return (color == 0xF3F2C0FF) ? 0xD2B48CFF : color; },
          "red"},
      SDL_GetTicks());

  scene->addSetupSystem<TilemapSetupSystem>(renderer);
  scene->addRenderSystem<TilemapRenderSystem>();

  scene->addSetupSystem<SpriteSetupSystem>(renderer);
  scene->addRenderSystem<SpriteRenderSystem>();
  scene->addUpdateSystem<SpriteUpdateSystem>();

  return scene;
}
