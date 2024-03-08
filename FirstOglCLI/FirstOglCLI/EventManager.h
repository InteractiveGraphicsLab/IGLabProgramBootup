#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include <vector>

class EventManager
{
private:
  bool isL_, isR_, isM_; //�}�E�X�{�^���̏��
  bool isHit_;
  EVec2i str_pos_;       //���N���b�N���������W
  EVec2i end_pos_;       //���N���b�N����������W
  EVec2i cur_pos_;       //�}�E�X�̌��݂̈ʒu
  EventManager();

  std::vector<Ball> balls_;

public:
  //�V���O���g���N���X�isee �f�U�C���p�^�[��, �V���O���g���j
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
