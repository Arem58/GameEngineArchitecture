#include <print.h>
#include "Pong.h"
#include "Components.h"
#include "ECS/Entity.h"
#include "System.h"
#include "Game/ScriptingManager.h"

Pong::Pong() : Game("Pong", SCREEN_WIDTH, SCREEN_HEIGHT)
{
    ScriptingManager::init();
    ScriptingManager::runScriptFile("Scripts/paddleMovement.lua");

    std::unique_ptr<Scene> gameplayScene = createGameplayScene();
    setScene(std::move(gameplayScene));
}

Pong::~Pong()
{
    // destructor implementation
}

std::unique_ptr<Scene> Pong::createGameplayScene()
{
    // Create a unique_ptr to hold the created scene
    std::unique_ptr<Scene> gameplayScene = std::make_unique<Scene>("Gameplay");

    Entity ball = gameplayScene->createEntity("ball", 100, 100);
    ball.addComponent<SpeedComponent>(200, 200);
    ball.addComponent<SizeComponent>(30, 30);
    ball.addComponent<ColliderComponent>(false);

    // Paddle izquierdo
    Entity paddle = gameplayScene->createEntity("paddle1", 0, (screen_height / 2) - 50);
    paddle.addComponent<SpeedComponent>(0, 0);
    paddle.addComponent<SizeComponent>(20, 100);
    paddle.addComponent<PlayerComponent>(200, 0);

    // Paddle derecho
    Entity paddle2 = gameplayScene->createEntity("paddle2", screen_width - 20, (screen_height / 2) - 50);
    paddle2.addComponent<SpeedComponent>(0, 0);
    paddle2.addComponent<SizeComponent>(20, 100);
    paddle2.addComponent<PlayerComponent>(200, 2);

    gameplayScene->addSetupSystem<HelloSystem>();
    gameplayScene->addRenderSystem<RectRenderSystem>();
    gameplayScene->addUpdateSystem<MovementUpdateSystem>(SCREEN_WIDTH, SCREEN_HEIGHT);
    gameplayScene->addEventSystem<PlayerInputEventSystem>();
    gameplayScene->addUpdateSystem<CollisionDetectionUpdateSystem>();
    gameplayScene->addUpdateSystem<BounceUpdateSystem>();
    gameplayScene->addUpdateSystem<EnemyMoveSystem>();

    return gameplayScene;
}