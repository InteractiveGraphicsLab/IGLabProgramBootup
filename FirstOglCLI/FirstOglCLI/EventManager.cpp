#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  //InitializeBalls();

  m_balls.push_back(Ball(0.5f, EVec3f(0, 0.5f, 0)));
  m_balls.push_back(Ball(0.5f, EVec3f(2, 0.5f, 0), EVec3f(-9, 0, 0)));

}

void EventManager::InitializeBalls()
{
  const float radi = 1.0f;

  m_balls.push_back(Ball(radi, EVec3f(0, 0, 0)));

  const int row = 5; // 5
  const EVec3f first_pos = EVec3f(0, radi, -10.0);

  for (int i = 0; i < row; ++i) // ビリヤードボール生成
  {
    if (i % 2 == 0) // 偶数のみ
    {
      EVec3f pos = EVec3f(0, 0, -i * sqrtf(3) * radi) + first_pos;
      m_balls.push_back(Ball(radi, pos));
    }

    for (int j = 0; j < i; j += 2) // z軸対称
    {
      EVec3f pos = EVec3f((i - j) * radi, 0, -i * sqrtf(3) * radi) + first_pos;
      m_balls.push_back(Ball(radi, EVec3f(pos[0], pos[1], pos[2])));
      m_balls.push_back(Ball(radi, EVec3f(-pos[0], pos[1], pos[2])));
    }
  }
}

void EventManager::InitializeBalls1()
{
  const float radi = 0.5f;

  EVec3f bt_pos = BilliardTable::GetInst()->GetPos();
  float bt_width = BilliardTable::GetInst()->GetWidth();
  float bt_height = BilliardTable::GetInst()->GetHeight();
  float bt_depth = BilliardTable::GetInst()->GetDepth();

  for (int i = 0; i < 1000; ++i)
  {
    const float div = 100.0f;
    float posx = (std::rand() % (int)(2 * div * (bt_width - radi) + 1) - div * (bt_width - radi)) / div + bt_pos[0];
    float posy = (std::rand() % (int)(2 * div * (bt_height - radi) + 1) - div * (bt_height - radi)) / div + bt_pos[1];
    float posz = (std::rand() % (int)(2 * div * (bt_depth - radi) + 1) - div * (bt_depth - radi)) / div + bt_pos[2];

    const float velox_max = 10.0;
    const float veloy_max = 0.0;
    const float veloz_max = 10.0;
    float velox = (std::rand() % (int)(div * ((velox_max + 1) - velox_max / 2))) / div;
    float veloy = (std::rand() % (int)(div * ((veloy_max + 1) - veloy_max / 2))) / div;
    float veloz = (std::rand() % (int)(div * ((veloz_max + 1) - veloz_max / 2))) / div;

    m_balls.push_back(Ball(
      radi,
      EVec3f(posx, posy, posz),
      EVec3f(velox, veloy, veloz)));
  }
}

