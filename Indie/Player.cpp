#include "Character.h"
#include "event.h"

bool move_player(const f32 frameDeltaTime, MyEventReceiver receiver, Player *bomberman, game_t *game)
{
    core::vector3df player_position = bomberman->getnode()->getPosition();
    const f32 MOVEMENT_SPEED = 5.f;
    bool is_running = false;

    float coté = 1;
    float droit = 1;
    if (receiver.IsKeyDown(bomberman->getKeyLeft()) || receiver.IsKeyDown(bomberman->getKeyRight())) {
        coté = 0.6;
        is_running = true;
    }
    if (receiver.IsKeyDown(bomberman->getKeyDown()) || receiver.IsKeyDown(bomberman->getKeyUp())) {
        droit = 0.6;
        is_running = true;
    }

    if (receiver.IsKeyDown(bomberman->getKeyUp()) && check_collision(bomberman, 2, game)) {
        player_position.Z += MOVEMENT_SPEED * frameDeltaTime * coté + bomberman->getSpeed() * 1.f * frameDeltaTime;
        bomberman->getnode()->setRotation(vector3df(0, 180, 0));
    }
    else if (receiver.IsKeyDown(bomberman->getKeyDown()) && check_collision(bomberman, 4, game)) {
        player_position.Z -= MOVEMENT_SPEED * frameDeltaTime * coté + bomberman->getSpeed() * 1.f * frameDeltaTime;
        bomberman->getnode()->setRotation(vector3df(0, 0, 0));
    }
    if (receiver.IsKeyDown(bomberman->getKeyLeft()) && check_collision(bomberman, 1, game)) {
        player_position.X -= MOVEMENT_SPEED * frameDeltaTime * droit + bomberman->getSpeed() * 1.f * frameDeltaTime;
        bomberman->getnode()->setRotation(vector3df(0, 90, 0));
    }
    else if (receiver.IsKeyDown(bomberman->getKeyRight()) && check_collision(bomberman, 3, game)) {
        player_position.X += MOVEMENT_SPEED * frameDeltaTime * droit + bomberman->getSpeed() * 1.f * frameDeltaTime;
        bomberman->getnode()->setRotation(vector3df(0, 270, 0));
    }
    bomberman->getnode()->setPosition(player_position);
    return (is_running);
}

bool player_movement(const f32 frameDeltaTime, MyEventReceiver receiver, Player *bomberman, game_t *game)
{
    bool now_running = move_player(frameDeltaTime, receiver, bomberman, game);
    if (bomberman->getIsRunning() == false && now_running == true) {
        bomberman->getnode()->setFrameLoop(0, 27);
    }
    else if (bomberman->getIsRunning() == true && now_running == false) {
        bomberman->getnode()->setFrameLoop(27, 64);
    }
    return (now_running);
}