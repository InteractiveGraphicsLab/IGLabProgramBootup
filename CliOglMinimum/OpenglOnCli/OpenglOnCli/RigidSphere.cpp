#include "stdafx.h"
#include "RigidObject.h"

#pragma unmanaged

using namespace std;

RigidSphere::RigidSphere(const ObjectType &type, const float &radius, const float &mass, const EVec3f &position, const EVec3f &velocity) :RigidObject(type, mass, position, velocity)
{
  this->m_radius = radius > 0 ? radius : 1;

  //���_�̌v�Z
  for (int i = 0; i < reso_i; ++i)
  {
    for (int j = 0; j < reso_j; ++j)
    {
      this->norm.push_back(GetPosOnSphere(M_PI * i / (reso_i - 1.0f) - M_PI / 2.0f,
        2 * M_PI * j / (reso_j - 1.0f)));
      this->vert.push_back(m_radius * norm[j + i * reso_j]);
    }
  }
}

//other
EVec3f RigidSphere::GetPosOnSphere(const float &phi, const float &theta)
{
  return EVec3f(cos(phi) * cos(theta),
                sin(phi),
               -cos(phi) * sin(theta));
}

void RigidSphere::DrawObject()
{
  //�`�揈��
  const static float diff[4] = { 1.0f, 0.2f, 0, 0.3f };
  const static float ambi[4] = { 1.0f, 0.2f, 0, 0.3f };
  const static float spec[4] = { 1,1,1,0.3f };
  const static float shin[1] = { 64.0f };

  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

  glPushMatrix();
  glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < reso_i - 1; ++i)
  {
    for (int j = 0; j < reso_j - 1; ++j)
    {
      int idx0 = reso_j * i + j, idx1 = reso_j * i + j + 1;
      int idx2 = reso_j * (i + 1) + j, idx3 = reso_j * (i + 1) + j + 1;
      glNormal3fv(norm[idx0].data()); glVertex3fv(vert[idx0].data());
      glNormal3fv(norm[idx2].data()); glVertex3fv(vert[idx2].data());
      glNormal3fv(norm[idx3].data()); glVertex3fv(vert[idx3].data());

      glNormal3fv(norm[idx0].data()); glVertex3fv(vert[idx0].data());
      glNormal3fv(norm[idx3].data()); glVertex3fv(vert[idx3].data());
      glNormal3fv(norm[idx1].data()); glVertex3fv(vert[idx1].data());
    }
  }
  glEnd();
  glPopMatrix();
}

//void RigidSphere::DrawObject()
//{
//  //���_�̌v�Z
//  const int reso_i = 32, reso_j = 16;
//  EVec3f *norms = new EVec3f[reso_i * reso_j];
//  EVec3f *verts = new EVec3f[reso_i * reso_j];
//  
//  for (int i = 0; i < reso_i; ++i)
//  {
//    for (int j = 0; j < reso_i; ++j)
//    {
//      norms[j + i * reso_j] = GetPosOnSphere(M_PI * i / (reso_i - 1.0f) - M_PI / 2.0f,
//        2 * M_PI * j / (reso_j - 1.0f));
//      verts[j + i * reso_j] = m_radius * norms[j + i * reso_j];
//    }
//  }
//
//  //�`�揈��
//  //const static float diff[4] = { 1.0f, 0.2f, 0, 0.3f };
//  //const static float ambi[4] = { 1.0f, 0.2f, 0, 0.3f };
//  //const static float spec[4] = { 1,1,1,0.3f };
//  //const static float shin[1] = { 64.0f };
//
//  //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
//  //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
//  //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi);
//  //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
//
//
//  glPushMatrix();
//  glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
//  glBegin(GL_TRIANGLES);
//  for (int i = 0; i < reso_i - 1; ++i)
//  {
//    for (int j = 0; j < reso_j - 1; ++j)
//    {
//      int idx0 = reso_j * i + j, idx1 = reso_j * i + j + 1;
//      int idx2 = reso_j * (i + 1) + j, idx3 = reso_j * (i + 1) + j + 1;
//      glNormal3fv(norms[idx0].data()); glVertex3fv(verts[idx0].data());
//      glNormal3fv(norms[idx2].data()); glVertex3fv(verts[idx2].data());
//      glNormal3fv(norms[idx3].data()); glVertex3fv(verts[idx3].data());
//
//      glNormal3fv(norms[idx0].data()); glVertex3fv(verts[idx0].data());
//      glNormal3fv(norms[idx3].data()); glVertex3fv(verts[idx3].data());
//      glNormal3fv(norms[idx1].data()); glVertex3fv(verts[idx1].data());
//    }
//  }
//  glEnd();
//  glPopMatrix();
//
//  delete[] verts;
//  delete[] norms;
//  std::cout << "Drawphere" << std::endl;
//
//}

