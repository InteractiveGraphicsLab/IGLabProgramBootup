#include "stdafx.h"
#include "RigidObject.h"

using namespace std;

RigidPlane::RigidPlane(const ObjectType &type, const float &width, const float &length, const float &mass, const EVec3f &position, const EVec3f &velocity) :RigidObject(type, mass, position, velocity)
{
  this->m_width = width;
  this->m_length = length;
  this->m_norm = EVec3f(0, 1, 0);
};

//other
//このプログラムではPlaneはxy平面に水平である
void RigidPlane::DrawObject()
{
  const static float diffG[4] = { 0.2f, 0.8f, 0.2f, 0.3f };
  const static float ambiG[4] = { 0.2f, 0.8f, 0.2f, 0.3f };
  const static float spec[4] = { 1,1,1,0.3f };
  const static float shin[1] = { 64.0f };
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffG);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiG);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

  glEnable(GL_CULL_FACE);
  glDisable(GL_CULL_FACE);
  glBegin(GL_TRIANGLES);
  glColor3d(0, 0.5, 0);
  glNormal3f(0,1,0);
  
  //todo]xz平面以外にも対応させる
  glVertex3f(-this->m_width, 0, -this->m_length);
  glVertex3f( this->m_width, 0, -this->m_length);
  glVertex3f( this->m_width, 0,  this->m_length);

  glVertex3f(-this->m_width, 0, -this->m_length);
  glVertex3f( this->m_width, 0,  this->m_length);
  glVertex3f(-this->m_width, 0,  this->m_length);
  glEnd();
}

bool RigidPlane::isPickedObject()
{
  return false;
}

void RigidPlane::StepSimulation(const EVec3f &force)
{
  //このプログラムではPlaneは不動
}

////平面-平面
//void RigidPlane::CollisionDetection(RigidPlane &CollisionPartner)
//{
//  //何もしない
//}
//
////平面-球
//void RigidPlane::CollisionDetection(RigidSphere &CollisionPartner)
//{
//  //衝突判定
//  bool isCollision = false;
//
//  if (isCollision == false) return;
//
//  //衝突計算（plane_massはsphere_massより十分重いとする）
//  float e = 0.5;
//  EVec3f v_s = CollisionPartner.GetVelocity(), v_p = this->GetVelocity();
//
//  EVec3f newVelo_plane = v_p;
//  EVec3f newVelo_sphere = v_s + (1 + e) * (v_p - v_s);
//  this->SetVelocity(newVelo_plane);
//  CollisionPartner.SetVelocity(newVelo_sphere);
//}


//for copy
RigidPlane::RigidPlane(const RigidPlane &src) :RigidObject(src)
{
  this->m_width = src.m_width;
  this->m_length = src.m_length;
}

//get
float RigidPlane::GetWidth()
{
  return this->m_width;
}

float RigidPlane::GetLength()
{
  return this->m_length;
}

EVec3f RigidPlane::GetNorm()
{
  return m_norm;
}
