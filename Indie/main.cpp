#include "Object.h"
#include "event.h"

bool move_player(const f32 frameDeltaTime, MyEventReceiver receiver, Node *bomberman)
{
    core::vector3df player_position = bomberman->getnode()->getPosition();
    const f32 MOVEMENT_SPEED = 5.f;
    bool is_running = false;

    float cot� = 1;
    float droit = 1;
    if (receiver.IsKeyDown(irr::KEY_KEY_D) || receiver.IsKeyDown(irr::KEY_KEY_Q)) {
        cot� = 0.6;
        is_running = true;
    }
    if (receiver.IsKeyDown(irr::KEY_KEY_S) || receiver.IsKeyDown(irr::KEY_KEY_Z)) {
        droit = 0.6;
        is_running = true;
    }

    if (receiver.IsKeyDown(irr::KEY_KEY_Z)) {
        player_position.Z += MOVEMENT_SPEED * frameDeltaTime * cot�;
        bomberman->getnode()->setRotation(vector3df(0, 180, 0));
    } else if (receiver.IsKeyDown(irr::KEY_KEY_S)) {
        player_position.Z -= MOVEMENT_SPEED * frameDeltaTime * cot�;
        bomberman->getnode()->setRotation(vector3df(0, 0, 0));
    }
    if (receiver.IsKeyDown(irr::KEY_KEY_Q)) {
        player_position.X -= MOVEMENT_SPEED * frameDeltaTime * droit;
        bomberman->getnode()->setRotation(vector3df(0, 90, 0));
    } else if (receiver.IsKeyDown(irr::KEY_KEY_D)) {
        player_position.X += MOVEMENT_SPEED * frameDeltaTime * droit;
        bomberman->getnode()->setRotation(vector3df(0, 270, 0));
    }
    bomberman->getnode()->setPosition(player_position);
    return (is_running);
}

bool player_movement(const f32 frameDeltaTime, MyEventReceiver receiver, Node *bomberman, bool is_running)
{
    bool now_running = move_player(frameDeltaTime, receiver, bomberman);
    if (is_running == false && now_running == true) {
        bomberman->getnode()->setFrameLoop(0, 27);
    } else if (is_running == true && now_running == false) {
        bomberman->getnode()->setFrameLoop(27, 64);
    }
    return (now_running);
}

void place_bomb(Mesh bomb_mesh, game_t game, Node bomberman, MyEventReceiver receiver)
{
    if (receiver.IsKeyDown(irr::KEY_KEY_E)) {
        Node bomb(bomb_mesh, "../media/Albedo2.png", &game);
        bomb.getnode()->setScale(vector3df(2, 2, 2));
        bomb.getnode()->setPosition(bomberman.getnode()->getPosition() + vector3df(0, 0.5, 0));
    }
}

int main(void)
{
    game_t game;
    MyEventReceiver receiver;
    game.device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1920, 1080), 16, false, false, false, &receiver);

    if (!game.device)
        return 1;
    game.device->setWindowCaption(L"Indie Studio");
    game.driver = game.device->getVideoDriver();
    game.smgr = game.device->getSceneManager();
    game.guienv = game.device->getGUIEnvironment();
    game.guienv->addStaticText(L"Hello World! Indie Studio!", rect<s32>(10, 10, 260, 22), true);

    Mesh crate_mesh("../media/Crate1.obj", &game);
    Mesh bomberman_mesh("../media/Bomberman.md3", &game);
    Mesh bomb_mesh("../media/bomb.obj", &game);
    Node ground(crate_mesh, "../media/white_marble_03_4k_baseColor.tga", &game);
    Node bomberman(bomberman_mesh, "../media/WhiteBombermanTextures.png", &game);
    bomberman.getnode()->setPosition(core::vector3df(0, 1, 0));
    ground.getnode()->setScale(core::vector3df(10, 1, 10));

    //smgr->addCameraSceneNode(0, vector3df(0, 10, 40), vector3df(0, 0, 0));//
    game.smgr->addCameraSceneNodeFPS(0, 100.0f, 0.02f);
    game.device->getCursorControl()->setVisible(false);
    u32 then = game.device->getTimer()->getTime();

    bool is_running = false;

    while (game.device->run())
    {
        game.driver->beginScene(true, true, SColor(255, 100, 101, 140));

        const u32 now = game.device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        is_running = player_movement(frameDeltaTime, receiver, &bomberman, is_running);
        place_bomb(bomb_mesh, game, bomberman, receiver);

        game.smgr->drawAll();
        game.guienv->drawAll();

        game.driver->endScene();
    }
    game.device->drop();

    return 0;
}