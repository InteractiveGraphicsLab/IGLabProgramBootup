#include "pch.h"
#include "BilliardTable.h"

//�R���X�g���N�^�i�����o�ϐ��̏������j
BilliardTable::BilliardTable(float w, float d)
{
  m_width = w;
  m_depth = d;
}

void BilliardTable::Draw()
{
  glBegin(GL_TRIANGLES);

  //���
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
