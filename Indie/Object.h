#pragma once

#include "Game.h"

class Player;
class Character;

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

class Bomb : public Node
{
public:
	Bomb(Mesh mesh1, const char* node1, game_t* game, int the_power) : Node(mesh1, node1, game)
	{
		timer = 0;
		power = the_power;
	};
	f32& getTime();
	int getPower() const;
protected:
private:
	int power;
	f32 timer;
};

std::vector <Node> map_gen3D(char** map2D, Mesh crate_mesh, game_t* game);
bool player_movement(const f32 frameDeltaTime, MyEventReceiver receiver, Player* bomberman, game_t *game);
std::vector <Node> reloadMap(std::vector <Node> blocks, Mesh crate_mesh, game_t* game);
void place_bomb(Mesh bomb_mesh, game_t* game, Player bomberman, MyEventReceiver receiver);
bool check_collision(Player *bomberman, int direction, game_t *game);
void update_bomb(game_t* game, f32 frameDeltaTime, std::vector <Node>* blocks, Mesh crate_mesh);
bool check_death(game_t* game, Character *bomberman);
void check_bonus(Player* bomberman, game_t* game);
void load_save(game_t* game, data_t* data, Player* bomberman1, Player* bomberman2, Character* bomberman3, Character* bomberman4);
void load_save_in_data(game_t* game, data_t* data, std::string Filename);
void restore_p2(Character* bomberman2, data_t* data);
void create_save(game_t* game, Character* bomberman1, Character* bomberman2, Character* bomberman3, Character* bomberman4);

