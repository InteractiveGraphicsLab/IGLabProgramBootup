#include "pch.h"
#include "BilliardTable.h"


BilliardTable::BilliardTable()
{
  m_pos = EVec3f(0, 10, 0);
  m_width = 15;
  m_height = 10;
  m_depth = 28;
  m_bounce = 1.0f; // îΩî≠åWêî
}

void BilliardTable::Draw()
{
  DrawBilliardTable();
}

void BilliardTable::DrawBilliardTable()
{
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

  EVec3f twoPos[2];
  twoPos[0] = m_pos - EVec3f(m_width, m_height, m_depth);
  twoPos[1] = m_pos + EVec3f(m_width, m_height, m_depth);


  glVertex3f(twoPos[0][0], twoPos[0][1], twoPos[0][2]);
  glVertex3f(twoPos[1][0], twoPos[0][1], twoPos[0][2]);
  glVertex3f(twoPos[0][0], twoPos[0][1], twoPos[1][2]);

  glVertex3f(twoPos[1][0], twoPos[0][1], twoPos[1][2]);
  glVertex3f(twoPos[1][0], twoPos[0][1], twoPos[0][2]);
  glVertex3f(twoPos[0][0], twoPos[0][1], twoPos[1][2]);

  glEnd();
}

EVec3f BilliardTable::GetPos()
{
  return m_pos;
}

float BilliardTable::GetWidth()
{
  return m_width;
}

float BilliardTable::GetHeight()
{
  return m_height;
}

float BilliardTable::GetDepth()
{
  return m_depth;
}

float BilliardTable::GetBounce()
{
  return m_bounce;
}
