#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include <vector>

class EventManager
{
private:
  bool isL_, isR_, isM_; //マウスボタンの状態
  bool isHit_;
  EVec2i str_pos_;       //左クリック押した座標
  EVec2i end_pos_;       //左クリックを放した座標
  EVec2i cur_pos_;       //マウスの現在の位置
  EventManager();

  std::vector<Ball> balls_;

public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    static EventManager p;
    return &p;
  }

  //void SetMode(const bool& f);

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
