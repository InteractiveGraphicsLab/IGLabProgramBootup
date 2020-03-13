#pragma once

#pragma unmanaged

#include <vector>
#include "COMMON/tmath.h"
#include "COMMON/OglForCLI.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

//既定クラス
class RigidObject
{
public:
  enum ObjectType
  {
    Sphere,
    Plane,
  };

protected:
  ObjectType m_type;
  float  m_mass;
  EVec3f m_force;
  EVec3f m_pos, m_velo;
  EVec3f m_rot, m_rotVelo;

public:
  RigidObject(const ObjectType &type, const float &mass, const EVec3f &position, const EVec3f &velocity);

  //other
  virtual void DrawObject() = 0;
  virtual bool isPickedObject() = 0;
  virtual void StepSimulation(const EVec3f &force);

  //for copy
  RigidObject(const RigidObject &src) { Copy(src); };
  void Copy(const RigidObject &src);

  //virtual void CollisionDetection() = 0;
  //virtual void CollisionDetection(RigidPlane &collisionPartner) = 0;
  //virtual void CollisionDetection(RigidSphere &collisionPartner) = 0;


  //get
  float  GetMass();
  EVec3f GetPosition();
  EVec3f GetVelocity();
  EVec3f GetRotation();
  EVec3f GetRotVelo();
  ObjectType GetObjectType();

  //set
  void SetPosition(const EVec3f &position);
  void SetVelocity(const EVec3f &velocity);
  void SetRotation(const EVec3f &rotation);
  void SetRotVelo (const EVec3f &rotVelocity);
};


//球のクラス
class RigidSphere: public RigidObject
{
private:
  std::vector<EVec3f> vert, norm;
  
  float m_radius;

  static const int reso_i = 32, reso_j = 16;
  
public:
  RigidSphere(const ObjectType &type, const float &radius, const float &mass, const EVec3f &position, const EVec3f &velocity);
  
  //other
  EVec3f GetPosOnSphere(const float &phi, const float &theta);
  void DrawObject();
  bool isPickedObject();
  //void CollisionDetection(RigidPlane  &collisionPartner);
  //void CollisionDetection(RigidSphere &collisionPartner);

  //for copy
  RigidSphere(const RigidSphere &src);
  
  //get
  float GetRadius();
};


//Planeのクラス
class RigidPlane :public RigidObject
{
private:
  float m_width, m_length;
  EVec3f m_norm;

public:
  RigidPlane(const ObjectType &type, const float &width, const float &length, const float &mass, const EVec3f &position, const EVec3f &velocity);

  //other
  void DrawObject();
  bool isPickedObject();
  void StepSimulation(const EVec3f &force);
  //void CollisionDetection(RigidSphere &CollisionPartner);
  //void CollisionDetection(RigidPlane &CollisionPartner);

  //copy
  RigidPlane(const RigidPlane &src);

  //get
  float GetWidth();
  float GetLength();
  EVec3f GetNorm();
};
#pragma managed