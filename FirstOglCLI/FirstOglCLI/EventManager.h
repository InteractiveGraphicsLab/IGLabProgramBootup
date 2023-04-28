#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"

class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //マウスボタンの状態
  std::vector<Ball> m_balls;
  EventManager();

public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    static EventManager p;
    return &p;
  }
  //double vector;

  void DrawScene();
  //void GreenLoad(char FileName);
  //void GreenLoad(const char* filename, vector<glm::vec4>& vertices, vector<glm::vec3>& normals, vector<GLushort>& elements);
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
