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
  EVec3f vertex[] = {
    {EVec3f(-width_, -height_, -depth_)},
    {EVec3f(-width_, -height_,  depth_)},
    {EVec3f(-width_,  height_, -depth_)},
    {EVec3f(-width_,  height_,  depth_)},
    {EVec3f( width_, -height_, -depth_)},
    {EVec3f( width_, -height_,  depth_)},
    {EVec3f( width_,  height_, -depth_)},
    {EVec3f( width_,  height_,  depth_)}
  };

  int face[][3] = {
    {0, 1, 2},
    {1, 2, 3},
    {0, 1, 4},
    {1, 4, 5},
    {0, 2, 4},
    {2, 4, 6},
    {4, 5, 6},
    {5, 6, 7},
    {2, 3, 6},
    {3, 6, 7},
    {1, 3, 5},
    {3, 5, 7}
  };

  EVec3f normal[] = {
    {EVec3f(-1.0,  0.0,  0.0)},
    {EVec3f(-1.0,  0.0,  0.0)},
    {EVec3f( 0.0, -1.0,  0.0)},
    {EVec3f( 0.0, -1.0,  0.0)},
    {EVec3f( 0.0,  0.0, -1.0)},
    {EVec3f( 0.0,  0.0, -1.0)},
    {EVec3f( 1.0,  0.0,  0.0)},
    {EVec3f( 1.0,  0.0,  0.0)},
    {EVec3f( 0.0,  1.0,  0.0)},
    {EVec3f( 0.0,  1.0,  0.0)},
    {EVec3f( 0.0,  0.0,  1.0)},
    {EVec3f( 0.0,  0.0,  1.0)}
  };

  glEnable(GL_LIGHTING);
  glBegin(GL_TRIANGLES);

  for (int i = 0; i < 12; ++i) {
    glNormal3fv(normal[i].data()); //法線ベクトルの指定
    for (int j = 0; j < 3; ++j) {
      glVertex3fv(vertex[face[i][j]].data());
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
