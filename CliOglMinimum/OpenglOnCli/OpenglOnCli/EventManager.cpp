#include "stdafx.h"
#include "MainForm.h"
#include "EventManager.h"

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>





class MyVec3
{
private: 
  //ここに各変数はprivate変数になり外からは見えない
  int m_priv;
  
public: 
  //ここに各変数はpublic変数になり外から参照・修正可能
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

  //オペレーターオーバーロード
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

  m_object.push_back(new RigidPlane(RigidObject::Plane, 8, 14, 1, EVec3f(0, 0, 0),   EVec3f(0, 0, 0)));
  m_object.push_back(new RigidSphere(RigidObject::Sphere, 2, 1,   EVec3f(0, 10, 0),  EVec3f(0, 0, 0)));

  m_btn_right = m_btn_left = m_btn_middle = false;
  m_cursorPos = m_cursorDir = EVec3f(0, 0, 0);
  m_dt = 0.1;
  m_pickObjID = -1;
}



void EventManager::BtnDownLeft  (int x, int y, OglForCLI *ogl)
{
  m_btn_left = true;

  ogl->GetCursorRay(EVec2i(x, y), m_cursorPos, m_cursorDir);
  for (int i = 0; i < (int)m_object.size(); ++i)
  {
    if (m_object[i]->isPickedObject(m_cursorPos, m_cursorDir)==true)
    {
      this->m_pickObjID = i;
    }
  }
  
  if(m_pickObjID ==-1) ogl->BtnDown_Trans(EVec2i(x, y));
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

  if (m_pickObjID == -1) return;

  ////引っ張り処理orパチンコ処理実装
  //this->m_object[m_pickObjID]->SetForce()

  m_pickObjID = -1;
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

  if (m_pickObjID != -1)
  {
    ogl->GetCursorRay(EVec2i(x, y), m_cursorPos, m_cursorDir);
  }
  else
  {
    ogl->MouseMove(EVec2i(x, y));
  }
}

void EventManager::ClickGenerateBtn()
{
  m_object.push_back(new RigidSphere(RigidObject::Sphere, 2, 1, EVec3f(0, 10, 0), EVec3f(0, 0, 0)));
}

////ビルヤード台を描画（xz平面の辺に高さがwall_heightの壁を付けたもの）
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
  for (int i = (int)m_object.size()-1; i >=0 ; --i)
  {
    for (int j = i -1; j >=0 ; --j)
    {
      m_object[i]->CollisionDetection(m_object[j], m_dt);
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


