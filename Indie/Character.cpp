#include "Character.h"

Character::Character(Mesh mesh1, const char* node1, game_t* game) : Node(mesh1, node1, game)
{
	power = 1;
	speed = 0;
	nb_bombe = 1;
	wallpass = false;
	is_alive = true;
}

Character::Character(Mesh mesh1, const char* node1, game_t* game, int the_power, int the_speed, int the_nb_bomb, bool the_wallpass, bool the_is_alive) : Node(mesh1, node1, game)
{
	power = the_power;
	speed = the_speed;
	nb_bombe = the_nb_bomb;
	wallpass = the_wallpass;
	is_alive = the_is_alive;
}

int& Character::getPower()
{
	return power;
}

int& Character::getSpeed()
{
	return speed;
}

void Character::setSpeed(int new_speed)
{
	speed = new_speed;
}

int& Character::getNbBomb()
{
	return nb_bombe;
}

bool& Character::getWallpass()
{
	return wallpass;
}

bool& Character::getIsAlive()
{
	return is_alive;
}

Player::Player(Mesh mesh1, const char* node1, game_t* game, int player) : Character(mesh1, node1, game)
{
	if (player == 1) {
		key_bomb = KEY_KEY_E;
		key_up = KEY_KEY_Z;
		key_down = KEY_KEY_S;
		key_left = KEY_KEY_Q;
		key_right = KEY_KEY_D;
	} else {
		key_bomb = KEY_NUMPAD0;
		key_up = KEY_UP;
		key_down = KEY_DOWN;
		key_left = KEY_LEFT;
		key_right = KEY_RIGHT;
	}
	is_running = false;
}

Player::Player(Mesh mesh1, const char* node1, game_t* game, int the_power, int the_speed, int the_nb_bomb, bool the_wallpass, int player, bool is_alive) : Character(mesh1, node1, game, the_power, the_speed, the_nb_bomb, the_wallpass, is_alive)
{
	if (player == 1) {
		key_bomb = KEY_KEY_E;
		key_up = KEY_KEY_Z;
		key_down = KEY_KEY_S;
		key_left = KEY_KEY_Q;
		key_right = KEY_KEY_D;
	}
	else {
		key_bomb = KEY_NUMPAD0;
		key_up = KEY_UP;
		key_down = KEY_DOWN;
		key_left = KEY_LEFT;
		key_right = KEY_RIGHT;
	}
	is_running = false;
}

irr::EKEY_CODE Player::getKeyUp() const
{
	return key_up;
}

irr::EKEY_CODE Player::getKeyDown() const
{
	return key_down;
}

irr::EKEY_CODE Player::getKeyRight() const
{
	return key_right;
}

irr::EKEY_CODE Player::getKeyLeft() const
{
	return key_left;
}

irr::EKEY_CODE Player::getKeyBomb() const
{
	return key_bomb;
}

bool& Player::getIsRunning()
{
	return is_running;
}
