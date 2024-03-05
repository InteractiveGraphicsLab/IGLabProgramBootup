#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "Box.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  //箱の大きさを設定
  EVec3d max1 = { 20.0f, 10.0f, 20.0f };
  box1_.setMax(max1);

  //球の初期位置をセット
  EVec3d pos1 = { 1.0f, 2.0f, 3.0f }, pos2 = { 2.0f, 3.0f, 4.0f }, pos3 = { 3.0f, 4.0f, 5.0f };
  b1_.setPos(pos1);
  b2_.setPos(pos2);
  b3_.setPos(pos3);

  //球の初速をセット
  EVec3d v1 = { 2.0f, 2.0f, 2.0f }, v2 = { 3.0f, 3.0f, 3.0f }, v3 = { 4.0f, 4.0f, 4.0f };
  b1_.setVelocity(v1);
  b2_.setVelocity(v2);
  b3_.setVelocity(v3);
}


void EventManager::DrawScene()
{
  //箱を書く
  box1_.Draw();

  //x:red, y:green, z:blue 
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//電気を消す

  //OpenGLで3本の直線を描く
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();

  //電気をつける
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  //球を描く
  b1_.Draw();
  b2_.Draw();
  b3_.Draw();


  //電気を消す
  glDisable(GL_LIGHTING);

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
	b1_.setVelocity(b1_.CalcVelocity(b1_.getVelocity())); // 球１の速度を更新
	b2_.setVelocity(b2_.CalcVelocity(b2_.getVelocity())); // 球２
	b3_.setVelocity(b3_.CalcVelocity(b3_.getVelocity())); // 球３

	b1_.Step();//球１の位置を更新
	b2_.Step();//球２
	b3_.Step();//球３
}
