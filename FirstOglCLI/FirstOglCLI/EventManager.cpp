#include "pch.h"
#include "EventManager.h"


EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  m_balls.push_back(Ball(EVec3f(0,0,0), EVec3f(0, 0, 0), EVec3f(0, 0, 0), EVec3f(0, 0, 0)));
  m_balls.push_back(Ball(EVec3f(10,0,0), EVec3f(0, 0, 0), EVec3f(0, 0, 0), EVec3f(0, 0, 0)));
  m_balls.push_back(Ball(EVec3f(0,10,0), EVec3f(0, 0, 0), EVec3f(0, 0, 0), EVec3f(0, 0, 0)));
}

void EventManager::DrawScene()
{
  glEnable(GL_DEPTH_TEST);
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//“d‹C‚ðÁ‚·

  //OpenGL‚Å3–{‚Ì’¼ü‚ð•`‚­
  //glBegin(GL_LINES);
  //glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  //glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  //glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  //glEnd();

  //glBegin(GL_TRIANGLES);
  //glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  //glVertex3d(10, 10, 0);
  //glEnd();

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  m_balls[0].Draw();
  m_balls[1].Draw();
  m_balls[2].Draw();
  


}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGL‚ÌŽ‹“_‚ð‰ñ“]‚³‚¹‚é€”õ
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

}
