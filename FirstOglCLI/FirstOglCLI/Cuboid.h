#pragma once

#include "OglForCLI.h"

class Cuboid
{
private:
	EVec3f pos_;
	float width_;
	float height_;
	float depth_;

public:
	Cuboid::Cuboid(const EVec3f& pos, float width, float height, float depth);
	Cuboid::Cuboid(const Cuboid& src);
	EVec3f GetPos() const;
	float GetWidth() const;
	float GetHeight() const;
	float GetDepth() const;
	void DrawCuboid() const;
};

