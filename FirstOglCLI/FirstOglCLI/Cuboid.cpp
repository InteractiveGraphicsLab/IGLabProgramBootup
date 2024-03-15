#include "pch.h"
#include "Cuboid.h"
Cuboid::Cuboid(const EVec3f& pos, float width, float height, float depth)
{
	pos_    = pos;
	width_  = width;
	height_ = height;
	depth_  = depth;
}

Cuboid::Cuboid(const Cuboid& src)
{

	pos_    = src.pos_;
	width_  = src.width_;
	height_ = src.height_;
	depth_  = src.depth_;
}

void Cuboid::Draw() const
{
	glPushMatrix();
	glTranslated(pos_[0], pos_[1], pos_[2]);
	DrawCuboid();
	glPopMatrix();
}

void Cuboid::DrawCuboid() const
{
  glEnable(GL_LIGHTING);
  glBegin(GL_TRIANGLES);

  EVec3f twoPos[2];
  twoPos[0] = pos_ - EVec3f(width_, height_, depth_);
  twoPos[1] = pos_ + EVec3f(width_, height_, depth_);

  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 2; y++) {
      glVertex3f(twoPos[x][0], twoPos[y][1], twoPos[y][2]);
      glVertex3f(twoPos[x][0], twoPos[1 - y][1], twoPos[y][2]);
      glVertex3f(twoPos[x][0], twoPos[1 - y][1], twoPos[1 - y][2]);

      glVertex3f(twoPos[y][0], twoPos[x][1], twoPos[y][2]);
      glVertex3f(twoPos[1 - y][0], twoPos[x][1], twoPos[y][2]);
      glVertex3f(twoPos[1 - y][0], twoPos[x][1], twoPos[1 - y][2]);

      glVertex3f(twoPos[y][0], twoPos[y][1], twoPos[x][2]);
      glVertex3f(twoPos[1 - y][0], twoPos[y][1], twoPos[x][2]);
      glVertex3f(twoPos[1 - y][0], twoPos[1 - y][1], twoPos[x][2]);
    }
  }
  glEnd();
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
