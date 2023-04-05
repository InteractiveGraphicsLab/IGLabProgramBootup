#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Cuboid.h"
#include "BilliardTable.h"

class Ball
{
private:
  EVec3f m_pos;
  EVec3f m_velo;
  float  m_radi;
  bool   m_is_skip;

  void DrawSphere();

public:
  Ball(float radi, EVec3f& pos, EVec3f& velo);
  Ball(float radi, EVec3f& pos);
  Ball(const Ball& src);

  void Step();

  void Draw();

  EVec3f GetPos();
  EVec3f GetVelo();
  float GetRadi();
  bool GetIsSkip();

  void SetPos(EVec3f pos);
  void SetVelo(EVec3f velo);
  void SetIsSkip(bool is_skip);

};

