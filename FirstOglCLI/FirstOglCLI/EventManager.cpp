#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
}

void EventManager::DrawScene()
{
  glEnable(GL_DEPTH_TEST);
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//電気を消す

  //OpenGLで3本の直線を描く
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();

  //glBegin(GL_TRIANGLES);
  //glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  //glVertex3d(10, 10, 0);
  //glEnd();

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  const int N = 30;
  glPointSize(3);
  glBegin(GL_TRIANGLES);
  for (int t = 0; t < N; t++)
  {
	  for (int p = 0; p < N; p++)
	  {
		  float t1 = t / (float)N * 2 * 3.141592;
		  float t2 = (t + 1) / (float)N * 2 * 3.141592;
		  float p1 = p / ((float)N - 0.5f) * 3.141592;
		  float p2 = (p + 1) / ((float)N - 0.5f) * 3.141592;
		  glNormal3d(cos(p1) * cos(t1), cos(p1) * sin(t1), sin(p1));
		  glVertex3d(2 * cos(p1) * cos(t1), 2 * cos(p1) * sin(t1), 2 * sin(p1));
		  glVertex3d(2 * cos(p2) * cos(t1), 2 * cos(p2) * sin(t1), 2 * sin(p2));
		  glVertex3d(2 * cos(p2) * cos(t2), 2 * cos(p2) * sin(t2), 2 * sin(p2));
		  glVertex3d(2 * cos(p1) * cos(t1), 2 * cos(p1) * sin(t1), 2 * sin(p1));
		  glVertex3d(2 * cos(p2) * cos(t2), 2 * cos(p2) * sin(t2), 2 * sin(p2));
		  glVertex3d(2 * cos(p1) * cos(t2), 2 * cos(p1) * sin(t2), 2 * sin(p1));

	  }
  }
  glEnd();

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

}
