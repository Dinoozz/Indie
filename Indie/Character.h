#pragma once
#include "Object.h"

class Character : public Node
{
	public:
		Character(Mesh mesh1, const char* node1, game_t* game);
		Character(Mesh mesh1, const char* node1, game_t* game, int the_power, int the_speed, int the_nb_bomb, bool the_wallpass, bool the_is_alive);
		int &getPower();
		int& getSpeed();
		void setSpeed(int new_speed);
		int& getNbBomb();
		bool& getWallpass();
		bool& getIsAlive();
	protected:
	private:
		int power;
		int speed;
		int nb_bombe;
		bool wallpass;
		bool is_alive;
};

class Player : public Character
{
	public:
		Player(Mesh mesh1, const char* node1, game_t* game, int player);
		Player(Mesh mesh1, const char* node1, game_t* game, int the_power, int the_speed, int the_nb_bomb, bool the_wallpass, int player, bool is_alive);
		irr::EKEY_CODE getKeyUp() const;
		irr::EKEY_CODE getKeyDown() const;
		irr::EKEY_CODE getKeyRight() const;
		irr::EKEY_CODE getKeyLeft() const;
		irr::EKEY_CODE getKeyBomb() const;
		bool& getIsRunning();
protected:
	private:
		irr::EKEY_CODE key_up;
		irr::EKEY_CODE key_down;
		irr::EKEY_CODE key_left;
		irr::EKEY_CODE key_right;
		irr::EKEY_CODE key_bomb;
		bool is_running;
};

class IA : public Character
{
	public:
	protected:
	private:
};