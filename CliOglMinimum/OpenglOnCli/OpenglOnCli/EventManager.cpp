#include "stdafx.h"
#include "MainForm.h"
#include "EventManager.h"

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

EventManager::EventManager()
{
  this->m_object.push_back(new RigidPlane(RigidObject::Plane, 8, 14, 1, EVec3f(0, 0, 0),   EVec3f(0, 0, 0)));
  this->m_object.push_back(new RigidSphere(RigidObject::Sphere, 2, 1,   EVec3f(8, 10, 0),  EVec3f(0, 0, 0)));

  this->m_btn_right = this->m_btn_left = this->m_btn_middle = false;
  this->m_cursorPos = this->m_cursorDir = EVec3f(0, 0, 0);
  this->m_dt = 0.1;
  this->m_pickObjID = -1;
  this->m_calcCollision = new CollisionCalculator(this->m_dt);
}

//マウスボタンクリック
void EventManager::BtnDownLeft  (int x, int y, OglForCLI *ogl)
{
  this->m_btn_left = true;

  ogl->GetCursorRay(EVec2i(x, y), this->m_cursorPos, this->m_cursorDir);
  for (int i = 0; i < (int)this->m_object.size(); ++i)
  {
    if (this->m_object[i]->isPickedObject(m_cursorPos, m_cursorDir)==true)
    {
      this->m_pickObjID = i;
    }
  }
  
  if(this->m_pickObjID ==-1) ogl->BtnDown_Trans(EVec2i(x, y));
} 
void EventManager::BtnDownMiddle(int x, int y, OglForCLI *ogl)
{
  this->m_btn_middle = true;
  ogl->BtnDown_Zoom( EVec2i(x,y) );
}
void EventManager::BtnDownRight (int x, int y, OglForCLI *ogl)
{
  this->m_btn_right = true;
  ogl->BtnDown_Rot( EVec2i(x,y) );
}

//マウスボタンリリース
void EventManager::BtnUpLeft  (int x, int y, OglForCLI *ogl)
{
  this->m_btn_left = false;
  ogl->BtnUp();

  if (this->m_pickObjID == -1) return;

  this->m_pickObjID = -1;
}
void EventManager::BtnUpMiddle(int x, int y, OglForCLI *ogl)
{
  this->m_btn_middle = false;
  ogl->BtnUp();
}
void EventManager::BtnUpRight (int x, int y, OglForCLI *ogl)
{
  this->m_btn_right = false;
  ogl->BtnUp();
}

//マウスムーブ
void EventManager::MouseMove    (int x, int y, OglForCLI *ogl)
{
  if ( !this->m_btn_right && !this->m_btn_middle && !this->m_btn_left) return;

  if (this->m_pickObjID != -1)
  {
    ogl->GetCursorRay(EVec2i(x, y), this->m_cursorPos, this->m_cursorDir);
  }
  else
  {
    ogl->MouseMove(EVec2i(x, y));
  }
}

//MainFormボタンイベント
void EventManager::ClickGenerateBtn()
{
  this->m_object.push_back(new RigidSphere(RigidObject::Sphere, 2, 1, EVec3f(0, 10, 0), EVec3f(0, 0, 0)));
}

//描画処理
void EventManager::DrawScene(){
  //軸を描画
  glBegin(GL_LINES );
  glColor3d(1,0,0); glVertex3d(0,0,0); glVertex3d(10,0,0);
  glColor3d(0,1,0); glVertex3d(0,0,0); glVertex3d(0,10,0);
  glColor3d(0,0,1); glVertex3d(0,0,0); glVertex3d(0,0,10);
  glEnd();

  //ライト点灯
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  //RigidObject群を描画
  for (int i = 0; i < (int)m_object.size(); ++i)
  {
    m_object[i]->DrawObject();
  }

  //掴んで引っ張った際の紐の描画
  if (m_pickObjID != -1)
  {
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3fv(m_cursorPos.data());
    glVertex3fv(m_object[m_pickObjID]->GetPosition().data());
    glEnd();
  }
}


void EventManager::Step()
{
  //todo処理
  //std::cout << "step";

  //  //交差判定 
  //for (int i = 0; i < (int)m_object.size(); ++i)
  //{
  //  for (int j = i + 1; j < (int)m_object.size(); ++j)
  //  {
  //    m_object[i]->CollisionDetection(m_object[j], m_dt);
  //  }
  //}
  //for (int i = (int)m_object.size()-1; i >=0 ; --i)
  //{
  //  for (int j = i -1; j >=0 ; --j)
  //  {
  //    m_object[i]->CollisionDetection(m_object[j], m_dt);
  //  }
  //}
  for (int i = 0; i < (int)m_object.size(); ++i)
  {
    for (int j = i + 1; j < (int)m_object.size(); ++j)
    {
      m_calcCollision->CollisionDetection(*m_object[i], *m_object[j]);
    }
  }

  for (int i = 0; i < (int)m_object.size(); ++i)
  {
    m_object[i]->StepSimulation(EVec3f(0, 0, 0), this->m_dt);
    //移動計算 OK
    //回転も   TODO 井尻
  }
  
  OpenglOnCli::MainForm_RedrawPanel();
}


