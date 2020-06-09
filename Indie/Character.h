#pragma once
#include "Object.h"
class Character : public Object
{
public:
	Character(IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, int speed, int pui, int NbBombe, bool WallPass);
protected:
private:
	int speed;
	int pui;
	int NbBombe;
	bool WallPass;
};

