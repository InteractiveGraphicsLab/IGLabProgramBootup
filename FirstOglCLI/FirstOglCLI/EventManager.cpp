#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  balls_.push_back(Ball(EVec3f(0, 0, 0), EVec3f(0, 0, 0), 1.0f));
}

void EventManager::DrawScene()
{
  for (const Ball& b : balls_) {
    b.Draw();
  }

  BilliardTable::GetInst()->Draw();
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
  for (Ball& b : balls_) {
    b.Step();
  }

  /*for (Ball& b : balls_) {
    if (IsCollisionWithBalls(b))
    {
      ProcessCollisionWithBalls(b);
    }

    if (IsCollisionWithBilliardTable(b))
    {
      ProcessCollisionWithBilliardTable(b);
    }
  }*/
}

//bool EventManager::IsCollisionWithBalls(const Ball& ball) const
//{
//  return; //Todo
//}
//
//void EventManager::ProcessCollisionWithBalls(const Ball& ball)
//{
//  return; //Todo
//}
//
//bool EventManager::IsCollisionWithBilliardTable(const Ball& ball) const
//{
//  return; //Todo
//}
//
//void EventManager::ProcessCollisionWithBilliardTable(const Ball& ball)
//{
//  return; //Todo
//}

int* EventManager::GetCollisionList() const
{
  const float bounce = 1.0f;

  for (const Ball& b1 : balls_) {
    for (const Ball& b2 : balls_) {
      EVec3f b1_pos  = b1.GetPos();
      EVec3f b2_pos  = b2.GetPos();
      float  b1_radi = b1.GetRadi();
      float  b2_radi = b2.GetRadi();
      EVec3f b1_velo = b1.GetVelo();
      EVec3f b2_velo = b2.GetVelo();

      EVec3f q = b1_pos - b2_pos;
      EVec3f u = b1_velo - b2_velo;

      float discri = powf(q.dot(u), 2.0f) - u.squaredNorm() * (q.squaredNorm() - powf(b1_radi + b2_radi, 2.0f));

      if (discri > 0.0f && u.norm() > 0.0f)
      {
        float C = (-q.dot(u) - sqrtf(discri)) / u.squaredNorm();
        std::cout << C << std::endl;
        if (C >= 0.0f && C <= t)
        {
          return true;
        }
      }
      return false;
    }
  }
};