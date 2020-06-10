#include "Object.h"

Mesh::Mesh(const char *mesh1, game_t *game)
{
	mesh = game->smgr->getMesh(mesh1);
    if (!mesh)
    {
        game->device->drop();
        exit (1);
    }
}

IAnimatedMesh* Mesh::getmesh()
{
    return(mesh);
}

Node::Node(Mesh mesh1, const char* node1, game_t* game)
{
    node = game->smgr->addAnimatedMeshSceneNode(mesh1.getmesh());
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, game->driver->getTexture(node1));
        node->setPosition(core::vector3df(0, 0, 0));
    }
}

IAnimatedMeshSceneNode* Node::getnode()
{
    return(node);
}

Mesh::~Mesh()

{
}

Node::~Node()
{
}
