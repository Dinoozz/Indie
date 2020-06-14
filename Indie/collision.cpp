#include "Character.h"

void check_bonus(Player* bomberman, game_t* game)
{
	vector3df position = bomberman->getnode()->getPosition();
	int posx = round(position.X / 2);
	int posz = round(position.Z / 2);

	if (game->map2D[posz][posx] == 'b') {
		printf("b\n");
		bomberman->getNbBomb() += 1;
		game->map2D[posz][posx] = ' ';
	} else if (game->map2D[posz][posx] == 'p') {
		printf("p\n");
		bomberman->getPower() += 1;
		game->map2D[posz][posx] = ' ';
	} else if (game->map2D[posz][posx] == 's') {
		bomberman->setSpeed(bomberman->getSpeed() + 1);
		game->map2D[posz][posx] = ' ';
		printf("%d\n", bomberman->getSpeed());
	} else if (game->map2D[posz][posx] == 'w') {
		printf("w\n");
		bomberman->getWallpass() = true;
		game->map2D[posz][posx] = ' ';
	}
	for (int i = 0; i < game->bonus.size(); i++) {
		position = game->bonus.at(i).getnode()->getPosition();
		if (round(position.X / 2) == posx && round(position.Z / 2) == posz) {
			game->bonus.at(i).getnode()->remove();
			game->bonus.erase(game->bonus.begin() + i);
		}
	}
}

bool check_collision(Player *bomberman, int direction, game_t *game)
{
    vector3df position = bomberman->getnode()->getPosition();
    int rnd_posx = round(position.X / 2) * 2;
    int rnd_posz = round(position.Z / 2) * 2;
	f32 posx = position.X;
	f32 posz = position.Z;
	switch (direction)
	{
	case 1: // gauche
		posx -= 0.3;
		break;
	case 2: // haut
		posz += 0.3;
		break;
	case 3: // droite
		posx += 0.3;
		break;
	case 4: // bas
		posz -= 0.3;
		break;
	default:
		break;
	}
	int check_posx = round(posx / 2);
	int check_posz = round(posz / 2);
	if (check_posx != rnd_posx / 2 || check_posz != rnd_posz / 2) {
		if (game->map2D[check_posz][check_posx] == ' ' || game->map2D[check_posz][check_posx] == 'F' || game->map2D[check_posz][check_posx] == 'p' || game->map2D[check_posz][check_posx] == 'b' || game->map2D[check_posz][check_posx] == 's' || game->map2D[check_posz][check_posx] == 'w')
			return (true);
		return (false);
	}
	return (true);
}

bool check_death(game_t* game, Character* bomberman)
{
	vector3df position = bomberman->getnode()->getPosition();
	int posx = round(position.X / 2);
	int posz = round(position.Z / 2);

	if (game->map2D[posz][posx] == 'F') {
		bomberman->getnode()->remove();
		bomberman->getIsAlive() = false;
		return false;
	}
	return true;
}