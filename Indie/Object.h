#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Object
{
public:
	Object(IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node);
	virtual ~Object();

protected:
private:
	IAnimatedMesh* mesh;
	IAnimatedMeshSceneNode* node;
};

