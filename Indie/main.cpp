#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(void)
{
    IrrlichtDevice* device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1920, 1080), 16, false, false, false, 0);
    
    if (!device)
        return 1;
    device->setWindowCaption(L"Indie Studio");
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();
    guienv->addStaticText(L"Hello World! Indie Studio!", rect<s32>(10, 10, 260, 22), true);
    IAnimatedMesh* mesh = smgr->getMesh("../media/Crate1.obj");
    if (!mesh)
    {
        device->drop();
        return 1;
    }

    IAnimatedMesh* mesh2 = smgr->getMesh("../media/Bomberman.md3");
    if (!mesh2)
    {
        device->drop();
        return 1;
    }
    
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture("../media/white_marble_03_4k_baseColor.tga"));
        node->setPosition(core::vector3df(0, 0, 0));
    }

    IAnimatedMeshSceneNode* node3 = smgr->addAnimatedMeshSceneNode(mesh);
    if (node3)
    {
        node3->setMaterialFlag(EMF_LIGHTING, false);
        node3->setMD2Animation(scene::EMAT_STAND);
        node3->setMaterialTexture(0, driver->getTexture("../media/white_marble_03_4k_baseColor.tga"));
        node3->setPosition(core::vector3df(2, 0, 0));
    }

    IAnimatedMeshSceneNode* node2 = smgr->addAnimatedMeshSceneNode(mesh2);
    if (node2)
    {
        node2->setMaterialFlag(EMF_LIGHTING, false);
        node2->setMD2Animation(scene::EMAT_RUN);
        node2->setMaterialTexture(0, driver->getTexture("../media/WhiteBombermanTextures.png"));
        node2->setPosition(core::vector3df(0, 1, 0));
        node2->setFrameLoop(0, 25);
    }

    //smgr->addCameraSceneNode(0, vector3df(0, 10, 40), vector3df(0, 0, 0));
    smgr->addCameraSceneNodeFPS(0, 100.0f, 0.02f);
    device->getCursorControl()->setVisible(false);
    while (device->run())
    {
        driver->beginScene(true, true, SColor(255, 100, 101, 140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}