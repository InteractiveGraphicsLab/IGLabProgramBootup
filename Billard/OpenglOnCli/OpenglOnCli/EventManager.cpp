#include "stdafx.h"

#include "COMMON\tmath.h"
#include <cmath>
#include "MainForm.h"
#include "EventManager.h"

#include <vector>
#include <list>

//todo 
//
// MouseListener ��redraw --> timer�ŃC�x���g�N��
// Ball���N���X�� 
// �ړ��E��]�V�~�����[�V���� 
// �V�[����`�� TODO --> �݂��
// 


//�N���X��.h
//�N���X��.cpp

SolidBall::SolidBall( EVec3f pos, EVec3f velo , EVec3f angle, EVec3f anglevelo )
{
  m_radius    = 3    ; //cm
  m_mass      = 170  ; //g
  m_position  = pos  ;
  m_velocity  = velo ;
  m_angle     = angle;
  m_anglevelo = anglevelo;
  m_force_onestep = EVec3f(0,0,0);
  m_torque_onestep = EVec3f(0,0,0);
}

SolidBall::~SolidBall( )
{

}



void SolidBall::Step( float h )
{
  static EVec3f Gravity = EVec3f(0,-100, 0);
  m_force_onestep += m_mass * Gravity;

  //step volocify 
  // F = m x a   -->  a = F/m 
  EVec3f accel = (1/m_mass) * m_force_onestep;
  
  //dv = a x dt,  v = v + dv
  m_velocity = m_velocity + h * accel;

  //dx = v * dt, x = x + dx
  m_position = m_position + h * m_velocity;    

  //step rotation 

  //�p�����x a, �g���N N, �������[�����g�e���\�� I,  
  //���ar�̋��Ȃ� I = diag(r^2,r^2,r^2)
  // a = I^-1 x N  
  EVec3f angleaccel = m_torque_onestep / (m_mass * m_radius * m_radius);

  //�p���x = �p���x + �p�����x x dt
  m_anglevelo = m_anglevelo + angleaccel * h;
  
  //�p�x = �p�x + �p���x x dt
  m_angle = m_angle + m_anglevelo * h;

  
  //���Ƃ̌�������

  if ( m_position[1] - m_radius < FLOOR_Y )
  {
    m_position[1] = m_radius; //��������߂���
    m_velocity[1] *= -0.9f;    //���˕Ԃ点��
  } 

  m_velocity *= 0.99999f;//���� 
}




static EVec3f GetPosOnSphere( const float &phi, const float &theta)
{
  return EVec3f( std::cos(phi) * std::cos(theta), 
                 std::sin(phi),
                -std::cos(phi) * std::sin(theta) );
}



