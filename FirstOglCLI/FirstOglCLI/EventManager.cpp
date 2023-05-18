#include "pch.h"
#include "EventManager.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

static double M_PI = 3.141592;



EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  m_balls.push_back(Ball(1.0f, EVec3f(0,0,10.f), EVec3f(0,0,-1.f)));
}




void EventManager::DrawScene()
{
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//電気を消す

  //OpenGLで3本の直線を描く
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();


  //ビリヤード台
  glColor3d(0.4, 0.7, 0.15); 
  glBegin(GL_TRIANGLES);
  for (int j = -20; j < 20; ++j) {
      for (int i = -25; i < 30; ++i) {
          glVertex3d(j, i, 0); glVertex3d(j + 1, i, 0); glVertex3d(j + 1, i + 1, 0);
          glVertex3d(j, i, 0); glVertex3d(j, i + 1, 0); glVertex3d(j + 1, i + 1, 0);
      }
  }

  //glVertex3d(10, 0, 0); glVertex3d(-3, -4, 0); glVertex3d(-3, 4, 0);
  glEnd();
 
  m_balls[0].Draw();
 
}






void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLの視点を回転させる準備
}

void EventManager::MBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isM = true;
  ogl->BtnDown_Zoom(EVec2i(x, y));
}

void EventManager::RBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isR = true;
  ogl->BtnDown_Rot(EVec2i(x, y));
}

void EventManager::LBtnUp(int x, int y, OglForCLI* ogl)
{
  m_isL = false;
  ogl->BtnUp();
}

void EventManager::MBtnUp(int x, int y, OglForCLI* ogl)
{
  m_isM = false;
  ogl->BtnUp();
}

void EventManager::RBtnUp(int x, int y, OglForCLI* ogl)
{
  m_isR = false;
  ogl->BtnUp();
}

void EventManager::MouseMove(int x, int y, OglForCLI* ogl)
{
  if (!m_isL && !m_isR && !m_isM) return;
  ogl->MouseMove(EVec2i(x, y));
}


void EventManager::Step()
{
    m_balls[0].Step();
    m_balls[0].Bound();
}
