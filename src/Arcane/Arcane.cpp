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

  // Entity normal = scene->createEntity("cat1", 0, 0);
  // auto& s = normal.addComponent<SpriteComponent>(
  //   "Sprites/Cat/Sprite-0002.png",
  //   0, 0,
  //   48,
  //   0,
  //   0
  // );

  Entity wolf = scene->createEntity("wolf", 15, 30);
  auto &s = wolf.addComponent<SpriteComponent>(
      "Sprites/Cat/lobo_spritesheet.png",
      0, 0,
      48,
      8,
      1000,
      getShader(ShaderType::Negative),
      SDL_GetTicks());
  // s2.lastUpdate = SDL_GetTicks();

  scene->player->addComponent<SpriteComponent>(
      "Sprites/Eleina/SPRITESHEET_RENATO_FINAL.png",
      0, 0,
      48,
      8,
      1000,
      getShader(ShaderType::Negative), 
      SDL_GetTicks());

  scene->addSetupSystem<TilemapSetupSystem>(renderer);
  scene->addRenderSystem<TilemapRenderSystem>();

  scene->addEventSystem<PlayerInputEventSystem>();
  scene->addUpdateSystem<PlayerSpriteUpdateSystem>();
  scene->addUpdateSystem<MovementUpdateSystem>();

  scene->addSetupSystem<SpriteSetupSystem>(renderer);
  scene->addRenderSystem<SpriteRenderSystem>();
  scene->addUpdateSystem<SpriteUpdateSystem>();

  return scene;
}
