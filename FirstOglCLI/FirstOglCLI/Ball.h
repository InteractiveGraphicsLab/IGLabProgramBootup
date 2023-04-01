#pragma once

#pragma unmanaged
#include "OglForCLI.h"

class Ball
{
private:
  EVec3f m_pos, m_velo;
  float  m_radi;


public:
  Ball(float radi, const EVec3f& pos, const EVec3f& velo);
  Ball(const Ball& src);

  void Step();
  void Draw();
};

