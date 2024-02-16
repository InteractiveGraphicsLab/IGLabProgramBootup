#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "PrimitiveObjects.h"
#include "PipeLine.h"
#include <time.h>

class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //マウスボタンの状態
  std::vector<Ball> balls;//ボール群
  std::vector<std::unique_ptr<PrimitiveObject>> objects;
  PipeLine pipeLine;//パイプライン
  float prevTime;
  EventManager();


public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    //最初しか呼ばれないから
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
  void OnButton1Click();
  void OnButton2Click();
  void OnButton3Click();
  void Step();
};
#pragma managed
