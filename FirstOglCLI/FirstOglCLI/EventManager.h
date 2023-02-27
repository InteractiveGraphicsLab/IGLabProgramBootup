#pragma once

#pragma unmanaged
#include "OglForCLI.h"

class Ball
{
private:
    EVec3f pos_, velo_;
    float rad_;

public:
    Ball(const double rad, const EVec3f& pos, const EVec3f& velo)
    {
        rad_ = rad;
        pos_ = pos;
        velo_ = velo;
    };

    void Step();
    void DrawSphere();
    EVec3f GetPos();
    EVec3f GetVelo();
    EVec3f SetPos();
};

class EventManager
{
private:
  bool isL_, isR_, isM_; //マウスボタンの状態
  EventManager();

  std::vector<Ball> balls_;

public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    static EventManager p;
    return &p;
  }
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
