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


std::vector <Node> map_gen3D(char** map2D, Mesh crate_mesh, game_t* game);
bool move_player(const f32 frameDeltaTime, MyEventReceiver receiver, Node* bomberman);
bool player_movement(const f32 frameDeltaTime, MyEventReceiver receiver, Node* bomberman, bool is_running);
std::vector <Node> reloadMap(std::vector <Node> blocks, Mesh crate_mesh, game_t* game);
void place_bomb(Mesh bomb_mesh, game_t game, Node bomberman, MyEventReceiver receiver);