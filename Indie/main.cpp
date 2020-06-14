#include "Character.h"
#include "event.h"
#include "menu.h"

int main(void)
{
    game_t game;
    data_t data;
    menu_t menu;
    pause_t pause;
    MyEventReceiver receiver;
    game.device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1920, 1080), 16, false, false, false, &receiver);

    if (!game.device)
        return 1;
    game.device->setWindowCaption(L"Indie Studio");
    game.driver = game.device->getVideoDriver();
    game.smgr = game.device->getSceneManager();
    game.guienv = game.device->getGUIEnvironment();
    game.load = false;

    Mesh crate_mesh("../media/Crate1.obj", &game);
    Mesh bomberman_mesh("../media/Bomberman.md3", &game);
    Mesh bomb_mesh("../media/bomb.obj", &game);
    Node ground(crate_mesh, "../media/grass.jpg", &game); 

    //Non static init
    Player bomberman1(bomberman_mesh, "../media/WhiteBombermanTextures.png", &game, 1);
    Player bomberman2(bomberman_mesh, "../media/BlackBombermanTextures.png", &game, 2);
    Character bomberman3(bomberman_mesh, "../media/PinkBombermanTextures.png", &game);
    Character bomberman4(bomberman_mesh, "../media/RedBombermanTextures.png", &game);
    bomberman1.getnode()->setPosition(core::vector3df(2, 0, 2));
    bomberman2.getnode()->setPosition(core::vector3df(30, 0, 30));
    bomberman3.getnode()->setPosition(core::vector3df(30, 0, 2));
    bomberman4.getnode()->setPosition(core::vector3df(2, 0, 30));
    //
    bomberman1.getnode()->setScale(core::vector3df(1.25, 1.25, 1.25));
    bomberman2.getnode()->setScale(core::vector3df(1.25, 1.25, 1.25));
    bomberman3.getnode()->setScale(core::vector3df(1.25, 1.25, 1.25));
    bomberman4.getnode()->setScale(core::vector3df(1.25, 1.25, 1.25));
    bomberman1.getnode()->setFrameLoop(27, 64);
    bomberman2.getnode()->setFrameLoop(27, 64);
    bomberman3.getnode()->setFrameLoop(27, 64);
    bomberman4.getnode()->setFrameLoop(27, 64);

    ground.getnode()->setScale(core::vector3df(17, 1, 17));
    ground.getnode()->setPosition(core::vector3df(16, -1, 16));


    //MAP GEN
    std::vector <Node> destructibleList = map_gen3D(map_gen(15), crate_mesh, &game);
    //

    init_menu(&game, &menu, &data);
    init_pause(&game, &pause);
    
    ICameraSceneNode *camera = game.smgr->addCameraSceneNode(0, vector3df(0, 10, -10), vector3df(16, 40, 16));//
    //game.smgr->addCameraSceneNodeFPS(0, 100.0f, 0.02f);
    game.device->getCursorControl()->setVisible(false);
    u32 then = game.device->getTimer()->getTime();
    camera->setPosition(vector3df(16, 23, 9));
    bool is_running = false;
    bool loading = true;
    bool create_map = true;

    scene::ISceneNode *SkyBox = game.smgr->addSkyBoxSceneNode(
        game.driver->getTexture("../media/irrlicht2_up.jpg"),
        game.driver->getTexture("../media/irrlicht2_dn.jpg"),
        game.driver->getTexture("../media/irrlicht2_lf.jpg"),
        game.driver->getTexture("../media/irrlicht2_rt.jpg"),
        game.driver->getTexture("../media/irrlicht2_ft.jpg"),
        game.driver->getTexture("../media/irrlicht2_bk.jpg"));

    while (game.device->run())
    {
        game.driver->beginScene(true, true, SColor(255, 100, 101, 140));

        const u32 now = game.device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        if (menu.in_game == true && menu.pause == false) {
            /*if (loading) {
                if (game.nb_player == 1 && bomberman2.getIsAlive() == true) {
                    bomberman2.getnode()->remove();
                    Character bomberman2(bomberman_mesh, "../media/BlackBombermanTextures.png", &game);
                    bomberman2.getnode()->setPosition(core::vector3df(30, 0, 30));
                    bomberman2.getnode()->setScale(core::vector3df(1.25, 1.25, 1.25));
                    bomberman2.getnode()->setFrameLoop(27, 64);
                    if (game.load == true) {
                        restore_p2(&bomberman2, &data);
                        game.load = false;
                    }
                }
                loading = false;
            }*/
            if (bomberman1.getIsAlive() && check_death(&game, &bomberman1)) {
                    bomberman1.getIsRunning() = player_movement(frameDeltaTime, receiver, &bomberman1, &game);
                    check_bonus(&bomberman1, &game);
                    place_bomb(bomb_mesh, &game, bomberman1, receiver);
            }
            if (game.nb_player == 2 && bomberman2.getIsAlive() && check_death(&game, &bomberman2)) {
                bomberman2.getIsRunning() = player_movement(frameDeltaTime, receiver, &bomberman2, &game);
                check_bonus(&bomberman2, &game);
                place_bomb(bomb_mesh, &game, bomberman2, receiver);
            }
            update_bomb(&game, frameDeltaTime, &destructibleList, crate_mesh);
            if (receiver.IsKeyDown(irr::KEY_ESCAPE)) {
                menu.pause = true;
            }

            game.smgr->drawAll();
        } else if (menu.in_game == false) {
            game.smgr->drawAll();
            if (menu.is_rotating) {
                if (game.load == true && create_map == true) {
                    load_save(&game, &data, &bomberman1, &bomberman2, &bomberman3, &bomberman4);
                    destructibleList = reloadMap(destructibleList, crate_mesh, &game);
                    create_map = false;
                }
                menu_camera_rotate(&game, &menu, frameDeltaTime, camera);
            }
            else if (main_menu(&game, &menu, frameDeltaTime, receiver, &data))
                break;
        } else {
            game.smgr->drawAll();
            if (play_pause(&game, &pause, frameDeltaTime, receiver, &menu, &bomberman1, &bomberman2, &bomberman3, &bomberman4)) {
                break;
            }
        }



        game.guienv->drawAll();

        game.driver->endScene();
    }
    game.device->drop();

    return 0;
}