#include "Object.h"
#include "event.h"

std::vector <Node> map_gen(const std::string map2D, Mesh crate_mesh, game_t *game)
{
    int x = -15;
    int y = 2;
    int z = -15;
    int i = 0;
    std::vector <Node> destructibleList;

    while (map2D[i]) {
        if (map2D[i] == '#') {
            Node tmp(crate_mesh, "../media/white_marble_03_4k_baseColor.tga", game);
            tmp.getnode()->setPosition(vector3df(x, y, z));
            x+=2;
        }
        else if (map2D[i] == '*') {
            Node tmp(crate_mesh, "../media/crate_1.jpg", game);
            tmp.getnode()->setPosition(vector3df(x, y, z));
            destructibleList.emplace_back(tmp);
            x+=2;
        }
        else if (map2D[i] == ' ') {
            x+=2;
        }
        else if (map2D[i] == '\n') {
            z+=2;
            x = -15;
        }
        i++;
    }
    return destructibleList;
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
    //Object mesh2("../media/Bomberman.md3", "../media/WhiteBombermanTextures.png", game);

    Mesh crate_mesh("../media/Crate1.obj", &game);
    Mesh bomberman_mesh("../media/Bomberman.md3", &game);
    Node ground(crate_mesh, "../media/white_marble_03_4k_baseColor.tga", &game);
    Node bomberman(bomberman_mesh, "../media/WhiteBombermanTextures.png", &game);
    bomberman.getnode()->setPosition(core::vector3df(0, 1, 0));
    ground.getnode()->setScale(core::vector3df(15, 1, 15));

    //MAP GEN
   
    std::vector <Node> destructibleList = map_gen("###############\n#  *********  #\n# #*#*#*#*#*# #\n#*************#\n#*#*#*#*#*#*#*#\n#*************#\n#*#*#*#*#*#*#*#\n#*************#\n#*#*#*#*#*#*#*#\n#*************#\n# #*#*#*#*#*# #\n#  *********  #\n###############", crate_mesh, &game);


    //smgr->addCameraSceneNode(0, vector3df(0, 10, 40), vector3df(0, 0, 0));//
    game.smgr->addCameraSceneNodeFPS(0, 100.0f, 0.02f);
    game.device->getCursorControl()->setVisible(false);
    const f32 MOVEMENT_SPEED = 5.f;
    u32 then = game.device->getTimer()->getTime();
    while (game.device->run())
    {
        game.driver->beginScene(true, true, SColor(255, 100, 101, 140));

        core::vector3df player_position = bomberman.getnode()->getPosition();
        const u32 now = game.device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        float coté = 1;
        if (receiver.IsKeyDown(irr::KEY_KEY_D) || receiver.IsKeyDown(irr::KEY_KEY_Q))
            coté = 0.6;

        float droit = 1;
        if (receiver.IsKeyDown(irr::KEY_KEY_S) || receiver.IsKeyDown(irr::KEY_KEY_Z))
            droit = 0.6;

        if (receiver.IsKeyDown(irr::KEY_KEY_S)) {
            player_position.Z += MOVEMENT_SPEED * frameDeltaTime * coté;
        } else if (receiver.IsKeyDown(irr::KEY_KEY_Z))
            player_position.Z -= MOVEMENT_SPEED * frameDeltaTime * coté;

        if (receiver.IsKeyDown(irr::KEY_KEY_D))
            player_position.X -= MOVEMENT_SPEED * frameDeltaTime * droit;
        else if (receiver.IsKeyDown(irr::KEY_KEY_Q))
            player_position.X += MOVEMENT_SPEED * frameDeltaTime * droit;
        bomberman.getnode()->setPosition(player_position);

        game.smgr->drawAll();
        game.guienv->drawAll();

        game.driver->endScene();
    }
    game.device->drop();

    return 0;
}