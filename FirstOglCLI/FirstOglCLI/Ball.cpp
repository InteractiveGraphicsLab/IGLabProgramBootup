#include "pch.h"
#include "Ball.h"

Ball::Ball(const EVec3f& pos, const EVec3f& velo, const EVec3f& rot, float radi)
{
	pos_ = pos;
	velo_ = velo;
	rot_ = rot;
	radi_ = radi;
}

Ball::Ball(const EVec3f& pos, const EVec3f& velo, float radi)
{
	pos_ = pos;
	velo_ = velo;
	radi_ = radi;
}

Ball::Ball(const Ball& src)
{
	pos_  = src.pos_;
	velo_ = src.velo_;
	rot_  = src.rot_;
	radi_ = src.radi_;
}

void Ball::Step()
{
	const float dt = 0.33f;
	const EVec3f g = EVec3f(0, 9.8f, 0);

	velo_ -= 0.02f * g * dt;
	pos_ += velo_ * dt;
}

void Ball::Draw() const
{
	glPushMatrix();
	glTranslated(pos_[0], pos_[1], pos_[2]);
	/*glMultMatrix();*/
	DrawSphere();
	glPopMatrix();
}

void Ball::DrawSphere() const
{
  const int    N = 20;
  const float M_PI = 3.141592f;

  glEnable(GL_DEPTH_TEST);
  //Material
  float   shin[1] = { 64 };
  EVec4f  spec(1, 1, 1, 0.5f);
  EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);
  EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);

  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);


  glBegin(GL_TRIANGLES);
  for (int y = 0; y < N; ++y)
  {
    for (int x = 0; x < N; ++x)
    {
      float t1 = (x) / (float)N * 2.0f * M_PI;
      float t2 = (x + 1) / (float)N * 2.0f * M_PI;
      float p1 = (y) / (float)N * 1.0f * M_PI - 0.5f * M_PI;
      float p2 = (y + 1) / (float)N * 1.0f * M_PI - 0.5f * M_PI;

      glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glVertex3d(radi_ * cos(t1) * cos(p1), radi_ * sin(p1), radi_ * sin(t1) * cos(p1));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(radi_ * cos(t2) * cos(p2), radi_ * sin(p2), radi_ * sin(t2) * cos(p2));
      glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
      glVertex3d(radi_ * cos(t2) * cos(p1), radi_ * sin(p1), radi_ * sin(t2) * cos(p1));

      glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glVertex3d(radi_ * cos(t1) * cos(p1), radi_ * sin(p1), radi_ * sin(t1) * cos(p1));
      glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
      glVertex3d(radi_ * cos(t1) * cos(p2), radi_ * sin(p2), radi_ * sin(t1) * cos(p2));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(radi_ * cos(t2) * cos(p2), radi_ * sin(p2), radi_ * sin(t2) * cos(p2));

    }
  }
  glEnd();
}

void Ball::SetPos(EVec3f& pos)
{
  pos_ = pos;
}

void Ball::SetVelo(EVec3f& velo)
{
  velo_ = velo;
}

void Ball::SetRot(EVec3f& rot)
{
  rot_ = rot;
}

void Ball::SetRadi(float radi)
{
  radi_ = radi;
}

EVec3f Ball::GetPos() const
{
  return pos_;
}

EVec3f Ball::GetVelo() const
{
  return velo_;
}

EVec3f Ball::GetRot() const
{
  return rot_;
}

float  Ball::GetRadi() const
{
  return radi_;
}