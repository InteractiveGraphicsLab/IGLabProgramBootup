#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"


class EventManager
{
private:
    static int m_num;


  bool m_isL, m_isR, m_isM; //�}�E�X�{�^���̏��
  EventManager();

  std::vector<Ball> m_balls;

public:
  //�V���O���g���N���X�isee �f�U�C���p�^�[��, �V���O���g���j
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
