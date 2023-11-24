#include <print.h>
#include "System.h"
#include "Components.h"

HelloSystem::HelloSystem()
{
    print("Hello System Constructor");
}

HelloSystem::HelloSystem(const HelloSystem &other)
{
    print("Hello System Copy Constructor");
}

HelloSystem::~HelloSystem()
{
    print("Hello System Destructor");
}

void HelloSystem::run()
{
    print("Hello System!");
}

void RectRenderSystem::run(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

    const auto view = scene->r.view<TransformComponent, SizeComponent>();
    for (const entt::entity e : view)
    {
        const TransformComponent &t = view.get<TransformComponent>(e);
        const SizeComponent &c = view.get<SizeComponent>(e);
        const int x = t.position.x;
        const int y = t.position.y;
        const int w = c.w;
        const int h = c.h;

        SDL_Rect rect = {x, y, w, h};
        SDL_RenderFillRect(renderer, &rect);
    }
}

MovementUpdateSystem::MovementUpdateSystem(int screen_width, int screen_height)
    : screen_width(screen_width), screen_height(screen_height) {}

void MovementUpdateSystem::run(double dT)
{
    const auto view = scene->r.view<NameComponent, TransformComponent, SpeedComponent>();
    for (const entt::entity e : view)
    {
        TransformComponent &t = view.get<TransformComponent>(e);
        SpeedComponent &m = view.get<SpeedComponent>(e);
        NameComponent &n = view.get<NameComponent>(e);

        if (m.x == 0 && m.y == 0)
        {
            continue;
        }

        if (n.name == "ball")
        {

            if (t.position.x <= 0)
            {
                print("Jugador 2 gana!!!");
                exit(0);
            }
            if (t.position.x >= screen_width - 20)
            {
                print("Jugador 1 gana!!!");
                exit(0);
            }
            if (t.position.y <= 0)
            {
                m.y *= -1;
                
                m.x *= 1.1f;
                m.y *= 1.1f;
            }
            if (t.position.y > screen_height - 20)
            {
                m.y *= -1;

                m.x *= 1.1f;
                m.y *= 1.1f;
            }
        }

        t.position.x += m.x * dT;
        t.position.y += m.y * dT;
    }
}

void PlayerInputEventSystem::run(SDL_Event event)
{
    scene->r.view<PlayerComponent, SpeedComponent>().each(
        [&](const auto &entity, PlayerComponent &player, SpeedComponent &speed)
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (player.playerNumber == 0)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        speed.y = -player.moveSpeed;
                        break;

                    case SDLK_s:
                        speed.y = player.moveSpeed;
                        break;
                    }
                }
                else if (player.playerNumber == 1)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_i:
                        speed.y = -player.moveSpeed;
                        break;

                    case SDLK_k:
                        speed.y = player.moveSpeed;
                        break;
                    }
                }
            }
            if (event.type == SDL_KEYUP)
            {
                speed.y = 0;
            }
        });
}

void CollisionDetectionUpdateSystem::run(double dT)
{
    const auto view = scene->r.view<TransformComponent, SizeComponent, ColliderComponent>();
    const auto view2 = scene->r.view<TransformComponent, SizeComponent>();

    view.each([&](auto e1, TransformComponent &t1, SizeComponent &s1, ColliderComponent &c1)
              {
        // Create a bounding box for the first entity
        SDL_Rect box1 = { t1.position.x, t1.position.y, s1.w, s1.h };

        // Check against all other entities
        view2.each([&](auto e2, TransformComponent& t2, SizeComponent& s2) {
            if (e1 == e2) return;  // Skip self

            // Create a bounding box for the second entity
            SDL_Rect box2 = { t2.position.x, t2.position.y, s2.w, s2.h };

            // Check for intersection
            if (SDL_HasIntersection(&box1, &box2)) {
              c1.triggered = true;
            }
        }); });
}

void BounceUpdateSystem::run(double dT)
{
    const auto view = scene->r.view<ColliderComponent, SpeedComponent>();

    view.each([&](auto e, ColliderComponent &c, SpeedComponent &s)
              {
        if(c.triggered){
            c.triggered = false;
            s.x *= -1.1;
        } });
}