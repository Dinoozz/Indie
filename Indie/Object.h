#include "Game.h"

class Mesh
{
public:
	Mesh(const char *mesh1, game_t *game);
	virtual ~Mesh();
	IAnimatedMesh *getmesh();

protected:
private:
	IAnimatedMesh* mesh;
};

class Node
{
public:
	Node(Mesh mesh1, const char* node1, game_t* game);
	virtual ~Node();
	IAnimatedMeshSceneNode* getnode();

protected:
private:
	IAnimatedMeshSceneNode* node;
};