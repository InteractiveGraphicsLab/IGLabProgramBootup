#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "Box.h"

class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //マウスボタンの状態
  Ball b1_, b2_, b3_;       //球を３つ生成
  Box  box1_;               //箱を生成
  EventManager();

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
