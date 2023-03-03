#include "pch.h"
#include "EventManager.h"

const int Wall = 10;

Ball::Ball(double radi, EVec3f& pos, EVec3f& velo)
{
    m_pos = pos;
    m_velo = velo;
    m_radi = radi;
}

Ball::Ball(const Ball& src)
{
    m_pos = src.m_pos;
    m_velo = src.m_velo;
    m_radi = src.m_radi;
}

EVec3f Ball::GetPos()
{
    return m_pos;
}

EVec3f Ball::GetVelo()
{
    return m_velo;
}

float Ball::GetRadi()
{
    return m_radi;
}

void Ball::SetPos(EVec3f& pos)
{
    m_pos = pos;
}

void Ball::SetVelo(EVec3f& velo)
{
    m_velo = velo;
}

void Ball::Collision_Ball(Ball& trgt)
{
    float hantei = (trgt.m_pos[0] - m_pos[0]) * (trgt.m_pos[0] - m_pos[0]) + (trgt.m_pos[2] - m_pos[2]) * (trgt.m_pos[2] - m_pos[2]);
    EVec3f tmp_velo;

    if (hantei <= ((m_radi + trgt.m_radi) * (m_radi + trgt.m_radi)))
    {
        //衝突後の速度
        std::cout << "衝突\n";
        tmp_velo = trgt.m_velo;
        trgt.SetVelo(m_velo);
        m_velo = tmp_velo;

        //衝突後の位置調整
        if (m_velo[0] > 0)
            m_pos[0] += (m_radi / 2);
        if (m_velo[0] < 0)
            m_pos[0] -= (m_radi / 2);
        if (m_velo[2] > 0)
            m_pos[2] += (m_radi / 2);
        if (m_velo[2] < 0)
            m_pos[2] -= (m_radi / 2);

        if (trgt.m_velo[0] > 0)
            trgt.m_pos[0] += (trgt.m_radi / 2);
        if (trgt.m_velo[0] < 0)
            trgt.m_pos[0] -= (trgt.m_radi / 2);
        if (m_velo[2] > 0)
            trgt.m_pos[2] += (trgt.m_radi / 2);
        if (m_velo[2] < 0)
            trgt.m_pos[2] -= (trgt.m_radi / 2);
    }
}

void Ball::Step()
{
    float dt = 0.33;
    m_pos += m_velo * dt;
    //m_velo += EVec3f(1.0, 0, 0); //*dt;
    //m_velo *= 0.99;

    //壁の反射
    if (m_pos[0] + m_radi > Wall)
    {
        m_velo[0] *= -0.97;
        m_pos[0] = Wall - 0.00001 - m_radi;
    }
    if (m_pos[0] - m_radi < -Wall)
    {
        m_velo[0] *= -0.97;
        m_pos[0] = -Wall + 0.00001 + m_radi;
    }
    if (m_pos[2] + m_radi > Wall)
    {
        m_velo[2] *= -0.97;
        m_pos[2] = Wall - 0.00001 - m_radi;
    }
    if (m_pos[2] - m_radi < -Wall)
    {
        m_velo[2] *= -0.97;
        m_pos[2] = -Wall + 0.00001 + m_radi;
    }
}

void Ball::Draw()
{
    glTranslated(m_pos[0], m_pos[1], m_pos[2]);
    DrawSphere();
    glTranslated(-m_pos[0], -m_pos[1], -m_pos[2]);
}

void Ball::DrawSphere()
{
    const int    N = 20;
    const double M_PI = 3.141592;

    glEnable(GL_DEPTH_TEST);
    //Material 
    float   shin[1] = { 64 };
    EVec4f  spec(1, 1, 1, 0.5);
    EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);
    EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glBegin(GL_TRIANGLES);
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            double t1 = (x) / (double)N * 2.0 * M_PI;
            double t2 = (x + 1) / (double)N * 2.0 * M_PI;
            double p1 = (y) / (double)N * 1.0 * M_PI - 0.5 * M_PI;
            double p2 = (y + 1) / (double)N * 1.0 * M_PI - 0.5 * M_PI;

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glVertex3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
            glVertex3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
            glVertex3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
            glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glVertex3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));

        }
    }

    glEnd();
}

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  m_balls.push_back(Ball(1, EVec3f(1, 1, 0), EVec3f(4, 0, 2)));
  m_balls.push_back(Ball(1, EVec3f(3, 1, 3), EVec3f(-5, 0, -2)));
  //m_balls.push_back(Ball(1, EVec3f(2, 1, -1), EVec3f(0, 0, 3)));
}