void EventManager::DrawScene()
{
  //glLineWidth(2.0f);
  //glDisable(GL_LIGHTING);//電気を消す

  /*
  //OpenGLで3本の直線を描く
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();*/

  BilliardTable::GetInst()->Draw();
  for (int i = 0; i < m_balls.size(); ++i)
  {
    m_balls[i].Draw();
  }
  //for (int i = 0; i < m_cuboids.size(); ++i)
  //{
  //    m_cuboids[i].Draw();
  //}

  if (m_isL && m_idx != -1)
  {
    glLineWidth(2.0f);
    glDisable(GL_LIGHTING);

    EVec3f b_pos = m_balls[m_idx].GetPos();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(b_pos[0], b_pos[1], b_pos[2]);
    glVertex3f(m_MousePos[0], m_MousePos[1], m_MousePos[2]);
    glEnd();
  }

}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;

  EVec3f ray_pos, ray_dir;
  ogl->GetCursorRay(x, y, ray_pos, ray_dir);

  m_idx = PickBall(ray_pos, ray_dir);
  m_MousePos = m_balls[m_idx].GetPos();

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
  m_isL = false;
  if (m_idx != -1)
  {
    EVec3f ray_pos, ray_dir;

    ogl->GetCursorRay(x, y, ray_pos, ray_dir);

    EVec3f b_pos = m_balls[m_idx].GetPos();
    //EVec3f mouse_pos = CalcMousePos(b_pos, ray_pos, ray_dir);
    EVec3f mouse_pos = CalcMousePos1(ray_pos, ray_dir, m_balls[m_idx]);
    EVec3f nor_vec = b_pos - mouse_pos;
    EVec3f b_velo = m_balls[m_idx].GetVelo();
    b_velo += nor_vec / 2;
    m_balls[m_idx].SetVelo(b_velo);
  }

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
  else if (m_isL && m_idx != -1)
  {
    EVec3f ray_pos, ray_dir;

    ogl->GetCursorRay(x, y, ray_pos, ray_dir);

    //EVec3f b_pos = m_balls[m_idx].GetPos();
    //m_MousePos = CalcMousePos(b_pos, ray_pos, ray_dir);
    m_MousePos = CalcMousePos1(ray_pos, ray_dir, m_balls[m_idx]);
  }
  ogl->MouseMove(EVec2i(x, y));
}

void EventManager::Step()
{
  int i, j;
  // PreCollideAndSolve
  for (i = 0; i < m_balls.size(); ++i)
  {

    // 球とビリヤード台
    CollideAndSolve(m_balls[i]);

    // 球と球
    int idx = -1;
    float t = 0.33f;
    for (j = i + 1; j < m_balls.size(); ++j)
    {
      //CollideAndSolve(m_balls[i], m_balls[j]);
      if (Collide(m_balls[i], m_balls[j], t))
      {
        idx = j;
      }
    }
    if (idx != -1)
    {
      Solve(m_balls[i], m_balls[idx]);
    }
  }


  // Step
  for (i = 0; i < m_balls.size(); ++i)
  {
    m_balls[i].Step();
  }
  for (int i = 0; i < m_cuboids.size(); ++i)
  {
    m_cuboids[i].Step();
  }


  // CollideAndSolve
  for (i = 0; i < m_balls.size(); ++i)
  {
    // 球とビリヤード台
    CollideAndSolve(m_balls[i]);

    // 球と球
    for (j = i + 1; j < m_balls.size(); ++j)
    {
      CollideAndSolve(m_balls[i], m_balls[j]);
    }

    // 球と直方体
    for (j = 0; j < m_cuboids.size(); ++j)
    {
      CollideAndSolve(m_balls[i], m_cuboids[j]);
    }


    //m_balls[i].HitCuboid(m_cuboids);
    //m_balls[i].HitBall(m_balls);
  }

}

void EventManager::Reset()
{
  m_balls.erase(m_balls.begin(), m_balls.end());
  InitializeBalls();
}

void EventManager::Add()
{
  m_balls.push_back(Ball(0.5f, EVec3f(0, 10.0f, 0)));
}

