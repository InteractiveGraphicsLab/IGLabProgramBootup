#include "stdafx.h"
#include "MainForm.h"
#include "EventManager.h"

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>





class MyVec3
{
private: 
  //�����Ɋe�ϐ���private�ϐ��ɂȂ�O����͌����Ȃ�
  int m_priv;
  
public: 
  //�����Ɋe�ϐ���public�ϐ��ɂȂ�O����Q�ƁE�C���\
  int m_publ;

  float m_data[3];
  
  //constructrue
  MyVec3(float x = 0, float y = 0, float z = 0)
  {
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
  }

  MyVec3(const MyVec3 &src)
  {
    //todo copy
    
  }

  MyVec3 &operator=(const MyVec3 &src)
  {
    //todo copy
    return *this;
  }

  //�I�y���[�^�[�I�[�o�[���[�h
  MyVec3 operator+(const MyVec3 &v){
    MyVec3 p;
    p.m_data[0] = this->m_data[0] + v.m_data[0];
    p.m_data[1] = this->m_data[1] + v.m_data[1];
    p.m_data[2] = this->m_data[2] + v.m_data[2];
    return p;
  }

  void Trace()
  {
    std::cout << m_data[0] << m_data[1] << m_data[2];
  }
};


EventManager::EventManager()
{
  std::cout << "EventManager constructor\n";
  MyVec3 p(1,2,3);
  MyVec3 q(1,2,3);
  auto a = p + q;
  p.Trace();
  q.Trace();
  a.Trace();

  m_object.push_back(new RigidPlane(RigidObject::Plane, 8, 14, 1, EVec3f(0, 0, 0), EVec3f(0, 0, 0)));

  m_btn_right = m_btn_left = m_btn_middle = false;
}



void EventManager::BtnDownLeft  (int x, int y, OglForCLI *ogl)
{
  m_btn_left = true;
  ogl->BtnDown_Trans( EVec2i(x,y) );
} 

void EventManager::BtnDownMiddle(int x, int y, OglForCLI *ogl)
{
  m_btn_middle = true;
  ogl->BtnDown_Zoom( EVec2i(x,y) );
}

void EventManager::BtnDownRight (int x, int y, OglForCLI *ogl)
{
  m_btn_right = true;
  ogl->BtnDown_Rot( EVec2i(x,y) );
}



void EventManager::BtnUpLeft  (int x, int y, OglForCLI *ogl)
{
  m_btn_left = false;
  ogl->BtnUp();
}

void EventManager::BtnUpMiddle(int x, int y, OglForCLI *ogl)
{
  m_btn_middle = false;
  ogl->BtnUp();
}

void EventManager::BtnUpRight (int x, int y, OglForCLI *ogl)
{
  m_btn_right = false;
  ogl->BtnUp();
}

void EventManager::MouseMove    (int x, int y, OglForCLI *ogl)
{
  if ( !m_btn_right && !m_btn_middle && !m_btn_left) return;

  ogl->MouseMove( EVec2i(x,y) );
}

void EventManager::ClickGenerateBtn()
{
  m_object.push_back(new RigidSphere(RigidObject::Sphere, 2, 1, EVec3f(0, 10, 0), EVec3f(0, 0, 0)));
}

////�r�����[�h���`��ixz���ʂ̕ӂɍ�����wall_height�̕ǂ�t�������́j
//static void DrawBilliardTable() {
//
//  glEnable(GL_CULL_FACE);
//  glDisable(GL_CULL_FACE);
//  glBegin(GL_TRIANGLES);
//  glColor3d(0, 0.5, 0);
//  glNormal3f(0, 0, 1);
//  glVertex3f(-FLOOR_WIDTH, 0, -FLOOR_LENGTH);
//  glVertex3f( FLOOR_WIDTH, 0, -FLOOR_LENGTH);
//  glVertex3f(FLOOR_WIDTH,  0,  FLOOR_LENGTH);
//
//  glVertex3f(-FLOOR_WIDTH, 0, -FLOOR_LENGTH);
//  glVertex3f( FLOOR_WIDTH, 0, FLOOR_LENGTH);
//  glVertex3f(-FLOOR_WIDTH, 0, FLOOR_LENGTH);
//  glEnd();
//}

void EventManager::DrawScene(){
  //����`��
  glBegin(GL_LINES );
  glColor3d(1,0,0); glVertex3d(0,0,0); glVertex3d(10,0,0);
  glColor3d(0,1,0); glVertex3d(0,0,0); glVertex3d(0,10,0);
  glColor3d(0,0,1); glVertex3d(0,0,0); glVertex3d(0,0,10);
  glEnd();

  //���C�g�_��
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);


  //const static float diff[4] = { 1.0f, 0.2f, 0, 0.3f };
  //const static float ambi[4] = { 1.0f, 0.2f, 0, 0.3f };
  //const static float diffG[4] = { 0.2f, 0.8f, 0.2f, 0.3f };
  //const static float ambiG[4] = { 0.2f, 0.8f, 0.2f, 0.3f };
  //const static float spec[4] = { 1,1,1,0.3f };
  //const static float shin[1] = { 64.0f };
  //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffG);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiG);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);


  ////�r�����[�h���`��
  //DrawBilliardTable();

  //RigidObject�Q��`��
  for (int i = 0; i < (int)m_object.size(); ++i)
  {
    m_object[i]->DrawObject();
  }
}


void EventManager::Step()
{
  //todo����
  //std::cout << "step";

  for (int i = 0; i < (int)m_object.size(); ++i)
  {
    m_object[i]->StepSimulation(EVec3f(0, 0, 0));
    //�ړ��v�Z OK
    //��]��   TODO ��K
  }
  

  ////�������� 
  //for (int i = 0; i < (int)m_balls.size(); ++i)
  //{
  //  for (int j = i + 1; j < (int)m_balls.size(); ++j)
  //  {
  //    m_balls[i];
  //    m_balls[j];
  //  }
  //}

  OpenglOnCli::MainForm_RedrawPanel();

}


