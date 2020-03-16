#include "stdafx.h"
#include "CollisionCalculator.h"


CollisionCalculator::CollisionCalculator(const float &dt)
{
  m_dt = dt;
}

void CollisionCalculator::CollisionDetection(RigidObject &obj1, RigidObject &obj2)
{
  switch (obj1.GetObjectType())
  {
  case RigidObject::Plane:
    if      (obj2.GetObjectType() == RigidObject::Plane)  SimulateCollision_PlanePlane(obj1, obj2);
    else if (obj2.GetObjectType() == RigidObject::Sphere) SimulateCollision_SpherePlane(obj2, obj1);
    break;

  case RigidObject::Sphere:
    if      (obj2.GetObjectType() == RigidObject::Plane)  SimulateCollision_SpherePlane(obj1, obj2);
    else if (obj2.GetObjectType() == RigidObject::Sphere) SimulateCollision_SphereSphere(obj1, obj2);
    break;
  }
}

void CollisionCalculator::SimulateCollision_SphereSphere(RigidObject &sphere1, RigidObject &sphere2)
{
      //�Փ˔���
    bool isCollision = false;
    const float rad_src1 = sphere1.GetRadius(), rad_src2 = sphere2.GetRadius();
    const EVec3f pos_src1 = sphere1.GetPosition(), pos_src2 = sphere2.GetPosition();

    float distance = (pos_src1 - pos_src2).norm();
    if (distance <= rad_src1 + rad_src2) isCollision = true;

    if (isCollision == false) return;

    //�Փˌv�Z
    const float e = 0.8;
    const EVec3f velo_src1 = sphere1.GetVelocity(), velo_src2 = sphere2.GetVelocity();
    const float mass_src1 = sphere1.GetMass(), mass_src2 = sphere2.GetMass();

    EVec3f newVelo_src1 = (velo_src1 * (mass_src1 - e * mass_src2) + mass_src2 * velo_src2 * (1 + e)) / (mass_src1 + mass_src2);
    EVec3f newVelo_src2 = ((1 + e) * velo_src1 * mass_src1 + velo_src2 * (mass_src2 - e * mass_src1)) / (mass_src1 + mass_src2);
    sphere1.SetVelocity(newVelo_src1);
    sphere2.SetVelocity(newVelo_src2);
}

void CollisionCalculator::SimulateCollision_SpherePlane(RigidObject &sphere, RigidObject &plane)
{
  EVec3f norm_plane = plane.GetNorm();
  float width_plane = plane.GetWidth(), length_plane = plane.GetLength(); 
  vector<EVec3f> verts_plane = plane.GetVertex();
  EVec3f pos_plane = plane.GetPosition(), pos_sphere = sphere.GetPosition();
  
  //�@�������̋��������a�ȓ���
  EVec3f vec_normDir = norm_plane.dot((pos_sphere - pos_plane))*norm_plane;
  float distance = vec_normDir.norm();
  if (abs(distance) > sphere.GetRadius()) return;
  
  //���ʂ���͂ݏo���Ă��邩
  EVec3f vec_width  = (verts_plane[1] - verts_plane[0]).normalized(), vec_length = (verts_plane[3] - verts_plane[0]).normalized();
  EVec3f vec_plane = (pos_sphere - pos_plane) - vec_normDir;
  float dis_widthDir = vec_width.dot(vec_plane) / vec_width.norm();
  float dis_lengthDir = (vec_plane - vec_width.dot(vec_plane)*vec_width).norm();
  if (dis_widthDir > width_plane/2 + sphere.GetRadius() || dis_lengthDir > length_plane/2 + sphere.GetRadius()) return; 
  
  //�@�����̑��x�̃x�N�g���̑傫����0.1��菬���������琂���R�͂�������
  float a = abs(norm_plane.dot((sphere.GetVelocity()))) / norm_plane .norm();
  if (a < 0.1)
  {
    sphere.SetForce(sphere.GetForce() + sphere.GetMass() *EVec3f(0, 9.8, 0));
    //EVec3f v = norm_p.dot((this->GetVelocity())) * norm_p;
    //this->SetForce(this->GetForce() + this->GetMass() * v / dt);
  }
  //�Փˌv�Z�iplane_mass��sphere_mass���\���d���Ƃ���j
  float e = 0.8;
  EVec3f v_s = sphere.GetVelocity(), v_p = plane.GetVelocity();

  EVec3f newVelo_plane = v_p;
  EVec3f newVelo_sphere = (1 + e) * v_p - e * v_s;

  plane.SetVelocity(newVelo_plane);
  sphere.SetVelocity(newVelo_sphere.norm() < 0.0001 ? EVec3f(0, 0, 0) : newVelo_sphere);
}

void CollisionCalculator::SimulateCollision_PlanePlane(RigidObject &plane1, RigidObject &plane2)
{
  //�������Ȃ�
}

