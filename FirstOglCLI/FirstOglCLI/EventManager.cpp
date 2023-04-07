#include "pch.h"
#include "EventManager.h"
#include "math.h"


EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  //2.855cmはビリヤード玉の半径
  m_balls.push_back(Ball(2.855f, EVec3f(2.0f, 2.855f, 0.0f), EVec3f(0.0f, 0.0f, 1.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(2.0f, 2.855f, 15.0f), EVec3f(0.0f, 0.0f, 0.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(11.0f, 2.855f, 3.0f), EVec3f(7.0f, 9.0f, 4.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(28.0f, 2.855f, 15.0f), EVec3f(6.0f, 8.0f, 2.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(11.0f, 2.855f, 30.0f), EVec3f(3.0f, 9.0f, 4.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(21.0f, 2.855f, 30.0f), EVec3f(3.0f, 9.0f, 4.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(1.0f, 2.855f, 30.0f), EVec3f(3.0f, 9.0f, 4.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(15.0f, 2.855f, 30.0f), EVec3f(3.0f, 9.0f, 4.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(30.0f, 2.855f, 30.0f), EVec3f(3.0f, 9.0f, 4.0f)));
  m_balls.push_back(Ball(2.855f, EVec3f(-1.0f, 2.855f, 30.0f), EVec3f(3.0f, 9.0f, 4.0f)));

}

void EventManager::DrawScene()
{
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//電気を消す

  //OpenGLで3本の直線を描く
  /*glBegin(GL_LINES);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();
  */

  //ビリヤード台(254cm×127cm)を描く
  glBegin(GL_TRIANGLES);
  glColor3d(0.0f, 0.3f, 0.0f);
  
  glNormal3d(0.0, 1.0 , 0.0);
  glVertex3d(127.0, 0.0, 63.5);
  glNormal3d(0.0, 1.0, 0.0);
  glVertex3d(127.0, 0.0, -63.5);
  glNormal3d(0.0, 1.0, 0.0);
  glVertex3d(-127.0, 0.0, 63.5);

  glNormal3d(0.0, 1.0, 0.0);
  glVertex3d(-127.0, 0.0, -63.5);
  glNormal3d(0.0, 1.0, 0.0);
  glVertex3d(127.0, 0.0, -63.5);
  glNormal3d(0.0, 1.0, 0.0);
  glVertex3d(-127.0, 0.0, 63.5);

  glEnd();

  for (int i = 0; i < m_balls.size(); ++i) {
      m_balls[i].Draw();
  }

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
    for (int i = 0; i < m_balls.size(); ++i) {
        m_balls[i].Step();
    }

    for (int i = 0; i < m_balls.size(); ++i) {
        for (int j = i+1; j < m_balls.size(); ++j) {
            m_balls[i].Collision(m_balls[j]);
        }
    }
}
