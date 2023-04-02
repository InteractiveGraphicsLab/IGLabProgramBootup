#include "pch.h"
#include "Ball.h"


Ball::Ball(float radi, const EVec3f& pos, const EVec3f& velo)
{
  m_radi = radi;
  m_pos = pos;
  m_velo = velo;
}


Ball::Ball(const Ball& src)//Copy Constructer
{
  m_pos = src.m_pos;
  m_velo = src.m_velo;
  m_radi = src.m_radi;
}

void Ball::Step() 
{
  float dt = 0.33f;
  // x = x + vdt
  m_pos += m_velo * dt;

  // v = v + gdt
  m_velo += EVec3f(0, -0.98f, 0) * dt;
  m_velo *= 0.99f;
}




static void DrawSphere()
{
  const int    N = 20;
  const double M_PI = 3.141592;

  glEnable(GL_DEPTH_TEST);
  //Material 
  float   shin[1] = { 64 };
  EVec4f  spec(1, 1, 1, 0.5);
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
      double t1 = (x) / (double)N * 2.0 * M_PI;
      double t2 = (x + 1) / (double)N * 2.0 * M_PI;
      double p1 = (y) / (double)N * 1.0 * M_PI - 0.5 * M_PI;
      double p2 = (y + 1) / (double)N * 1.0 * M_PI - 0.5 * M_PI;

      glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glVertex3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
      glVertex3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));

      glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glVertex3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
      glVertex3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));

    }
  }

  glEnd();
}


void Ball::Draw()
{
  glTranslated(m_pos[0], m_pos[1], m_pos[2]);
  DrawSphere();
  glTranslated(-m_pos[0], -m_pos[1], -m_pos[2]);
}
