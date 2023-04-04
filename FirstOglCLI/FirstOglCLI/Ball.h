#pragma once

#pragma unmanaged
#include "OglForCLI.h"

// ボールの状態を管理するクラス
class Ball
{
private:
  EVec3f m_pos, m_velo;
  float  m_radi;
  bool m_isPicked;

public:
  Ball(float radi, const EVec3f& pos, const EVec3f& velo);
  Ball(const Ball& src);
  

  void Step();
  void Draw();

  EVec3f GetPos() const;
  void SetPos(const EVec3f& pos);
  
  EVec3f GetVelo() const;  
  void SetVelo(const EVec3f& velo);
  
  float GetRadi() const;  
  void SetRadi(float radi);
  
  float GetD(const EVec3f& ray_pos, const EVec3f& ray_dir, const EVec3f& m_pos, float m_radi) const;

  bool IsPicked(const EVec3f& ray_pos, const EVec3f& ray_dir) ;
  bool IsRealsed(const EVec3f& ray_pos, const EVec3f& ray_dir) ;

  float GetHitDist(const EVec3f& ray_pos,const EVec3f& ray_dir,const EVec3f& m_pos) const;
  void SetIsPicked(bool isPicked);
};

