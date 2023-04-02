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

  EVec3f GetPos();
  void SetPos(const EVec3f& pos);
  
  EVec3f GetVelo();  
  void SetVelo(const EVec3f& velo);
  
  float GetRadi();  
  void SetVelo(float radi);
  
};

