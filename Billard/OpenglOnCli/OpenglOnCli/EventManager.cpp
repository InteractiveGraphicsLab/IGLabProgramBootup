#include "stdafx.h"

#include "COMMON\tmath.h"
#include <cmath>
#include "MainForm.h"
#include "EventManager.h"

#include <vector>
#include <list>

//todo 
//
// MouseListener にredraw --> timerでイベント起動
// Ballをクラス化 
// 移動・回転シミュレーション 
// シーンを描く TODO --> みんな
// 


SolidBall::SolidBall( EVec3f pos , EVec3f vel)
{
  m_radius    = 0.03f * 2; //m
  m_mass      = 0.17f;     //kg
  m_position  = pos  ;
  m_velocity  = vel;
  m_angle     = EVec3f(0.0f, 0.0f, 0.0f);
  m_anglevelo = EVec3f(0.0f, 0.0f, 0.0f);
}

SolidBall::~SolidBall( )
{
}


void SolidBall::Step( float h )
{
  static EVec3f Gravity = EVec3f(0,0,-10);
  //static EVec3f Gravity = EVec3f(0, 0, 0);

  // a = G 
  // dv/dt = a  --> dv = a dt
  // dx/dt = v  --> dx = v dt
  m_velocity += h * Gravity   ;
  m_position += h * m_velocity; 
  
}

bool SolidBall::isGrasped(const EVec3f& cursorPos, const EVec3f& cursorDir)
{
  EVec3f dir = cursorDir.normalized();
  EVec3f l = cursorPos - GetPos() + dir.dot(GetPos() - cursorPos) * dir;
  
  if (l.norm() < GetRadius())
  {
    return true;
  }
  return false;
}

bool SolidBall::isCollisionTable()
{
  EVec3f widthVec  = EVec3f(1, 0, 0);
  EVec3f lengthVec = EVec3f(0, 1, 0);
  EVec3f wallHVec  = EVec3f(0, 0, 1);
  float distanceX = std::abs(widthVec.dot(GetPos()));
  float distanceY = std::abs(lengthVec.dot(GetPos()));
  float distanceZ = std::abs(wallHVec.dot(GetPos()));
  //std::cout << distanceX << "\n";
  //std::cout << distanceY << "\n";
  //std::cout << distanceZ << "\n";

  if ( distanceX <= FLOOR_WIDTH + GetRadius()
    && distanceY <= FLOOR_LENGTH + GetRadius()
    && distanceZ <= m_radius)
  {
    //std::cout << "collision table\n";
    return true;
  }
  return false;
}

bool SolidBall::isCollisionBall(SolidBall& ball)
{
  const EVec3f disPos = m_position - ball.GetPos();
  const float disLen = disPos.norm();

  if (disLen <= m_radius + ball.GetRadius()) {
    return true;
  }
  return false;
}


static EVec3f GetPosOnBall( const float &phi, const float &theta)
{
  return EVec3f( std::cos(phi) * std::cos(theta), 
                 std::sin(phi),
                -std::cos(phi) * std::sin(theta) );
}


static void DrawBall(int reso_i, int reso_j, float radius)
{
  EVec3f *norms = new EVec3f[reso_i * reso_j];
  EVec3f *verts = new EVec3f[reso_i * reso_j];

  for ( int i = 0; i < reso_i; ++i ) 
  {
    for ( int j = 0; j < reso_j; ++j )
    {

      norms[j + i * reso_j ] = GetPosOnBall( M_PI * i / (reso_i - 1.0f) - M_PI / 2.0f,    
                                           2 * M_PI * j / (reso_j - 1.0f) );
      verts[j + i * reso_j] = radius * norms[ j + i * reso_j ];
    }
  }

  glBegin(GL_TRIANGLES);
  for ( int i = 0; i < reso_i-1; ++i ) 
  {
    for ( int j = 0; j < reso_j-1; ++j )
    { 
      int idx0 = reso_j*  i   + j, idx1 = reso_j*  i  + j+1;
      int idx2 = reso_j*(i+1) + j, idx3 = reso_j*(i+1)+ j+1;
      glColor3f(0.5, 0.5, 0.5);
      glNormal3fv( norms[ idx0 ].data() ); glVertex3fv( verts[ idx0 ].data() );
      glNormal3fv( norms[ idx2 ].data() ); glVertex3fv( verts[ idx2 ].data() );
      glNormal3fv( norms[ idx3 ].data() ); glVertex3fv( verts[ idx3 ].data() );

      glNormal3fv( norms[ idx0 ].data() ); glVertex3fv( verts[ idx0 ].data() );
      glNormal3fv( norms[ idx3 ].data() ); glVertex3fv( verts[ idx3 ].data() );
      glNormal3fv( norms[ idx1 ].data() ); glVertex3fv( verts[ idx1 ].data() );
    }
  }
  glEnd();
     

  delete[] verts;
  delete[] norms;
}


