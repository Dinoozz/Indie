#include "Character.h"

std::vector <std::string> open_save_data_base(game_t* game, data_t *data)
{
	std::vector <std::string> ListSave;
	std::string str;

	std::ifstream monFlux(str.c_str());
	//Déclaration d'un flux permettant d'écrire dans un fichier.

	std::ifstream DataBase_flux("../save/DataBase.txt");
	if (!DataBase_flux)
		exit(84);
	while (getline(DataBase_flux, str))
		ListSave.emplace_back(str);
	return ListSave;
}

