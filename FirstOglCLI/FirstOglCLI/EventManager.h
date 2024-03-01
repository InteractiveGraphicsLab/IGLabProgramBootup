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
  std::vector<std::unique_ptr<PrimitiveObject>> objects;//オブジェクト群
  //ボールを引っ張る時のマウスの位置と方向
  EVec3f rayPos;//rayの発生点
  EVec3f rayDir;//rayの方向
  EVec3f hitPos;//球との衝突位置
  PipeLine pipeLine;//パイプライン
  int graspedBallIdx;//つかんでるボールのindex
  float hitDist;
  EventManager();


public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    //最初しか呼ばれないから
    static EventManager p;
    return &p;
  }
  void Restart();
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
