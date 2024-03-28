#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include <vector>

class EventManager
{
private:
  bool isL_, isR_, isM_; //マウスボタンの状態
  bool isBtn2_;
  int ball_index_ = -1;
  EVec3f str_p_;
  EVec3f end_p_;
  EVec3f ball_p_;
  std::tuple<EVec3f, EVec3f> ray_;

  EventManager();

  std::vector<Ball> balls_;

public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    static EventManager p;
    return &p;
  }

  void SetMode(const bool& b);

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