bool RigidSphere::isPickedObject(const EVec3f &rayPos, const EVec3f &rayDir)
{
  const EVec3f dir = rayDir.normalized();
  const EVec3f a = dir.dot(this->m_pos - rayPos)*dir + rayPos;
  //const EVec3f a = (rayPos - this->m_pos).dot(rayDir.normalized())*rayDir.normalized() + rayPos;
  const float distance = (a - m_pos).norm();
  cout << distance << endl;
  return distance <= m_radius ? true : false;
}

//collision
void RigidSphere::CollisionDetection(RigidObject *collisionPartner, const float &dt)
{
  switch (collisionPartner->GetObjectType())
  {
  case Plane:
  {
    //�Փ˔���
    bool isCollision = false;
    EVec3f norm_p = collisionPartner->GetNorm();
    EVec3f pos_p = collisionPartner->GetPosition(), pos_s = this->GetPosition();

    //���ʂɑ΂��Đ��������������ĂȂ������������݂�[todo]
    float distance = abs(norm_p.dot((pos_s - pos_p))) / norm_p.norm();
    if (distance <= this->GetRadius()) isCollision = true;

    if (isCollision == false) return;

    //�@�����̑��x�̃x�N�g���̑傫����0.1��菬���������琂���R�͂�������
    float a = abs(norm_p.dot((this->GetVelocity()))) / norm_p.norm();
    if (a < 0.1)
    {
      this->SetForce(this->GetForce() + this->GetMass() *EVec3f(0, 9.8, 0));
      //EVec3f v = norm_p.dot((this->GetVelocity())) * norm_p;
      //this->SetForce(this->GetForce() + this->GetMass() * v / dt);
    }
    //�Փˌv�Z�iplane_mass��sphere_mass���\���d���Ƃ���j
    float e = 0.8;
    EVec3f v_s = this->GetVelocity(), v_p = collisionPartner->GetVelocity();

    EVec3f newVelo_plane = v_p;
    EVec3f newVelo_sphere = (1 + e) * v_p - e * v_s;
    collisionPartner->SetVelocity(newVelo_plane);
    this->SetVelocity(newVelo_sphere.norm() < 0.0001 ? EVec3f(0, 0, 0) : newVelo_sphere);

    break;
  }
  case Sphere:
  {
    //�Փ˔���
    bool isCollision = false;
    const float rad_src1 = this->GetRadius(), rad_src2 = collisionPartner->GetRadius();
    const EVec3f pos_src1 = this->GetPosition(), pos_src2 = collisionPartner->GetPosition();

    float distance = (pos_src1 - pos_src2).norm();
    if (distance <= rad_src1 + rad_src2) isCollision = true;

    if (isCollision == false) return;

    //�Փˌv�Z
    const float e = 0.8;
    const EVec3f velo_src1 = this->GetVelocity(), velo_src2 = collisionPartner->GetVelocity();
    const float mass_src1 = this->GetMass(), mass_src2 = collisionPartner->GetMass();

    EVec3f newVelo_src1 = (velo_src1 * (mass_src1 - e * mass_src2) + mass_src2 * velo_src2 * (1 + e)) / (mass_src1 + mass_src2);
    EVec3f newVelo_src2 = ((1 + e) * velo_src1 * mass_src1 + velo_src2 * (mass_src2 - e * mass_src1)) / (mass_src1 + mass_src2);
    this->SetVelocity(newVelo_src1);
    collisionPartner->SetVelocity(newVelo_src2);
    break;
  }
  default:
    break;
  }

}

//for copy
RigidSphere::RigidSphere(const RigidSphere &src) :RigidObject(src)
{
  this->m_radius = src.m_radius;
}

//get
float RigidSphere::GetRadius()
{
  return this->m_radius;
}
#pragma managed