void SolidBall::Draw( )
{
  //todo 
  // m_angle --> Matrxi3x3 m

  //半径rの球を各
  glPushMatrix();
  glTranslatef( m_position[0], m_position[1], m_position[2] );
  //glMultiMat3d(m.data());
  DrawBall(  20, 20, m_radius );
  glPopMatrix();
}




EventManager::EventManager()
{
  std::cout << "EventManager constructor\n";
    
  m_btn_right = m_btn_left = m_btn_middle = false;
  m_GraspedBall = -1;

  m_balls.push_back(SolidBall(EVec3f(0,  0.1, 5), EVec3f(0, 0, 0)));
  m_balls.push_back(SolidBall(EVec3f(0, -0.1, 5), EVec3f(0, 0, 0)));
  //m_balls.push_back(SolidBall(EVec3f(0, 0, 0), EVec3f(0, 1, 0)));


  //for (float i = -1; i < 2; ++i)
  //{
  //  for (float j = -1; j < 2; ++j)
  //  {
  //    m_balls.push_back(SolidBall(EVec3f(i / 10, j / 10, 1), EVec3f(0, 0, 0)));
  //  }
  //}

}


static EVec3f cursor_p, cursor_d;

void EventManager::BtnDownLeft  (int x, int y, OglForCLI *ogl)
{
  m_btn_left = true;
  
  ogl->GetCursorRay( EVec2i(x,y), cursor_p, cursor_d);
  for (int i = 0; i < m_balls.size(); ++i)
  {
    if (m_balls[i].isGrasped(cursor_p, cursor_d) == true)
    {
      m_GraspedBall = i;
    }
  }
  
  if (m_GraspedBall == -1)
  {
    ogl->BtnDown_Trans(EVec2i(x, y));
  }

} 


void EventManager::BtnDownMiddle(int x, int y, OglForCLI *ogl)
{
  m_btn_middle = true;
  ogl->BtnDown_Zoom( EVec2i(x,y) );
}


void EventManager::BtnDownRight (int x, int y, OglForCLI *ogl)
{
  m_btn_right = true;
  ogl->BtnDown_Rot( EVec2i(x,y) );
}


void EventManager::BtnUpLeft  (int x, int y, OglForCLI *ogl)
{
  m_btn_left = false;
  ogl->BtnUp();

  if (m_GraspedBall != -1)
  {
    ogl->GetCursorRay( EVec2i(x,y), cursor_p, cursor_d);
    float depth = (cursor_p - m_balls[m_GraspedBall].GetPos()).norm();
    EVec3f target = cursor_p + cursor_d * depth;
    m_shotF = - (target - m_balls[m_GraspedBall].GetPos());
    m_balls[m_GraspedBall].SetVel(m_balls[m_GraspedBall].GetVel() + m_shotF / m_balls[m_GraspedBall].GetMass());
  }
  m_GraspedBall = -1;
}


void EventManager::BtnUpMiddle(int x, int y, OglForCLI *ogl)
{
  m_btn_middle = false;
  ogl->BtnUp();
}


void EventManager::BtnUpRight (int x, int y, OglForCLI *ogl)
{
  m_btn_right = false;
  ogl->BtnUp();
}


void EventManager::MouseMove    (int x, int y, OglForCLI *ogl)
{
  if ( !m_btn_right && !m_btn_middle && !m_btn_left) return;

  if (m_GraspedBall == -1)
  {
    ogl->MouseMove(EVec2i(x, y));
  }
  else
  {
    ogl->GetCursorRay(EVec2i(x, y), cursor_p, cursor_d);
  }

}



