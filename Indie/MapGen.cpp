#include "Object.h"

char **map_gen(int size)
{
	char **map = (char **)malloc(sizeof(char *) * (size + 3));

	int coef = 72;
	for (int j = 0; j < size + 2; j++)
		map[j] = (char *)malloc(sizeof(char) * (size + 4));
	map[size + 2] = NULL;
	std::srand(time(NULL));
	for (int j = 0; j < size + 2; j++) {
		for (int i = 0; i < size + 3; i++) {
			int rand = std::rand() % 100;
			if (j == 1 || j == 2 || j == 3 || i == 1 || i == 2 || i == 3 || j == size || j == size - 1 || j == size - 2 || i == size || i == size - 1 || i == size - 2)
				coef = 100;
			else
				coef = 100;
			if (i == 0 || i == size + 1 || (j == 0 && i != size + 2) || (j == size + 1 && i != size +2))
				map[j][i] = '#';
			else if (i == size + 2)
				map[j][i] = '\n';
			else if (rand >= coef)
				map[j][i] = '#';
			else
				map[j][i] = '*';
		}
		map[j][size + 3] = '\0';
	}
	
	map[1][1] = ' ';
	map[1][2] = ' ';
	//map[1][3] = '*';
	map[1][size] = ' ';
	map[1][size - 1] = ' ';
	//map[1][size - 2] = '*';
	map[2][size] = ' ';
	//map[3][size] = '*';
	map[2][1] = ' ';
	//map[3][1] = '*';
	map[size][1] = ' ';
	map[size][2] = ' ';
	map[size][size] = ' ';
	map[size][size - 1] = ' ';
	map[size - 1][size] = ' ';
	map[size - 1][1] = ' ';
	for (int i = 0; map[i]; i++) {
		for (int j = 0; map[i][j] != '\n'; j++) {
			int walls = 0;
			int rand = std::rand() % 100;
			if (i > 0 && j > 0 && map[i][j] == '*' && j < size + 1 && i < size + 1) {
				if (map[i][j - 1] == '*')
					walls++;
				if (map[i][j + 1] == '*')
					walls++;
				if (map[i + 1][j] == '*')
					walls++;
				if (map[i - 1][j] == '*')
					walls++;
				if (walls >= 4 && rand > 60)
					map[i][j] = '#';
			}
		}
	}
	for (int i = 0; map[i]; i++) {
		for (int j = 0; map[i][j] != '\n'; j++) {
			if (i > 0 && j > 0 && j < size + 1 && i < size + 1) {
				if (map[i][j - 1] == '#' && map[i][j + 1] == '#' && map[i - 1][j] == '#' && map[i + 1][j] == '#')
					map[i][j] = '#';
			}
		}
	}
	return map;
}
