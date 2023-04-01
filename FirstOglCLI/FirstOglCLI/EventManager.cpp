#include "pch.h"
#include "EventManager.h"

// Unity‚Ì‹N“®
EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  m_balls.push_back(Ball(1, EVec3f(-1.0, 0, 0), EVec3f(0.0, 0.0, -1.0)));
  //m_balls.push_back(Ball(1, EVec3f(0, 0, 0), EVec3f(0, 2, 2)));
  //m_balls.push_back(Ball(1, EVec3f(0, 0, 0), EVec3f(0, 3, 3)));
}


void EventManager::DrawTable()
{
  glBegin(GL_TRIANGLES);

  //’ê–Ê
  glVertex3d(20, -1, 20);
  glVertex3d(-20, -1, 20);
  glVertex3d(-20, -1, -20);

  glVertex3d(20, -1, 20);
  glVertex3d(20, -1, -20);
  glVertex3d(-20, -1, -20);

  //‘¤–Ê‚P
  glVertex3d(20, -1, 20);
  glVertex3d(20, 1, 20);
  glVertex3d(20, 1, -20);

  glVertex3d(20, -1, 20);
  glVertex3d(20, -1, -20);
  glVertex3d(20, 1, -20);

  //‘¤–Ê‚Q
  glVertex3d(20, -1, -20);
  glVertex3d(20, 1, -20);
  glVertex3d(-20, 1, -20);

  glVertex3d(20, -1, -20);
  glVertex3d(-20, -1, -20);
  glVertex3d(-20, 1, -20);

  //‘¤–Ê‚R
  glVertex3d(-20, -1, -20);
  glVertex3d(-20, 1, -20);
  glVertex3d(-20, 1, 20);

  glVertex3d(-20, -1, -20);
  glVertex3d(-20, -1, 20);
  glVertex3d(-20, 1, 20);

  //‘¤–Ê‚S
  glVertex3d(-20, -1, 20);
  glVertex3d(-20, 1, 20);
  glVertex3d(20, 1, 20);

  glVertex3d(-20, -1, 20);
  glVertex3d(20, -1, 20);
  glVertex3d(20, 1, 20);

  glEnd();
}

// •`‰æˆ—
void EventManager::DrawScene()
{
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//“d‹C‚ğÁ‚·

  //OpenGL‚Å3–{‚Ì’¼ü‚ğ•`‚­
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();

  glColor3f(0.1f, 0.4f, 0.2f);
  DrawTable();

  for (int i = 0; i < m_balls.size(); ++i)
    m_balls[i].Draw();
}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGL‚Ì‹“_‚ğ‰ñ“]‚³‚¹‚é€”õ
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


// UpdateŠÖ”
void EventManager::Step()
{
  for (int i = 0; i < m_balls.size(); ++i)
  {
    m_balls[i].Step();
  }
}



void DrawSphere()
{

}