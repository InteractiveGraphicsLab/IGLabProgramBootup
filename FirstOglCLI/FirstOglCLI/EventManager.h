#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "BilliardTable.h"

class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //�}�E�X�{�^���̏��
  std::vector<Ball> balls_;
  EventManager();

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

  bool CheckCollisionWithBalls(const Ball& ball) const;
  void DoCollisionWithBalls(const Ball& ball);
  int* GetCollisionList() const;

  bool CheckCollisionWithBilliardTable(const Ball& ball) const;
  void DoCollisionWithBilliardTable(const Ball& ball);

  //�S�Ă̏Փˏ������̈ړ����Ō�ɍX�V����֐�(Todo) UpdatePos(��)
};