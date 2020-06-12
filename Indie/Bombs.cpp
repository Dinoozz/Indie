#include "Object.h"

void place_bomb(Mesh bomb_mesh, game_t game, Node bomberman, MyEventReceiver receiver)
{
    vector3df position = bomberman.getnode()->getPosition();
    int posx = round(position.X / 2) * 2;
    int posz = round(position.Z / 2) * 2;
    if (receiver.IsKeyDown(irr::KEY_KEY_E) && (posx % 2) == 0 && (posz % 2) == 0) {
        Node bomb(bomb_mesh, "../media/Albedo2.png", &game);
        bomb.getnode()->setScale(vector3df(4, 4, 4));
        bomb.getnode()->setPosition(vector3df(posx, position.Y + 0.5, posz));
    }
}