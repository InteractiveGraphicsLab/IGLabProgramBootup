#pragma once

#pragma unmanaged
#include "OglForCLI.h"

class Ball
{
private:
    EVec3f m_pos, m_velo;
    float  m_radi;

public:
    Ball(double radi, EVec3f& pos, EVec3f& velo);
    Ball(const Ball& src);
    EVec3f GetPos();
    EVec3f GetVelo();
    float GetRadi();
    void SetPos(EVec3f& pos);
    void SetVelo(EVec3f& velo);
    void Collision_Ball(Ball& trgt);
    void Step();
    void Draw();
    void DrawSphere();

};

class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //マウスボタンの状態
  EventManager();
  std::vector<Ball> m_balls;

public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    static EventManager p;
    return &p;
  }
  void DrawTable(); //ビリヤード台作成
  void DrawScene();
  void LBtnDown(int x, int y, OglForCLI* ogl);
  void MBtnDown(int x, int y, OglForCLI* ogl);
  void RBtnDown(int x, int y, OglForCLI* ogl);
  void LBtnUp(int x, int y, OglForCLI* ogl);
  void MBtnUp(int x, int y, OglForCLI* ogl);
  void RBtnUp(int x, int y, OglForCLI* ogl);
  void MouseMove(int x, int y, OglForCLI* ogl);

  void Step();
};
#pragma managed
