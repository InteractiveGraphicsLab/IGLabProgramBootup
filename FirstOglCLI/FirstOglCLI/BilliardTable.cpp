#include "pch.h"
#include "BilliardTable.h"

//コンストラクタ（メンバ変数の初期化）
BilliardTable::BilliardTable(float w, float d)
{
  m_width = w;
  m_depth = d;
}

void BilliardTable::Draw()
{
  glBegin(GL_TRIANGLES);

  //底面
  glVertex3d( m_width, 0,  m_depth);
  glVertex3d(-m_width, 0,  m_depth);
  glVertex3d(-m_width, 0, -m_depth);
                       
  glVertex3d( m_width, 0,  m_depth);
  glVertex3d( m_width, 0, -m_depth);
  glVertex3d(-m_width, 0, -m_depth);
                       

  glVertex3d( m_width, 0,  m_depth);
  glVertex3d( m_width, 0,  m_depth);
  glVertex3d( m_width, 0, -m_depth);
                       
  glVertex3d( m_width, 0,  m_depth);
  glVertex3d( m_width, 0, -m_depth);
  glVertex3d( m_width, 0, -m_depth);
                       

  glVertex3d( m_width, 0, -m_depth);
  glVertex3d( m_width, 0, -m_depth);
  glVertex3d(-m_width, 0, -m_depth);
                       
  glVertex3d( m_width, 0, -m_depth);
  glVertex3d(-m_width, 0, -m_depth);
  glVertex3d(-m_width, 0, -m_depth);
                       

  glVertex3d(-m_width, 0, -m_depth);
  glVertex3d(-m_width, 0, -m_depth);
  glVertex3d(-m_width, 0,  m_depth);
                       
  glVertex3d(-m_width, 0, -m_depth);
  glVertex3d(-m_width, 0,  m_depth);
  glVertex3d(-m_width, 0,  m_depth);


  glVertex3d(-m_width, 0,  m_depth);
  glVertex3d(-m_width, 0,  m_depth);
  glVertex3d( m_width, 0,  m_depth);
                       
  glVertex3d(-m_width, 0,  m_depth);
  glVertex3d( m_width, 0,  m_depth);
  glVertex3d( m_width, 0,  m_depth);

  glEnd();
}

float BilliardTable::GetWidth()
{
  return m_width;
}

float BilliardTable::GetDepth()
{
  return m_depth;
}
