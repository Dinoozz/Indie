#include "Object.h"
#include "event.h"

bool move_player(const f32 frameDeltaTime, MyEventReceiver receiver, Node* bomberman)
{
    core::vector3df player_position = bomberman->getnode()->getPosition();
    const f32 MOVEMENT_SPEED = 5.f;
    bool is_running = false;

    float coté = 1;
    float droit = 1;
    if (receiver.IsKeyDown(irr::KEY_KEY_D) || receiver.IsKeyDown(irr::KEY_KEY_Q)) {
        coté = 0.6;
        is_running = true;
    }
    if (receiver.IsKeyDown(irr::KEY_KEY_S) || receiver.IsKeyDown(irr::KEY_KEY_Z)) {
        droit = 0.6;
        is_running = true;
    }

    if (receiver.IsKeyDown(irr::KEY_KEY_Z)) {
        player_position.Z += MOVEMENT_SPEED * frameDeltaTime * coté;
        bomberman->getnode()->setRotation(vector3df(0, 180, 0));
    }
    else if (receiver.IsKeyDown(irr::KEY_KEY_S)) {
        player_position.Z -= MOVEMENT_SPEED * frameDeltaTime * coté;
        bomberman->getnode()->setRotation(vector3df(0, 0, 0));
    }
    if (receiver.IsKeyDown(irr::KEY_KEY_Q)) {
        player_position.X -= MOVEMENT_SPEED * frameDeltaTime * droit;
        bomberman->getnode()->setRotation(vector3df(0, 90, 0));
    }
    else if (receiver.IsKeyDown(irr::KEY_KEY_D)) {
        player_position.X += MOVEMENT_SPEED * frameDeltaTime * droit;
        bomberman->getnode()->setRotation(vector3df(0, 270, 0));
    }
    bomberman->getnode()->setPosition(player_position);
    return (is_running);
}

bool player_movement(const f32 frameDeltaTime, MyEventReceiver receiver, Node* bomberman, bool is_running)
{
    bool now_running = move_player(frameDeltaTime, receiver, bomberman);
    if (is_running == false && now_running == true) {
        bomberman->getnode()->setFrameLoop(0, 27);
    }
    else if (is_running == true && now_running == false) {
        bomberman->getnode()->setFrameLoop(27, 64);
    }
    return (now_running);
}