void EventManager::CollideAndSolve(Ball& b)
{
  EVec3f bt_pos = BilliardTable::GetInst()->GetPos();
  float bt_width = BilliardTable::GetInst()->GetWidth();
  float bt_height = BilliardTable::GetInst()->GetHeight();
  float bt_depth = BilliardTable::GetInst()->GetDepth();

  EVec3f b_pos = b.GetPos();
  float b_radi = b.GetRadi();

  if (fabsf(b_pos[0] - bt_pos[0]) > bt_width - b_radi)
  {
    EVec3f b_velo = b.GetVelo();
    float bt_bounce = BilliardTable::GetInst()->GetBounce();
    b_pos[0] = bt_pos[0] + (bt_width - b_radi) * (b_pos[0] - bt_pos[0]) / fabsf(b_pos[0] - bt_pos[0]);
    b_velo[0] *= -bt_bounce;
    b.SetVelo(b_velo);
    b.SetPos(b_pos);
  }
  if (fabsf(b_pos[1] - bt_pos[1]) > bt_height - b_radi)
  {
    EVec3f b_velo = b.GetVelo();
    float bt_bounce = BilliardTable::GetInst()->GetBounce();
    b_pos[1] = bt_pos[1] + (bt_height - b_radi) * (b_pos[1] - bt_pos[1]) / fabsf(b_pos[1] - bt_pos[1]);
    b_velo[1] *= -bt_bounce;
    b.SetVelo(b_velo);
    b.SetPos(b_pos);
  }
  if (fabsf(b_pos[2] - bt_pos[2]) > bt_depth - b_radi)
  {
    EVec3f b_velo = b.GetVelo();
    float bt_bounce = BilliardTable::GetInst()->GetBounce();
    b_pos[2] = bt_pos[2] + (bt_depth - b_radi) * (b_pos[2] - bt_pos[2]) / fabsf(b_pos[2] - bt_pos[2]);
    b_velo[2] *= -bt_bounce;
    b.SetVelo(b_velo);
    b.SetPos(b_pos);
  }
}

