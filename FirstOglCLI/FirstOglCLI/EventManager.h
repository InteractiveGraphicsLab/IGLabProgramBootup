#pragma once

#pragma unmanaged
#include "Ball.h"
#include "BilliardTable.h"


// 力学作用を計算するクラス　かつ
// Unityとマウス処理に関するクラス
class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //マウスボタンの状態
  EVec3f m_hit_pos;
  EVec3f m_release_pos;
  EVec3f m_addforce_vec;
  int m_ball_index;
  float m_hit_dist;
  EventManager();
  std::vector<Ball> m_balls;
  BilliardTable *m_table;
  void SolveReflection(Ball& ball);

  EVec3f m_ray_pos;
  EVec3f m_ray_dir;

public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    static EventManager p;
    return &p;
  }

  void DrawScene();  // 描画関数（シーン描画）

  void LBtnDown(int x, int y, OglForCLI* ogl);
  void MBtnDown(int x, int y, OglForCLI* ogl);
  void RBtnDown(int x, int y, OglForCLI* ogl);

  void LBtnUp(int x, int y, OglForCLI* ogl);
  void MBtnUp(int x, int y, OglForCLI* ogl);
  void RBtnUp(int x, int y, OglForCLI* ogl);

  void MouseMove(int x, int y, OglForCLI* ogl);

  //メンバ関数はメンバ変数にアクセスできるから引数は１つだけ
  EVec3f CalcAddforceVelo() const;

  void Step(); // Update関数

};
#pragma managed
