#pragma once

#include "OglForCLI.h"

class Cuboid
{
private:
	EVec3f pos_;
	float height;
	float width;
	float depth;

public:
	Cuboid::Cuboid(const EVec3f& pos, float height, float width);
	Cuboid::Cuboid(const Cuboid& src);
	EVec3f GetPos() const;
	void Draw();
};

