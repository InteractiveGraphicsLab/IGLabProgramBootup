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
//���̃v���O�����ł�Plane��xy���ʂɐ����ł���
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
  
  //todo]xz���ʈȊO�ɂ��Ή�������
  glVertex3f(-this->m_width, 0, -this->m_length);
  glVertex3f( this->m_width, 0, -this->m_length);
  glVertex3f( this->m_width, 0,  this->m_length);

  glVertex3f(-this->m_width, 0, -this->m_length);
  glVertex3f( this->m_width, 0,  this->m_length);
  glVertex3f(-this->m_width, 0,  this->m_length);
  glEnd();
}

bool RigidPlane::isPickedObject(const EVec3f &rayPos, const EVec3f &rayDir)
{

  return false;
}

void RigidPlane::StepSimulation(const EVec3f &force, const float &dt)
{
  //���̃v���O�����ł�Plane�͕s��
}

void RigidPlane::CollisionDetection(RigidObject *collisionPartner, const float &dt)
{
  switch (collisionPartner->GetObjectType())
  {
  case Plane:
    break;

  case Sphere:
  {
    //�Փ˔���
    bool isCollision = false;
    EVec3f norm_p = this->GetNorm();
    EVec3f pos_p = this->GetPosition(), pos_s = collisionPartner->GetPosition();

    //���ʂɑ΂��Đ��������������ĂȂ������������݂�[todo]
    float distance = abs(norm_p.dot((pos_s - pos_p))) / norm_p.norm();
    if (distance <= collisionPartner->GetRadius()) isCollision = true;

    if (isCollision == false) return;

    //�@�����̑��x�̃x�N�g���̑傫����0.1��菬���������琂���R�͂�������
    float a = abs(norm_p.dot((collisionPartner->GetVelocity()))) / norm_p.norm();
    if (a < 0.1)
    {
      collisionPartner->SetForce(collisionPartner->GetForce() + collisionPartner->GetMass() *EVec3f(0, 9.8, 0));
      //EVec3f v = norm_p.dot((this->GetVelocity())) * norm_p;
      //this->SetForce(this->GetForce() + this->GetMass() * v / dt);
    }
    //�Փˌv�Z�iplane_mass��sphere_mass���\���d���Ƃ���j
    float e = 0.8;
    EVec3f v_s = collisionPartner->GetVelocity(), v_p = this->GetVelocity();

    EVec3f newVelo_plane = v_p;
    EVec3f newVelo_sphere = (1 + e) * v_p - e * v_s;

    this->SetVelocity(newVelo_plane);
    collisionPartner->SetVelocity(newVelo_sphere.norm() < 0.0001 ? EVec3f(0, 0, 0) : newVelo_sphere);
    break;
  }

  default:
    break;
  }
}

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
