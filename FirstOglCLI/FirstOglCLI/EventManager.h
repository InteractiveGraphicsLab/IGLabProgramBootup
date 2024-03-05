#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "Box.h"

#define N 20.0f       //球を書く際の分割数
#define M_PI 3.141592 //円周率
#define R 2.0f        //球の半径
#define DT 0.01f      //stepの1フレームあたりの時間を仮定
#define G -9.8f       //重力加速度
#define E 0.99f        // 反発係数

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

  EVec3d isCollision1();  //球１と壁の衝突判定
  EVec3d isCollision2();  //球２と壁
  EVec3d isCollision3();  //球３と壁

  void Step();
};
#pragma managed
