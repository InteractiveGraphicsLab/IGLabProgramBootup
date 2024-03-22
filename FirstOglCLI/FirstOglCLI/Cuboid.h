#pragma once
#include "OglForCLI.h"

class Cuboid
{
private:
	EVec3f _pos;
	float _width;
	float _height;
	float _depth;

public:
	Cuboid(const EVec3f& pos, const float& width, const float& height, const float& depth);
	Cuboid(const Cuboid& src);
	void Draw();
	void DrawCuboid();
};
