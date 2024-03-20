#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  balls_.push_back(Ball(EVec3f(0, 0, 0), EVec3f(0, 0, 0), 1.0f));
}

void EventManager::DrawScene()
{
  for (const auto& b : balls_) {
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
  for (auto& b : balls_) {
    b.Step();
  }

  /*for (auto& b : balls_) {
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