static void DrawSphere(int reso_i, int reso_j, float radius)
{
  EVec3f *norms = new EVec3f[reso_i * reso_j];
  EVec3f *verts = new EVec3f[reso_i * reso_j];

  for ( int i = 0; i < reso_i; ++i ) 
  {
    for ( int j = 0; j < reso_j; ++j )
    {

      norms[j + i * reso_j ] = GetPosOnSphere( M_PI * i / (reso_i - 1.0f) - M_PI / 2.0f,    
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
  // m_angle --> Matrxi3x3 m
  const static float diff[4] = { 1.0f, 0.2f, 0, 0.3f };
  const static float ambi[4] = { 1.0f, 0.2f, 0, 0.3f };
  const static float spec[4] = { 1,1,1,0.3f };
  const static float shin[1] = { 64.0f };
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , ambi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
  glEnable( GL_LIGHTING );
  

  //���ar�̋����e
  glPushMatrix();
  glTranslatef( m_position[0], m_position[1], m_position[2] );

  if (m_angle.norm() > 0.001){
    EMat3f R;
    R = Eigen::AngleAxisf(m_angle.norm(), m_angle.normalized());
    float A[16];

    A[0] = R(0, 0); A[4] = R(0, 1); A[8] = R(0, 2); A[12] = 0;
    A[1] = R(1, 0); A[5] = R(1, 1); A[9] = R(1, 2); A[13] = 0;
    A[2] = R(2, 0); A[6] = R(2, 1); A[10] = R(2, 2); A[14] = 0;
    A[3] = 0; A[7] = 0; A[11] = 0; A[15] = 1;

    glMultMatrixf(A);
  }

  //glMultiMat3d(m.data());
  DrawSphere(  20, 20, m_radius );

  glDisable( GL_LIGHTING );
  glLineWidth(2.0);
  glBegin(GL_LINES );
  glColor3d(1,0,0); glVertex3d(0,0,0); glVertex3d(5,0,0);
  glColor3d(0,1,0); glVertex3d(0,0,0); glVertex3d(0,5,0);
  glColor3d(0,0,1); glVertex3d(0,0,0); glVertex3d(0,0,5);
  glEnd();
  
  glPopMatrix();
}


//.h
class MyVec3
{
private:
  float m_data[3];
  int *m_test;
     
public :
  MyVec3(float x = 0, float y = 0, float z = 0) 
  {
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
    m_test = new int[5];
  }

  ~MyVec3()
  {
    delete[] m_test;
  }

  MyVec3(const MyVec3 &src)
  { 
    this->m_data[0] = src.m_data[0];
    this->m_data[1] = src.m_data[1];
    this->m_data[2] = src.m_data[2];
    m_counter++;
  }
  
  MyVec3 operator+(const MyVec3 v)
  {
    MyVec3 p;
    p.m_data[0] = this->m_data[0] + v.m_data[0];
    p.m_data[1] = this->m_data[1] + v.m_data[1];
    p.m_data[2] = this->m_data[2] + v.m_data[2];
    return p;
  }
  
  void Trace();
  void Trace(int a)
  {
    printf("aaaakkkk");
  }

  static int m_counter;
  static void StaticFunc(){
    //m_publ = 0;
    m_counter = 0;
  }

  static void SetCountZero(){
    m_counter = 0;
  }

  void func();
  

};

// class�Ƃ�
// �t�B�[���h�ϐ�(private/public)�C
// �t�B�[���h�֐�(private/public)
// static �ϐ� static �֐�
// constructor

int MyVec3::m_counter = 0;




//.cpp
void MyVec3::Trace(){
  printf("aaaa %f %f %f\n", m_data[0], m_data[1], m_data[2]);
}


void MyVec3::func()
{

}


void func( int a, int &b, int *c )
{
  //�l�n���C�Q�Ɠn���C�|�C���^�n��
  a = 10;
  b = 10;
  if( c != 0) *c = 10;
}







EventManager::EventManager()
{
  std::cout << "EventManager constructor\n";
  //
  //MyVec3 v1(1,2,3), v2(3,4,5);
  //v1.Trace();
  //v2.Trace();
  //MyVec3 v3 = v1 + v2; //�I�y���[�^�I�[�o�[���[�h
  //v3.Trace();
  //v3.Trace(1);
  //
  ////v1.m_priv = 10; ����
  // 
  //v1.StaticFunc();
  //MyVec3::StaticFunc();

  ////MyVec3 p(1,2,3);
  ////MyVec3 q(1,2,3);
  ////auto a = p + q;
  ////p.Trace();
  ////q.Trace();
  ////a.Trace();
  //
  ////�X�R�[�v
  //{
  //  float a = 10;
  //  MyVec3 *aaa = new MyVec3();
 
  //  delete aaa;
  //}
  //
  //std::vector<int> array_int;
  //array_int.push_back(1);
  //array_int.push_back(2);
  //array_int.push_back(3);
  //array_int.push_back(0);
  //array_int.push_back(13);
  //array_int.push_back(11);
  //array_int.push_back(10);
  //
  //std::list<int> list_int;
  //list_int.push_back(1);
  //list_int.push_back(10);
  //list_int.push_back(122);
  //list_int.push_back(133);
  //list_int.push_back(144);
  //list_int.push_back(155);
  //list_int.push_back(1);
  //
  //array_int[4];
  //list_int.pop_front();

  //int a1 =1, a2 = 1, a3 = 1;
  //func(a1,a2,&a3);
  ////a1 == 1, a2 == 10, a3 == 10 
  //  
  m_btn_right = m_btn_left = m_btn_middle = false;
}










static EVec3f cursor_p, cursor_d;


void EventManager::BtnDownLeft  (int x, int y, OglForCLI *ogl)
{
  m_btn_left = true;
  ogl->BtnDown_Trans( EVec2i(x,y) );
  
  ogl->GetCursorRay( EVec2i(x,y), cursor_p, cursor_d);

  EVec3f v( rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX );
  EVec3f a( rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX );
  m_balls.push_back( SolidBall( EVec3f(0,30,0), 10 * v, EVec3f(0,0,0), a ) );
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

  ogl->MouseMove( EVec2i(x,y) );
}








void EventManager::DrawScene()
{
  //�����Ƀ����_�����O���[�`��������
  glDisable( GL_LIGHTING );
  glLineWidth(2.0);
  glBegin(GL_LINES );
  glColor3d(1,0,0); glVertex3d(0,0,0); glVertex3d(10,0,0);
  glColor3d(0,1,0); glVertex3d(0,0,0); glVertex3d(0,10,0);
  glColor3d(0,0,1); glVertex3d(0,0,0); glVertex3d(0,0,10);
  glEnd();

 
  const static float diff[4] = { 1.0f, 0.2f, 0, 0.3f };
  const static float ambi[4] = { 1.0f, 0.2f, 0, 0.3f };
  const static float spec[4] = { 1,1,1,0.3f };
  const static float shin[1] = { 64.0f };
  const static float diffG[4] = { 0.4f, 1.0f, 0.4f, 0.3f };
  const static float ambiG[4] = { 0.4f, 1.0f, 0.4f, 0.3f };
  
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , diffG);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , ambiG);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
  
  //render floor 
  glEnable( GL_CULL_FACE );
  glDisable(GL_CULL_FACE );
  glBegin(GL_TRIANGLES );
  glNormal3f(0,0,1);
  glVertex3f(-FLOOR_WIDTH, 0, -FLOOR_LENGTH);
  glVertex3f( FLOOR_WIDTH, 0, -FLOOR_LENGTH);
  glVertex3f( FLOOR_WIDTH, 0,  FLOOR_LENGTH);

  glVertex3f(-FLOOR_WIDTH, 0, -FLOOR_LENGTH);
  glVertex3f( FLOOR_WIDTH, 0,  FLOOR_LENGTH);
  glVertex3f(-FLOOR_WIDTH, 0,  FLOOR_LENGTH);
  glEnd();
 
  for ( auto &it : m_balls ) it.Draw();

  //for debug
  glDisable(GL_LIGHTING );
  glLineWidth(10);
  glBegin(GL_LINES );
  EVec3f tmp = cursor_p + 100 * cursor_d;
  glVertex3fv ( cursor_p.data() );
  glVertex3fv ( tmp.data() );
  glEnd();
}




void EventManager::Step()
{
  //todo����
  std::cout << "*";

  for ( auto &it : m_balls ) 
  {
    it.Step( 0.02 );
  }

  //�������� 
  /*
  for ( int i=0; i < (int)m_balls.size(); ++i )
  {
    for ( int j=i+1; j < (int)m_balls.size(); ++j )
    {
      m_balls[i];
      m_balls[j];
    }  
  }
  */
  OpenglOnCli::MainForm_RedrawPanel();

}
