#include "pch.h"
#include "Ball.h"


Ball::Ball(float radi, const EVec3f& pos, const EVec3f& velo)
{
  m_radi = radi;
  m_pos = pos;
  m_velo = velo;
  m_isPicked = false;
}

//コピーコンストラクタは現時点ではPushBuck時にしか呼ばれていない
Ball::Ball(const Ball& src)//Copy Constructer
{
  std::cout << "コピーコンストラクタが呼ばれた\n";
  m_pos = src.m_pos;
  m_velo = src.m_velo;
  m_radi = src.m_radi;
  m_isPicked = src.m_isPicked;
}

void Ball::Step() 
{
  float dt = 0.33f;

  // x = x + vdt
  m_pos += m_velo * dt;

  if(!m_isPicked)
  {
    // v = v + gdt
    m_velo += EVec3f(0, -0.98f, 0) * dt;

    // v = v + adt
    m_velo *= 0.99f;
  }
}


static void DrawSphere(float radi)
{
  const int    N = 20;
  const double M_PI = 3.141592;

  glEnable(GL_DEPTH_TEST);
  //Material 
  float   shin[1] = { 64 };

  static int count = 0;
  EVec4f  diff(1.0f, 0.0f, 0.0f, 0.5f);
  EVec4f  ambi(0.5f, 0.0f, 0.0f, 0.5f);
  count++;

  if (count % 2 == 0)
  {
    diff = EVec4f(1.0f, 0.0f, 0.0f, 0.5f);
    ambi = EVec4f(0.5f, 0.0f, 0.0f, 0.5f);
  }
  else
  {
    diff = EVec4f(0.0f, 1.0f, 0.0f, 0.5f);
    ambi = EVec4f(0.0f, 0.5f, 0.0f, 0.5f);
  }




  EVec4f  spec(1, 1, 1, 0.5);
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
      glVertex3d(radi * cos(t1) * cos(p1), radi * sin(p1), radi * sin(t1) * cos(p1));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(radi * cos(t2) * cos(p2), radi * sin(p2), radi * sin(t2) * cos(p2));
      glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
      glVertex3d(radi * cos(t2) * cos(p1), radi * sin(p1), radi * sin(t2) * cos(p1));

      glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
      glVertex3d(radi * cos(t1) * cos(p1), radi * sin(p1), radi * sin(t1) * cos(p1));
      glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
      glVertex3d(radi * cos(t1) * cos(p2), radi * sin(p2), radi * sin(t1) * cos(p2));
      glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
      glVertex3d(radi * cos(t2) * cos(p2), radi * sin(p2), radi * sin(t2) * cos(p2));
    }
  }

  glEnd();
}


void Ball::Draw()
{
  glTranslated(m_pos[0], m_pos[1], m_pos[2]);
  DrawSphere(m_radi);
  glTranslated(-m_pos[0], -m_pos[1], -m_pos[2]);
}

//メンバ関数の後ろのconstは、このメンバ関数内でメンバ変数を変更しませんという意思表示
EVec3f Ball::GetPos() const
{
  return m_pos;
}

void Ball::SetPos(const EVec3f& pos)
{
  m_pos = pos;
}

EVec3f Ball::GetVelo() const
{
  return m_velo;
}

void Ball::SetVelo(const EVec3f& velo)
{
  m_velo = velo;
}

float Ball::GetRadi() const
{
  return m_radi;
}

void Ball::SetRadi(float radi)
{
  m_radi = radi;
}

float Ball::GetD(const EVec3f& ray_pos, const EVec3f& ray_dir, const EVec3f& m_pos, float m_radi) const
{
  float D = powf(ray_dir.dot(ray_pos - m_pos), 2) - powf((ray_pos - m_pos).norm(), 2) + powf(m_radi, 2);
  return D;
}


//ボールがクリックされたかどうかをbool値で返してくれる関数,Xベクトルとtの値が存在するかどうかを判定する関数
bool Ball::IsPicked(const EVec3f& ray_pos, const EVec3f& ray_dir) 
{
  //float D = powf(ray_dir.dot(ray_pos - m_pos), 2) - powf((ray_pos - m_pos).norm(), 2) + powf(m_radi, 2);
  float D = GetD(ray_pos, ray_dir, m_pos, m_radi);

  if (D >= 0)
  {
    m_isPicked = true;
    return true;
  }
  else
  {
    return false;
  }
}

////ボールが１度クリックされた後に離されたかどうかをbool値で返してくれる関数
//bool Ball::IsRealsed(const EVec3f& ray_pos, const EVec3f& ray_dir) 
//{
//  float D = GetD(ray_pos, ray_dir, m_pos, m_radi);
//
//  
//}

//EventManagerがボールに対して聞いているから応えるための関数
float Ball::GetHitDist(const EVec3f& ray_pos, const EVec3f& ray_dir, const EVec3f& m_pos) const
{
  float D = GetD(ray_pos, ray_dir, m_pos, m_radi);
  float hit_dist;

  hit_dist = -((ray_dir.dot(ray_pos - m_pos)) - powf(D, 0.5f));
  return hit_dist;
}

void Ball::SetIsPicked(bool isPicked)
{
  m_isPicked = isPicked;
}
