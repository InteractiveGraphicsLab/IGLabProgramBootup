#pragma once

#pragma unmanaged

#include <vector>
#include "COMMON/tmath.h"

class RigidObject
{
protected:
  float m_mass;
  EVec3f m_pos, m_velo;
  EVec3f m_rot, m_rotVelo;

public:
  RigidObject();
  
  //get
  float  GetMass();
  EVec3f GetPosition();
  EVec3f GetVelocity();
  EVec3f GetRotation();
  EVec3f GetRotVelo();

  //set
  EVec3f SetPosition();
  EVec3f SetVelocity();
  EVec3f SetRotation();
  EVec3f SetRotVelo();
};

#pragma managed