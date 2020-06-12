#include "Object.h"
#include "event.h"
#include "menu.h"

int main(void)
{
    game_t game;
    menu_t menu;
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
    Node ground(crate_mesh, "../media/grass.jpg", &game);
    Node bomberman(bomberman_mesh, "../media/WhiteBombermanTextures.png", &game);
    bomberman.getnode()->setPosition(core::vector3df(0, 0, 0));
    bomberman.getnode()->setScale(core::vector3df(1.25, 1.25, 1.25));
    ground.getnode()->setScale(core::vector3df(17, 1, 17));
    ground.getnode()->setPosition(core::vector3df(16, -1, 16));


    //MAP GEN
   
    std::vector <Node> destructibleList = map_gen3D(map_gen(15), crate_mesh, &game);


    bomberman.getnode()->setFrameLoop(27, 64);

    init_menu(&game, &menu);
    ICameraSceneNode *camera = game.smgr->addCameraSceneNode(0, vector3df(0, 10, -10), vector3df(16, 40, 16));//
    //game.smgr->addCameraSceneNodeFPS(0, 100.0f, 0.02f);
    game.device->getCursorControl()->setVisible(false);
    u32 then = game.device->getTimer()->getTime();
    camera->setPosition(vector3df(16, 23, 9));
    bool is_running = false;

    while (game.device->run())
    {
        game.driver->beginScene(true, true, SColor(255, 100, 101, 140));

        const u32 now = game.device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        if (menu.in_game == true) {
            //camera->setTarget(bomberman.getnode()->getPosition());
            is_running = player_movement(frameDeltaTime, receiver, &bomberman, is_running);
            place_bomb(bomb_mesh, game, bomberman, receiver);
        } else {
            if (menu.is_rotating)
                menu_camera_rotate(&game, &menu, frameDeltaTime, camera);
            else if (main_menu(&game, &menu, frameDeltaTime, receiver))
                break;
        }

        game.smgr->drawAll();
        game.guienv->drawAll();

        game.driver->endScene();
    }
    game.device->drop();

    return 0;
}