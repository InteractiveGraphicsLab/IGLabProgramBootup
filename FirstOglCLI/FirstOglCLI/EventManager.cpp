#include "pch.h"
#include "EventManager.h"

// Unityの起動 メンバ変数はコンストラクタで初期化
EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  m_hit_pos = EVec3f(0,-1,0);
  m_release_pos = EVec3f(0, -1, 0);

  m_balls.push_back(Ball(1, EVec3f(-5.0, 0, 0), EVec3f(0, 0, 0)));
  m_balls.push_back(Ball(1, EVec3f(5, 0, 0), EVec3f(0, 0, 0)));
  m_balls.push_back(Ball(1, EVec3f(0, 10, 0), EVec3f(0, 0, 0)));
  m_balls.push_back(Ball(1, EVec3f(3, 10, 0), EVec3f(0, 0, 0)));

  m_table = new BilliardTable(20, 20);
  m_ball_index = -1;
  m_hit_dist = -1;

  m_ray_pos = EVec3f::Zero();
  m_ray_dir = EVec3f::Zero();
}




// 描画処理
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

  glColor3f(0.1f, 0.4f, 0.2f);
  m_table->Draw();

  for (int i = 0; i < m_balls.size(); ++i)
    m_balls[i].Draw();

  if (m_ball_index != -1)
  {
    glDisable(GL_LIGHTING);//電気を消す
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3fv(m_hit_pos.data());
    
    EVec3f drag_pos = m_ray_pos;
    glVertex3fv(drag_pos.data());
    glEnd();
  }
}

//x,yはパネルのx,y座標
void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  std::cout << "LButton 押された\n\n";
  m_isL = true;

  //右辺のEVec3f()はコンストラクタ
  EVec3f ray_pos = EVec3f(0, 0, 0);
  EVec3f ray_dir = EVec3f(0, 0, 0);

  ogl->GetCursorRay(x, y, ray_pos, ray_dir);

  //for文を回すことによってどのボールがクリックされたのかを探している
  for (int i = 0; i < m_balls.size(); ++i)
  {
    if (m_balls[i].IsPicked(ray_pos,ray_dir))
    {
      std::cout<<"当たった"<<std::endl;
      m_hit_pos = ray_pos + m_balls[i].GetHitDist(ray_pos,ray_dir,m_balls[i].GetPos()) * ray_dir;
      m_ball_index = i;
      m_hit_dist = m_balls[i].GetHitDist(ray_pos, ray_dir, m_balls[i].GetPos());
      m_balls[i].SetVelo(EVec3f(0, 0, 0));
      std::cout << m_hit_pos << std::endl;
    }
  }


  //ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLの視点を回転させる準備
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
  std::cout << "\nLButton 離された\n\n";

  m_isL = false;
  //ogl->BtnUp();



  EVec3f ray_pos = EVec3f(0, 0, 0);
  EVec3f ray_dir = EVec3f(0, 0, 0);

  ogl->GetCursorRay(x, y, ray_pos, ray_dir);

    if (m_ball_index != -1)
    {
      std::cout << "離した" << std::endl;
      m_release_pos = ray_pos + m_hit_dist * ray_dir;
      m_addforce_vec = m_hit_pos - m_release_pos;
      std::cout << m_release_pos << std::endl;
      m_balls[m_ball_index].SetVelo(CalcAddforceVelo());
      m_balls[m_ball_index].SetIsPicked(false);
      m_ball_index = -1;
    }
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
  if (!m_isL && !m_isR && !m_isM)
  {
    return;
  }
  else if (m_isL && !m_isR && !m_isM)
  {  
    //std::cout << "LButton ドラッグ中\n";
    ogl->GetCursorRay(x, y, m_ray_pos, m_ray_dir);
    return;
  }

  //画面の平行移動とかの処理
  ogl->MouseMove(EVec2i(x, y));
}

//めり込んでたらボールの位置を戻す処理
void EventManager::SolveReflection(Ball &ball)
{
  EVec3f pos = ball.GetPos();
  EVec3f velo = ball.GetVelo();
  float radi = ball.GetRadi();

  //反射
  if (pos[1] < radi)
  {
    velo[1] *= -0.5f;
    pos[1] = radi;
  }

  float x_wall = m_table->GetWidth() - radi;
  float z_wall = m_table->GetDepth() - radi;

  if (fabs(pos[0]) - x_wall > 0)
  {
    velo[0] *= -1.0f;
    pos[0] = (pos[0] > 0) ? x_wall : -x_wall;
  }

  if (fabs(pos[2]) - z_wall > 0)
  {
    velo[2] *= -1.0f;
    pos[2] = (pos[2] > 0) ? z_wall : -z_wall;
  }

  ball.SetVelo(velo);
  ball.SetPos(pos);
}


static bool IsCollision(const Ball& ball_i,const Ball& ball_j)
{
  EVec3f pos_i = ball_i.GetPos();
  EVec3f pos_j = ball_j.GetPos();
  float radi_i = ball_i.GetRadi();
  float radi_j = ball_j.GetRadi();

  float dist = (pos_i - pos_j).norm();

  if (dist <= radi_i + radi_j)
  {
    return true;
  }
  else
  {
    return false;
  }
}



EVec3f EventManager::CalcAddforceVelo() const
{
  EVec3f addforce_velo = EVec3f(0,0,0);
  addforce_velo = m_addforce_vec;
  return addforce_velo;
}

// Update関数
void EventManager::Step()
{
  for (int i = 0; i < m_balls.size(); ++i)
  {
    m_balls[i].Step();
    SolveReflection(m_balls[i]);
  }

  for (int i = 0; i < m_balls.size() - 1; ++i)
  {
    for (int j = i+1; j < m_balls.size(); ++j)
    {
      if (IsCollision(m_balls[i], m_balls[j]))
      {
        EVec3f pos_i  = m_balls[i].GetPos();
        EVec3f pos_j  = m_balls[j].GetPos();
        EVec3f velo_i = m_balls[i].GetVelo();
        EVec3f velo_j = m_balls[j].GetVelo();
        float radi_i  = m_balls[i].GetRadi();
        float radi_j  = m_balls[j].GetRadi();

        m_balls[j].SetVelo(velo_i);
        m_balls[i].SetVelo(velo_j);
        m_balls[i].SetPos((pos_i + pos_j) / 2 + radi_i * (pos_i - pos_j).normalized());
        m_balls[j].SetPos((pos_j + pos_i) / 2 + radi_j * (pos_j - pos_i).normalized());
      }
    }
  }
}





