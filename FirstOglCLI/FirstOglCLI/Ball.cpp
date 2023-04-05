#include "pch.h"
#include "Ball.h"
#include <math.h>


Ball::Ball(float radi, EVec3f& pos, EVec3f& velo)
{
  m_radi = radi;
  m_pos = pos;
  m_velo = velo;
  m_is_skip = false;
}

Ball::Ball(float radi, EVec3f& pos)
{
  m_pos = pos;
  m_radi = radi;
  m_velo = EVec3f(0.0f, 0.0f, 0.0f);
  m_is_skip = false;
}

Ball::Ball(const Ball& src)
{
  m_radi = src.m_radi;
  m_pos = src.m_pos;
  m_velo = src.m_velo;
  m_is_skip = src.m_is_skip;
}

void Ball::Step()
{
  if (!m_is_skip)
  {
    const float dt = 0.33f;
    //const float max_velo = 2 * m_radi / dt;
    const EVec3f acc = EVec3f(0, -0.2f, 0);

    m_velo[1] *= 0.99f;
    if (sqrt(m_velo[0] * m_velo[0] + m_velo[2] * m_velo[2]) < 0.001f) // ’âŽ~ðŒ
    {
    }
    else
    {
      m_velo[0] *= 0.99f;
      m_velo[2] *= 0.99f;
    }

    //if (sqrt(m_velo[0] * m_velo[0] + m_velo[2] * m_velo[2]) > max_velo) // §ŒÀðŒ(‹…‚Ì”¼Œa‚ª“™‚µ‚¢ê‡)
    //{
    //  m_velo[0] *= max_velo / sqrt(m_velo[0] * m_velo[0] + m_velo[2] * m_velo[2]);
    //  m_velo[2] *= max_velo / sqrt(m_velo[0] * m_velo[0] + m_velo[2] * m_velo[2]);
    //}

    m_velo[0] += acc[0] * dt;
    float bottom_y = BilliardTable::GetInst()->GetPos()[1] - BilliardTable::GetInst()->GetHeight();
    if (m_pos[1] != bottom_y + m_radi) m_velo[1] += acc[1] * dt;
    m_velo[2] += acc[2] * dt;
    m_pos += m_velo * dt;
  }
  else
  {
    m_is_skip = false;
  }
}

void Ball::Draw()
{
  glTranslated(m_pos[0], m_pos[1], m_pos[2]);
  /*glRotated(m_radi, 1, 1, 1);*/
  DrawSphere();
  glTranslated(-m_pos[0], -m_pos[1], -m_pos[2]);
  /*glRotated(m_radi, 1, 1, 1);*/
}

void Ball::DrawSphere()
{
  const int    N = 20;
  const float M_PI = 3.141592f;
  static int D = 0;

  glEnable(GL_DEPTH_TEST);
  //Material
  float   shin[1] = { 64 };
  EVec4f  spec(1, 1, 1, 0.5f);
  EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);
  EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);
  if (D%2 == 0)
  {
    diff = EVec4f(1.0, 0.0, 0.0, 0.5f);
  }
  else
  {
    diff = EVec4f(0.0, 1.0, 0.0, 0.5f);
  }
  D++;

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
      glVertex3d(m_radi * cos(t1) * cos(p1), m_radi * sin(p1), m_radi * sin(t1) * cos(p1));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(m_radi * cos(t2) * cos(p2), m_radi * sin(p2), m_radi * sin(t2) * cos(p2));
      glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
      glVertex3d(m_radi * cos(t2) * cos(p1), m_radi * sin(p1), m_radi * sin(t2) * cos(p1));

      glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glVertex3d(m_radi * cos(t1) * cos(p1), m_radi * sin(p1), m_radi * sin(t1) * cos(p1));
      glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
      glVertex3d(m_radi * cos(t1) * cos(p2), m_radi * sin(p2), m_radi * sin(t1) * cos(p2));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(m_radi * cos(t2) * cos(p2), m_radi * sin(p2), m_radi * sin(t2) * cos(p2));

    }
  }
  glEnd();
}

EVec3f Ball::GetPos()
{
  return m_pos;
}


EVec3f Ball::GetVelo()
{
  return m_velo;
}

float Ball::GetRadi()
{
  return m_radi;
}

bool Ball::GetIsSkip()
{
  return m_is_skip;
}

void Ball::SetPos(EVec3f pos)
{
  m_pos = pos;
}

void Ball::SetVelo(EVec3f velo)
{
  m_velo = velo;
}

void Ball::SetIsSkip(bool is_skip)
{
  m_is_skip = is_skip;
}

