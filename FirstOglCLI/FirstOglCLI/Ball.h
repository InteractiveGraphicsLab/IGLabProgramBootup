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
  EVec3f GetPos()
  {
    return m_pos;
  } 
  
  void SetPos(const EVec3f& pos)
  {
    m_pos = pos;
  } 
  
  EVec3f GetVelo()
  {
    return m_velo;
  }
  
  void SetVelo(const EVec3f& velo)
  {
    m_velo = velo;
  }
  
  float GetRadi()
  {
    return m_radi;
  } 
  
  void SetVelo(float radi)
  {
    m_radi = radi;
  }
  
};

