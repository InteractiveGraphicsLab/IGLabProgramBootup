#pragma once

#include "OglForCLI.h"

class Cuboid
{
private:
	EVec3f pos_;
	float width_, height_, depth_;

public:
	Cuboid(const EVec3f& pos, float width, float height, float depth);
	Cuboid(const Cuboid& src);

	void Draw() const;
	void DrawCuboid() const;

	EVec3f GetPos() const;
	float GetWidth() const;
	float GetHeight() const;
	float GetDepth() const;
};