#include "pch.h"
#include "Cuboid.h"

Cuboid::Cuboid(const EVec3f& pos, float width, float height, float depth)
{
	pos_ = pos;
	width_ = width;
	height_ = height;
	depth_ = depth;
}

Cuboid::Cuboid(const Cuboid& src)
{
	pos_ = src.pos_;
	width_ = src.width_;
	height_ = src.height_;
	depth_ = src.depth_;
}

EVec3f Cuboid::GetPos() const
{
	return pos_;
}

float Cuboid::GetWidth() const
{
	return width_;
}

float Cuboid::GetHeight() const
{
	return height_;
}

float Cuboid::GetDepth() const
{
	return depth_;
}

void Cuboid::DrawCuboid() const
{
	EVec3f ver1 = pos_ - EVec3f(width_, height_, depth_);
	EVec3f ver2 = pos_ + EVec3f(width_, height_, depth_);

	glBegin(GL_TRIANGLES);
    
    glEnd();
}