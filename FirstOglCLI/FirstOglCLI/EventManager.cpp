#include "pch.h"
#include "EventManager.h"

// UnityÇÃãNìÆ
EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  m_balls.push_back(Ball(1, EVec3f(-1.0, 0, 0), EVec3f(1, 0.0,0)));
  //m_balls.push_back(Ball(1, EVec3f(0, 0, 0), EVec3f(0, 2, 2)));
  //m_balls.push_back(Ball(1, EVec3f(0, 0, 0), EVec3f(0, 3, 3)));
}


void EventManager::DrawTable()
{
  glBegin(GL_TRIANGLES);

  //íÍñ 
  glVertex3d(20, -1, 20);
  glVertex3d(-20, -1, 20);
  glVertex3d(-20, -1, -20);

  glVertex3d(20, -1, 20);
  glVertex3d(20, -1, -20);
  glVertex3d(-20, -1, -20);

  //ë§ñ ÇP
  glVertex3d(20, -1, 20);
  glVertex3d(20, 1, 20);
  glVertex3d(20, 1, -20);

  glVertex3d(20, -1, 20);
  glVertex3d(20, -1, -20);
  glVertex3d(20, 1, -20);

  //ë§ñ ÇQ
  glVertex3d(20, -1, -20);
  glVertex3d(20, 1, -20);
  glVertex3d(-20, 1, -20);

  glVertex3d(20, -1, -20);
  glVertex3d(-20, -1, -20);
  glVertex3d(-20, 1, -20);

  //ë§ñ ÇR
  glVertex3d(-20, -1, -20);
  glVertex3d(-20, 1, -20);
  glVertex3d(-20, 1, 20);

  glVertex3d(-20, -1, -20);
  glVertex3d(-20, -1, 20);
  glVertex3d(-20, 1, 20);

  //ë§ñ ÇS
  glVertex3d(-20, -1, 20);
  glVertex3d(-20, 1, 20);
  glVertex3d(20, 1, 20);

  glVertex3d(-20, -1, 20);
  glVertex3d(20, -1, 20);
  glVertex3d(20, 1, 20);

  glEnd();
}

// ï`âÊèàóù
void EventManager::DrawScene()
{
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//ìdãCÇè¡Ç∑

  //OpenGLÇ≈3ñ{ÇÃíºê¸Çï`Ç≠
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();

  glColor3f(0.1f, 0.4f, 0.2f);
  DrawTable();

  for (int i = 0; i < m_balls.size(); ++i)
    m_balls[i].Draw();
}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLÇÃéãì_ÇâÒì]Ç≥ÇπÇÈèÄîı
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


static void SolveReflection(Ball &ball)
{
  EVec3f pos = ball.GetPos();
  EVec3f velo = ball.GetVelo();
  float radi = ball.GetRadi();

  //îΩéÀ
  if (pos[1] < 0)
  {
    velo[1] *= -0.97f;
    pos[1] = 0.00001f;
  }

  if (fabs(pos[0]) - (20 - radi) > 0)
  {
    velo[0] *= -1.0f;
    pos[0] = (pos[0] > 0) ? (20 - radi) : (radi - 20);
  }

  if (fabs(pos[2]) - (20 - radi) > 0)
  {
    velo[2] *= -1.0f;
    pos[2] = (pos[2] > 0) ? (20 - radi) : (radi - 20);
  }

  //if (pos[0] <= radi - 20)
  //{
  //  velo[0] *= -1;
  //  pos[0] = radi - 20;

  //}
  //else if (pos[0] >= 20 - radi)
  //{
  //  velo[0] *= -1;
  //  pos[0] = 20 - radi;
  //}

  //if (pos[2] <= radi - 20)
  //{
  //  velo[2] *= -1;
  //  pos[2] = radi - 20;
  //}
  //else if (pos[2] >= 20 - radi)
  //{
  //  velo[2] *= -1;
  //  pos[2] = 20 - radi;
  //}

  ball.SetVelo(velo);
  ball.SetPos(pos);
}


// Updateä÷êî
void EventManager::Step()
{
  for (int i = 0; i < m_balls.size(); ++i)
  {
    m_balls[i].Step();
    SolveReflection(m_balls[i]);
  }
}



void DrawSphere()
{

}