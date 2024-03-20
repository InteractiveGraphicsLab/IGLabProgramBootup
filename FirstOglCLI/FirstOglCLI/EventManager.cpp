#pragma once
#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "math.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  m_balls.push_back(Ball(EVec3f(2.0f, 2.855f, 0.0f), EVec3f(0.0f, 0.0f, 1.0f), 2.855f));

  //if (Lobj.loadObj("yasuda_pointcloud.obj") == true) obj = Lobj.GetObject();
}

void EventManager::DrawScene()
{
  std::cout << "DrawScene" << std::endl;
  
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//“d‹C‚ðÁ‚·

  //OpenGL‚Å3–{‚Ì’¼ü‚ð•`‚­
  //glBegin(GL_LINES);
  //glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  //glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  //glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  //glEnd();

  //int pointSize = 1;
  float t = 0.01;

  for (int i = 0; i < obj.vertices.size(); ++i) {
      glPointSize(1);
      glBegin(GL_POINTS);
      glVertex3f(obj.vertices[i].x, obj.vertices[i].y, obj.vertices[i].z);
      glEnd();

      /*
      glBegin(GL_LINES);
      glVertex3f(obj.vertices[i].x, obj.vertices[i].y, obj.vertices[i].z);
      glVertex3f(obj.vertices[i].x + t*obj.nomals[i].x, obj.vertices[i].y + t*obj.nomals[i].y, obj.vertices[i].z + t*obj.nomals[i].z);
      glEnd();
      */

  }

  glFlush();
  
  m_balls[0].Draw();

}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGL‚ÌŽ‹“_‚ð‰ñ“]‚³‚¹‚é€”õ
  /*
  EVec3f cam_pos;
  EVec3f cam_dir;
  EVec3f ball_pos;
  EVec3f velo;
  velo[0] = 0;
  velo[1] = 0;
  velo[2] = 0;
  ogl->GetCursorRay(x, y, cam_pos, cam_dir);
  for (int i = 0; i < m_balls.size(); ++i) {
      ball_pos = m_balls[i].GetPos();
      float discrimination = pow(cam_dir.dot(cam_pos - ball_pos), 2.0f) - cam_dir.squaredNorm() * ((cam_pos - ball_pos).squaredNorm() - pow(m_balls[i].GetRadius(), 2.0f));
      if (discrimination >= 0) {
          m_balls[i].SetVelo(velo);
      }

  }
  */
  //std::cout << cam_dir[0] << " " << cam_dir[1] << " " << cam_dir[2] << std::endl;
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
   // std::cout << "move" << std::endl;
  if (!m_isL && !m_isR && !m_isM) return;
  ogl->MouseMove(EVec2i(x, y));
}


void EventManager::Step()
{
    for (int i = 0; i < m_balls.size(); ++i) {
        m_balls[i].Step();
    }
}
