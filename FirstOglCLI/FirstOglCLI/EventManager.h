#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "BilliardTable.h"

class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //マウスボタンの状態
  std::vector<Ball> balls_;
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

  bool CheckCollisionWithBalls(const Ball& ball) const;
  void DoCollisionWithBalls(const Ball& ball);
  int* GetCollisionList() const;

  bool CheckCollisionWithBilliardTable(const Ball& ball) const;
  void DoCollisionWithBilliardTable(const Ball& ball);

  //全ての衝突処理内の移動を最後に更新する関数(Todo) UpdatePos(仮)
};