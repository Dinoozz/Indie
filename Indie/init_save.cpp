#include "Character.h"

void load_save(game_t *game, data_t *data, Player *bomberman1, Player *bomberman2, Character *bomberman3, Character *bomberman4)
{
	std::vector <Character*> Temp_list;
	Temp_list.emplace_back(bomberman1);
	Temp_list.emplace_back(bomberman2);
	Temp_list.emplace_back(bomberman3);
	Temp_list.emplace_back(bomberman4);
	game->nb_player = data->nb_player;
	game->map2D = data->map2D;
	for (int i = 0; i < 4; i++) {
		Temp_list.at(i)->getSpeed() = data->List_Charact.at(i)->speed;
		Temp_list.at(i)->getPower() = data->List_Charact.at(i)->power;
		Temp_list.at(i)->getNbBomb() = data->List_Charact.at(i)->nb_bomb;
		Temp_list.at(i)->getWallpass() = data->List_Charact.at(i)->wall_pass;
		Temp_list.at(i)->getIsAlive() = data->List_Charact.at(i)->is_alive;
		if (data->List_Charact.at(i)->is_alive == false) {
			Temp_list.at(i)->getnode()->remove();
			continue;
		}
		for (int j = 0; data->map2D[j] ; j++) {
			for (int g = 0; data->map2D[j][g]; g++) {
				if (data->map2D[j][g] == char(i + '1')) {
					game->map2D[j][g] = ' ';
					Temp_list.at(i)->getnode()->setPosition(vector3df(g * 2, 0, j * 2));
				}
			}
		}
	}
}

void restore_p2(Character* bomberman2, data_t *data)
{
	std::cout << "ouais je te jure" << std::endl;
	bomberman2->getSpeed() = data->List_Charact.at(1)->speed;
	bomberman2->getPower() = data->List_Charact.at(1)->power;
	bomberman2->getNbBomb() = data->List_Charact.at(1)->nb_bomb;
	bomberman2->getWallpass() = data->List_Charact.at(1)->wall_pass;
	bomberman2->getIsAlive() = data->List_Charact.at(1)->is_alive;
	std::cout << "ouais je te jure" << std::endl;

	for (int j = 0; data->map2D[j]; j++) {
		for (int g = 0; data->map2D[j][g]; g++) {
			if (data->map2D[j][g] == '2')
				bomberman2->getnode()->setPosition(vector3df(g * 2, 0, j * 2));
			
		}
	}
	std::cout << "ouais je te jure" << std::endl;
}