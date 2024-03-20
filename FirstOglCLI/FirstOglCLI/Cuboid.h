#pragma once
#include "OglForCLI.h"

class Cuboid
{
private:
	EVec3f _pos;
	float _size[3];

public:
	Cuboid(const EVec3f& pos, const float(& size)[3]);
	Cuboid(const Cuboid& src);
	void Draw();
	void DrawCuboid();
};
