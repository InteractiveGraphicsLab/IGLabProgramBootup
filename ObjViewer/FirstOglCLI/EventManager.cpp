#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
}

void EventManager::DrawScene()
{
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);//電気を消す



  if (m_mesh.m_vSize > 0)
  {
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3d(1, 1, 1);
    m_img.BindOgl(true);
    m_mesh.draw();
  }
  

  //OpenGLで3本の直線を描く
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
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



void EventManager::LoadMatrxTxt(std::string fname, OglForCLI* ogl)
{

  std::ifstream ifs(fname.c_str());
  if (!ifs)
  {
    std::cout << "ファイルが開けませんでした。\n";
    return;
  }

  float f, cx, cy;
  ifs >> f >> cx >> cy;

  float a11, a12, a13, a21, a22, a23, a31, a32, a33, t1, t2, t3;
  ifs >> a11 >> a12 >> a13 >> a21 >> a22 >> a23 >> a31 >> a32 >> a33;
  ifs >> t1 >> t2 >> t3;

  EVec3f eye_pos(t1, t2, t3);
  EVec3f eye_ray(-a13, -a23, -a33); //-z方向
  EVec3f eye_up (a12, a22, a23);
  eye_ray.normalize();
  eye_up .normalized();
  
  float t = -eye_ray.dot(eye_pos) / eye_ray.dot(eye_ray); //視線上で原点に一番近い点を見つける
  EVec3f eye_cnt = eye_pos + t * eye_ray;

  ogl->oglMakeCurrent();
  ogl->SetCam(eye_pos, eye_cnt, eye_up);
  
  //FoVとできればviewportサイズも

}