void EventManager::DrawBilliardTable()
{
  //render billboard floor 
  glEnable(GL_CULL_FACE);
  glDisable(GL_CULL_FACE);
  glBegin(GL_TRIANGLES);
  glNormal3f(0, 0, 1);
  glColor3f(0.3, 0.6, 0.3);

  glVertex3f(-FLOOR_WIDTH, -FLOOR_LENGTH, 0);
  glVertex3f(FLOOR_WIDTH, -FLOOR_LENGTH, 0);
  glVertex3f(FLOOR_WIDTH, FLOOR_LENGTH, 0);

  glVertex3f(-FLOOR_WIDTH, -FLOOR_LENGTH, 0);
  glVertex3f(FLOOR_WIDTH, FLOOR_LENGTH, 0);
  glVertex3f(-FLOOR_WIDTH, FLOOR_LENGTH, 0);
  //glEnd();

  ////render billboard wall
  glColor3f(0.8, 0.8, 0.8);

  //下
  glVertex3f(-FLOOR_WIDTH, -FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(FLOOR_WIDTH, -FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(FLOOR_WIDTH, -FLOOR_LENGTH, 0);

  glVertex3f(-FLOOR_WIDTH, -FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(FLOOR_WIDTH, -FLOOR_LENGTH, 0);
  glVertex3f(-FLOOR_WIDTH, -FLOOR_LENGTH, 0);

  //上
  glVertex3f(FLOOR_WIDTH, FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(-FLOOR_WIDTH, FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(-FLOOR_WIDTH, FLOOR_LENGTH, 0);

  glVertex3f(FLOOR_WIDTH, FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(-FLOOR_WIDTH, FLOOR_LENGTH, 0);
  glVertex3f(FLOOR_WIDTH, FLOOR_LENGTH, 0);

  //右
  glVertex3f(FLOOR_WIDTH, -FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(FLOOR_WIDTH, FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(FLOOR_WIDTH, FLOOR_LENGTH, 0);

  glVertex3f(FLOOR_WIDTH, -FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(FLOOR_WIDTH, FLOOR_LENGTH, 0);
  glVertex3f(FLOOR_WIDTH, -FLOOR_LENGTH, 0);

  //左
  glVertex3f(-FLOOR_WIDTH, FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(-FLOOR_WIDTH, -FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(-FLOOR_WIDTH, -FLOOR_LENGTH, 0);

  glVertex3f(-FLOOR_WIDTH, FLOOR_LENGTH, WALL_HEIGHT);
  glVertex3f(-FLOOR_WIDTH, -FLOOR_LENGTH, 0);
  glVertex3f(-FLOOR_WIDTH, FLOOR_LENGTH, 0);

  glEnd();
}


void EventManager::DrawScene()
{
  const static float diff[4] = { 0.3f, 0.7f, 0.3f, 0.3f };
  const static float ambi[4] = { 0.3f, 0.7f, 0.3f, 0.3f };
  const static float spec[4] = { 0.1f, 0.3f, 0.3f, 0.3f };
  const static float shin[1] = { 20.0f };
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , ambi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

  DrawBilliardTable();
 
  for ( auto &it : m_balls ) it.Draw();

  if (m_GraspedBall != -1)
  {
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3fv(cursor_p.data());
    glVertex3fv(m_balls[m_GraspedBall].GetPos().data());
    glEnd();
  }
}


void EventManager::Step()
{
  //todo処理
  //std::cout << "step";
  const float stepTime = 0.01f;

  for ( auto &it : m_balls ) 
  {
    it.Step( stepTime );
    //移動計算 OK
    //回転も   TODO 井尻
  }

  //交差判定 
  for ( int i = 0; i < (int)m_balls.size(); ++i )
  {
    //floor_ball
    if (m_balls[i].isCollisionTable())
    {
      //std::cout << "collision table\n";
      CollideTable(m_balls[i]);
    }

    for ( int j = i + 1; j < (int)m_balls.size(); ++j )
    {
      if (m_balls[i].isCollisionBall(m_balls[j]))
      {
        CollideBall(m_balls[i], m_balls[j]);
      }
    }  
  }

  OpenglOnCli::MainForm_RedrawPanel();
}



void EventManager::CollideTable(SolidBall& ball)
{
  const float elast = 0.8f;

  EVec3f widthVec = EVec3f(1, 0, 0);
  EVec3f lengthVec = EVec3f(0, 1, 0);
  EVec3f wallHVec = EVec3f(0, 0, 1);
  EVec3f wallHVel = wallHVec * wallHVec.dot(ball.GetVel());
  ball.SetVel(ball.GetVel() - (1.0f + elast) * wallHVel);

  float distanceZ = wallHVec.dot(ball.GetPos());

  ball.SetPos(ball.GetPos() + (ball.GetRadius() - distanceZ) * wallHVec);
}


void EventManager::CollideBall(SolidBall& ball1, SolidBall& ball2)
{
  const float elast = 0.8f; 
  EVec3f pos1 = ball1.GetPos();
  EVec3f pos2 = ball2.GetPos();
  const EVec3f vel1 = ball1.GetVel();
  const EVec3f vel2 = ball2.GetVel();
  const float mass1 = ball1.GetMass();
  const float mass2 = ball2.GetMass();

  ball1.SetVel(((1 + elast) * mass2 * vel2 + (mass1 - elast * mass2) * vel1) / (mass1 + mass2));
  ball2.SetVel(((1 + elast) * mass1 * vel1 + (mass2 - elast * mass1) * vel2) / (mass1 + mass2));

  //めり込み対応       
  const EVec3f distance = pos1 - pos2;
  const EVec3f distanceNormalized = distance.normalized();
  float tmp = 0.01f;
  for (int i = 0; i < 3; ++i) {
    pos1[i] += tmp * distanceNormalized[i];
    pos2[i] -= tmp * distanceNormalized[i];
  }
  ball1.SetPos(pos1);
  ball2.SetPos(pos2);
}
