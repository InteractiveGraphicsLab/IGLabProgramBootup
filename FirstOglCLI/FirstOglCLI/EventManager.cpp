#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
}

void EventManager::DrawScene()
{
    const int N = 20;
    const float PI = 3.1415f;
    const int radi = 2;

    glLineWidth(2.0f);
    glDisable(GL_LIGHTING);//電気を消す

  //OpenGLで3本の直線を描く
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();

  glBegin(GL_TRIANGLES);
  for (int y = 0; y < N; y++)
  {
      for (int x = 0; x < N; x++)
      {
          double t1 = (x) / (double)N * 2.0 * PI;
          double t2 = (x + 1.0) / (double)N * 2.0 * PI;
          double p1 = (y) / (double)N * 1.0 * PI - 0.5 * PI;
          double p2 = (y + 1.0) / (double)N * 1.0 * PI - 0.5 * PI;

          glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
          glVertex3d(cos(t1) * cos(p1) * radi, sin(p1) * radi, sin(t1) * cos(p1) * radi);
          glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
          glVertex3d(cos(t2) * cos(p2) * radi, sin(p2) * radi, sin(t2) * cos(p2) * radi);
          glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
          glVertex3d(cos(t2) * cos(p1) * radi, sin(p1) * radi, sin(t2) * cos(p1) * radi);

          glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
          glVertex3d(cos(t1) * cos(p1) * radi, sin(p1) * radi, sin(t1) * cos(p1) * radi);
          glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
          glVertex3d(cos(t1) * cos(p2) * radi, sin(p2) * radi, sin(t1) * cos(p2) * radi);
          glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
          glVertex3d(cos(t2) * cos(p2) * radi, sin(p2) * radi, sin(t2) * cos(p2) * radi);

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
