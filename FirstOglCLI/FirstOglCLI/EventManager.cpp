#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  m_balls.push_back( Ball(1, EVec3f(1,  0, 0), EVec3f(0, 1, 0)));
  m_balls.push_back( Ball(1, EVec3f(0,  2, 0), EVec3f(0, 2, 2)));
  m_balls.push_back( Ball(1, EVec3f(1, 10, 0), EVec3f(0, 3, 3)));
  
}





static double x_pos = 0;

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

  for ( int i=0; i < m_balls.size(); ++i)
    m_balls[i].Draw();

  //for (std::vector<Ball>::iterator it = m_balls.begin(); it != m_balls.end(); ++it)
  //  it->Draw();

  //for (auto& i : m_balls) i.Draw();

  //x_pos += 0.1;
  //glTranslated(  x_pos, 0, 0);
  //DrawSphere(3,20);
  //glTranslated(- x_pos, 0, 0);

  //DrawIta(10);
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
  for (auto& i : m_balls) i.Step();
}



/*
void DrawIta(int N = 20)
{
  glBegin(GL_TRIANGLES);
  for (int y = 0; y < N; ++y)
  {
    for (int x = 0; x < N; ++x)
    {
      double x1 = x / (double)N * 3;
      double x2 = (x + 1) / (double)N * 3;
      double y1 = y / (double)N * 3;
      double y2 = (y + 1) / (double)N * 3;

      glVertex3d(x1, y1, 0);
      glVertex3d(x2, y1, 0);
      glVertex3d(x2, y2, 0);

    }
  }
  glEnd();
}


void DrawSphere(double r, int N = 20)
{
  glEnable(GL_DEPTH_TEST);
  //Material 
  float   shin[1] = { 64 };
  EVec4f  spec(1, 1, 1, 0.5);
  EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);
  EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  glBegin(GL_TRIANGLES);
  for (int y = 0; y < N; ++y)
  {
    for (int x = 0; x < N; ++x)
    {
      double t1 = (x) / (double)N * 2.0 * M_PI;
      double t2 = (x + 1) / (double)N * 2.0 * M_PI;
      double p1 = (y) / (double)N * 1.0 * M_PI - 0.5 * M_PI;
      double p2 = (y + 1) / (double)N * 1.0 * M_PI - 0.5 * M_PI;

      glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glVertex3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
      glVertex3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));

      glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glVertex3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
      glVertex3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));

    }
  }

  glEnd();
}

*/