bool EventManager::Collide(Ball& b1, Ball& b2, float& t)
{
  float bounce = 1.0f; // 球の反発係数(未定)

  EVec3f pos1 = b1.GetPos();
  EVec3f pos2 = b2.GetPos();
  float radi1 = b1.GetRadi();
  float radi2 = b2.GetRadi();
  EVec3f velo1 = b1.GetVelo();
  EVec3f velo2 = b2.GetVelo();

  EVec3f q = pos1 - pos2;
  EVec3f u = velo1 - velo2;

  float discri = powf(q.dot(u), 2.0f) - u.squaredNorm() * (q.squaredNorm() - powf(radi1 + radi2, 2.0f));

  // 衝突判定
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

void EventManager::Solve(Ball& b1, Ball& b2)
{
  float bounce = 1.0f; // 球の反発係数(未定)

  EVec3f pos1 = b1.GetPos();
  EVec3f pos2 = b2.GetPos();
  float radi1 = b1.GetRadi();
  float radi2 = b2.GetRadi();
  EVec3f velo1 = b1.GetVelo();
  EVec3f velo2 = b2.GetVelo();

  EVec3f q = pos1 - pos2;
  EVec3f u = velo1 - velo2;

  float discri = powf(q.dot(u), 2.0f) - u.squaredNorm() * (q.squaredNorm() - powf(radi1 + radi2, 2.0f));
  float C = (-q.dot(u) - sqrtf(discri)) / u.squaredNorm();

  EVec3f colli_pos1 = pos1 + C * velo1;
  EVec3f colli_pos2 = pos2 + C * velo2;

  EVec3f diff = colli_pos2 - colli_pos1;
  EVec3f dir = diff.normalized(); // p1p2ベクトルの正規化

  // ベクトルの分割
  EVec3f v1 = dir * velo1.dot(dir);
  EVec3f v2 = velo1 - v1;
  EVec3f v3 = dir * velo2.dot(dir);
  EVec3f v4 = velo2 - v3;

  EVec3f temp = v1;
  v1 = v3;
  v3 = temp;

  //pos1 += -dir * (radi1 + radi2 - diff.norm()) / 2;
  //pos2 += dir * (radi1 + radi2 - diff.norm()) / 2;

  velo1 = v1 + v2;
  velo2 = v3 + v4;

  colli_pos1 += velo1 * (0.33f - C);
  colli_pos2 += velo2 * (0.33f - C);

  b1.SetPos(colli_pos1);
  b2.SetPos(colli_pos2);

  b1.SetVelo(velo1);
  b2.SetVelo(velo2);

  b1.SetIsSkip(true);
  b2.SetIsSkip(true);
}

void EventManager::CollideAndSolve(Ball& b1, Ball& b2) // ball to ball
{
  float bounce = 1.0f; // 球の反発係数(未定)

  EVec3f pos1 = b1.GetPos();
  EVec3f pos2 = b2.GetPos();
  float radi1 = b1.GetRadi();
  float radi2 = b2.GetRadi();
  EVec3f velo1 = b1.GetVelo();
  EVec3f velo2 = b2.GetVelo();

  EVec3f q = pos1 - pos2;

  if (q.norm() <= radi1 + radi2) // 衝突判定
  { // 衝突処理

    EVec3f diff = pos2 - pos1;
    EVec3f dir = diff.normalized(); // p1p2ベクトルの正規化

    // ベクトルの分割
    EVec3f v1 = dir * velo1.dot(dir);
    EVec3f v2 = velo1 - v1;
    EVec3f v3 = dir * velo2.dot(dir);
    EVec3f v4 = velo2 - v3;

    EVec3f temp = v1;
    v1 = v3;
    v3 = temp;

    pos1 += -dir * (radi1 + radi2 - diff.norm()) / 2;
    pos2 += dir * (radi1 + radi2 - diff.norm()) / 2;

    velo1 = v1 + v2;
    velo2 = v3 + v4;

    b1.SetPos(pos1);
    b2.SetPos(pos2);

    b1.SetVelo(velo1);
    b2.SetVelo(velo2);
  }
}
//
// //void EventManager::CollideAndSolve(Ball& b1, Ball& b2) // ball to ball
//{
//  float bounce = 1.0f; // 球の反発係数(未定)
//
//  EVec3f pos1 = b1.GetPos();
//  EVec3f pos2 = b2.GetPos();
//  float radi1 = b1.GetRadi();
//  float radi2 = b2.GetRadi();
//  EVec3f velo1 = b1.GetVelo();
//  EVec3f velo2 = b2.GetVelo();
//
//
//
//  EVec3f q = pos1 - pos2;
//  EVec3f u = velo1 - velo2;
//
//  float discri = powf(q.dot(u), 2.0f) - u.squaredNorm() * (q.squaredNorm() - powf(radi1 + radi2, 2.0f));
//
//  if (discri >= 0.0f && u.norm() > 0.0f) // 衝突判定
//  { // 衝突処理
//    float C = (-q.dot(u) - sqrtf(discri)) / u.squaredNorm();
//    if (C >= 0 && C <= 0.33f)
//    {
//
//      //std::cout << C << std::endl;
//
//      EVec3f colli_pos1 = pos1 + C * velo1;
//      EVec3f colli_pos2 = pos2 + C * velo2;
//
//
//      EVec3f diff = colli_pos2 - colli_pos1;
//      EVec3f dir = diff.normalized(); // p1p2ベクトルの正規化
//
//      // ベクトルの分割
//      EVec3f v1 = dir * velo1.dot(dir);
//      EVec3f v2 = velo1 - v1;
//      EVec3f v3 = dir * velo2.dot(dir);
//      EVec3f v4 = velo2 - v3;
//
//      EVec3f temp = v1;
//      v1 = v3;
//      v3 = temp;
//
//      //pos1 += -dir * (radi1 + radi2 - diff.norm()) / 2;
//      //pos2 += dir * (radi1 + radi2 - diff.norm()) / 2;
//
//      velo1 = v1 + v2;
//      std::cout << "v1(" << velo1[0] << ", " << velo1[1] << ", " << velo1[2] << ")" << std::endl;
//      velo2 = v3 + v4;
//      std::cout << "v2(" << velo2[0] << ", " << velo2[1] << ", " << velo2[2] << ")\n" << std::endl;
//
//      b1.SetPos(colli_pos1);
//      b2.SetPos(colli_pos2);
//
//      b1.SetVelo(velo1);
//      b2.SetVelo(velo2);
//    }
//  }
//}

void EventManager::CollideAndSolve(Ball& b, Cuboid& c) // ball to cuboid
{
  EVec3f b_pos = b.GetPos();
  float b_radi = b.GetRadi();
  EVec3f c_pos = c.GetPos();
  float c_width = c.GetWidth();
  float c_height = c.GetHeight();
  float c_depth = c.GetDepth();

  if (fabsf(b_pos[0] - c_pos[0]) < b_radi + c_width && fabsf(b_pos[1] - c_pos[1]) < c_height && fabsf(b_pos[2] - c_pos[2]) < c_depth)
  {
    EVec3f b_velo = b.GetVelo();
    float bounce = c.GetBounce();
    b_velo[0] *= -bounce;
    b_pos[0] = c_pos[0] + (b_radi + c_width) * (b_pos[0] - c_pos[0]) / fabsf(b_pos[0] - c_pos[0]);
    b.SetVelo(b_velo);
    b.SetPos(b_pos);
  }
  if (fabsf(b_pos[0] - c_pos[0]) < c_width && fabsf(b_pos[1] - c_pos[1]) < b_radi + c_height && fabsf(b_pos[2] - c_pos[2]) < c_depth)
  {
    EVec3f b_velo = b.GetVelo();
    float bounce = c.GetBounce();
    b_velo[1] *= -bounce;
    b_pos[1] = c_pos[1] + (b_radi + c_height) * (b_pos[1] - c_pos[1]) / fabsf(b_pos[1] - c_pos[1]);
    b.SetVelo(b_velo);
    b.SetPos(b_pos);
  }
  if (fabsf(b_pos[0] - c_pos[0]) < c_width && fabsf(b_pos[1] - c_pos[1]) < c_height && fabsf(b_pos[2] - c_pos[2]) < b_radi + c_depth)
  {
    EVec3f b_velo = b.GetVelo();
    float bounce = c.GetBounce();
    b_velo[2] *= -bounce;
    b_pos[2] = c_pos[2] + (b_radi + c_depth) * (b_pos[2] - c_pos[2]) / fabsf(b_pos[2] - c_pos[2]);
    b.SetVelo(b_velo);
    b.SetPos(b_pos);
  }
}

int EventManager::PickBall(EVec3f RayPos, EVec3f RayDir)
{
  float dis = 10000.0;
  int pick_idx = -1;
  for (int i = 0; i < m_balls.size(); ++i)
  {
    EVec3f b_pos = m_balls[i].GetPos();
    float b_radi = m_balls[i].GetRadi();
    float d = powf(RayDir.dot(RayPos - b_pos), 2) - (powf((RayPos - b_pos).norm(), 2) - powf(b_radi, 2));
    if (d > 0 && (RayPos - b_pos).norm() < dis) // 接触
    {
      pick_idx = i;
      dis = (RayPos - b_pos).norm();
    }
  }
  if (pick_idx != -1)
  {
    m_balls[pick_idx].SetVelo(EVec3f(0, 0, 0));
  }
  return pick_idx;
}

EVec3f EventManager::CalcMousePos(const EVec3f& TargetPos, const EVec3f& RayPos, const EVec3f& RayDir)
{ // RayDirの大きさを返す(RayDirと法線ベクトルの内積 = 0)
  float slope = (TargetPos - RayPos).dot(RayDir);
  return slope * RayDir + RayPos;
}

EVec3f EventManager::CalcMousePos1(const EVec3f& RayPos, const EVec3f& RayDir, const Ball& b)
{ // RayDirの大きさを返す(y座標 = 0.5)
  float bottom = BilliardTable::GetInst()->GetPos()[1] - BilliardTable::GetInst()->GetHeight();
  float radi = b.GetRadi();
  float slope = (bottom + radi - RayPos[1]) / RayDir[1];
  return slope * RayDir + RayPos;
}