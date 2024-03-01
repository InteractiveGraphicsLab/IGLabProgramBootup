#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  _balls.push_back(Ball(EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(1.0f, 0.0f, 0.0f), EVec3f(0.0f, 0.0f, 0.0f), 0.5f));
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

  for (int i = 0; i < _balls.size(); i++)
  {
      _balls[i].Draw();
  }
}

void EventManager::Collision()
{
    for (int i = 0; i < _balls.size(); i++)
    {
        for (int j = i+1; j < _balls.size(); j++)
        {
            EVec3f d = _balls[j].GetPos() - _balls[i].GetPos();
            EVec3f dn = d.normalized();
            float radi = _balls[i].GetRadi() + _balls[j].GetRadi();

            if (d.norm() > radi) continue;

            EVec3f vec_par1 = _balls[i].GetVelo().dot(dn) * dn;
            EVec3f vec_ver1 = _balls[i].GetVelo() - vec_par1;
            EVec3f vec_par2 = _balls[j].GetVelo().dot(dn) * dn;
            EVec3f vec_ver2 = _balls[j].GetVelo() - vec_par2;
            _balls[i].SetVelo(vec_par2 + vec_ver1);
            _balls[j].SetVelo(vec_par1 + vec_ver2);

            float distance = (radi - d.norm()) / 2.0f;
            _balls[i].SetPos(_balls[i].GetPos() - dn * distance);
            _balls[j].SetPos(_balls[j].GetPos() + dn * distance);
        }
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
    for (int i = 0; i < _balls.size(); i++)
    {
        _balls[i].Step();
    }
    Collision();
}
