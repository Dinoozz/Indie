#include "Character.h"

std::vector <std::string> open_save_data_base(game_t* game, data_t *data)
{
	std::vector <std::string> ListSave;
	std::string str;

	std::ifstream DataBase_flux("../save/DataBase.txt");
	if (!DataBase_flux)
		exit(84);
	while (std::getline(DataBase_flux, str))
		ListSave.emplace_back(str);
	return ListSave;
}

void load_save_in_data(game_t* game, data_t* data, std::string Filename)
{
	std::string str;
	std::vector <std::string> list;
	std::vector <std::string> temp_list;

	int i = 0;
	
	std::ifstream Content(std::string("../save/") + Filename.c_str());
	data->map2D = (char**)malloc(sizeof(char*) * (18));
	data->map2D[17] = NULL;
	while (std::getline(Content, str)) {
		if (i < 17) {
			str += std::string("\n");
			data->map2D[i] = _strdup(str.c_str());
		}
		else
			list.emplace_back(str);
		i++;
	}
	
	data->nb_player = std::atoi(list.at(0).c_str());
	list.at(0).erase();
	std::string tmp;
	for (i = 1; i < list.size(); i++) {
		character_t* new_character = (character_t*)malloc(sizeof(character_t));
		for (int j = 0; j < 5; j++) {
			tmp = list.at(i).substr(0, list.at(i).find(' '));
			list.at(i) = list.at(i).substr(list.at(i).find(' ') + 1, list.at(i).length());
			switch (j) {
			case (0):
				new_character->speed = atoi(tmp.c_str());
				break; 
			case (1):
				new_character->power = atoi(tmp.c_str());
				break;
			case (2):
				new_character->nb_bomb = atoi(tmp.c_str());
				break;
			case (3):
				new_character->wall_pass = atoi(tmp.c_str());
				break;
			case (4):
				new_character->is_alive = (atoi(tmp.c_str()) == 1) ? true : false;
				break;
			default:
				break;
			}
		}
		data->List_Charact.emplace_back(new_character);
	}
}