void EventManager::DrawTable() //ビリヤード台作成
{
    glBegin(GL_TRIANGLES);
    for (int y = 0; y < 2; y++) {
        for (int z = -Wall; z < Wall; z++) {
            for (int x = -Wall; x < Wall; x++) {
                //地面作成
                glColor3d(0, 1, 0);
                glNormal3d(x, 0, z);
                glVertex3d(x, 0, z);
                glNormal3d(x + 1, 0, z);
                glVertex3d(x + 1, 0, z);
                glNormal3d(x, 0, z + 1);
                glVertex3d(x, 0, z + 1);

                glColor3d(0, 0.8, 0);
                glNormal3d(x + 1, 0, z + 1);
                glVertex3d(x + 1, 0, z + 1);
                glNormal3d(x + 1, 0, z);
                glVertex3d(x + 1, 0, z);
                glNormal3d(x, 0, z + 1);
                glVertex3d(x, 0, z + 1);

                //左壁作成
                glColor3d(0, 1, 0);
                glNormal3d(-Wall, y, z);
                glVertex3d(-Wall, y, z);
                glNormal3d(-Wall, y, z + 1);
                glVertex3d(-Wall, y, z + 1);
                glNormal3d(-Wall, y + 1, z);
                glVertex3d(-Wall, y + 1, z);

                glColor3d(0, 0.8, 0);
                glNormal3d(-Wall, y + 1, z + 1);
                glVertex3d(-Wall, y + 1, z + 1);
                glNormal3d(-Wall, y, z + 1);
                glNormal3d(-Wall, y, z + 1);
                glVertex3d(-Wall, y, z + 1);
                glNormal3d(-Wall, y + 1, z);
                glVertex3d(-Wall, y + 1, z);

                //右壁作成
                glColor3d(0, 1, 0);
                glNormal3d(Wall, y, z);
                glVertex3d(Wall, y, z);
                glNormal3d(Wall, y, z + 1);
                glVertex3d(Wall, y, z + 1);
                glNormal3d(Wall, y + 1, z);
                glVertex3d(Wall, y + 1, z);

                glColor3d(0, 0.8, 0);
                glNormal3d(Wall, y + 1, z + 1);
                glVertex3d(Wall, y + 1, z + 1);
                glNormal3d(Wall, y, z + 1);
                glVertex3d(Wall, y, z + 1);
                glNormal3d(Wall, y + 1, z);
                glVertex3d(Wall, y + 1, z);

                //手前壁作成
                glColor3d(0, 1, 0);
                glNormal3d(x, y, Wall);
                glVertex3d(x, y, Wall);
                glNormal3d(x + 1, y, Wall);
                glVertex3d(x + 1, y, Wall);
                glNormal3d(x, y + 1, Wall);
                glVertex3d(x, y + 1, Wall);

                glColor3d(0, 0.8, 0);
                glNormal3d(x + 1, y + 1, Wall);
                glVertex3d(x + 1, y + 1, Wall);
                glNormal3d(x + 1, y, Wall);
                glVertex3d(x + 1, y, Wall);
                glNormal3d(x, y + 1, Wall);
                glVertex3d(x, y + 1, Wall);

                //奥壁作成
                glColor3d(0, 1, 0);
                glNormal3d(x, y, -Wall);
                glVertex3d(x, y, -Wall);
                glNormal3d(x + 1, y, -Wall);
                glVertex3d(x + 1, y, -Wall);
                glNormal3d(x, y + 1, -Wall);
                glVertex3d(x, y + 1, -Wall);

                glColor3d(0, 0.8, 0);
                glNormal3d(x + 1, y + 1, -Wall);
                glVertex3d(x + 1, y + 1, -Wall);
                glNormal3d(x + 1, y, -Wall);
                glVertex3d(x + 1, y, -Wall);
                glNormal3d(x, y + 1, -Wall);
                glVertex3d(x, y + 1, -Wall);
            }
        }
    }

    glEnd();
}

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

  //ビリヤード台作成
  DrawTable();

  //球を進める
  for (int i = 0; i < m_balls.size(); ++i) {
      m_balls[i].Step();
  }

  //球同士の衝突判定
  for (int i = 0; i < m_balls.size(); ++i) {
      for (int j = 0; j < m_balls.size(); ++j) {
          if (i == j) continue;
          m_balls[i].Collision_Ball(m_balls[j]);
      }
  }

  //球の描画
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

}
