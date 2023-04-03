#pragma once

#pragma unmanaged
#include "Ball.h"
#include "BilliardTable.h"


// �͊w��p���v�Z����N���X�@����
// Unity�ƃ}�E�X�����Ɋւ���N���X
class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //�}�E�X�{�^���̏��
  EVec3f m_hit_pos;
  EventManager();
  std::vector<Ball> m_balls;
  BilliardTable *m_table;
  void SolveReflection(Ball& ball);

public:
  //�V���O���g���N���X�isee �f�U�C���p�^�[��, �V���O���g���j
  static EventManager* GetInst() {
    static EventManager p;
    return &p;
  }

  void DrawScene();  // �`��֐��i�V�[���`��j

  void LBtnDown(int x, int y, OglForCLI* ogl);
  void MBtnDown(int x, int y, OglForCLI* ogl);
  void RBtnDown(int x, int y, OglForCLI* ogl);

  void LBtnUp(int x, int y, OglForCLI* ogl);
  void MBtnUp(int x, int y, OglForCLI* ogl);
  void RBtnUp(int x, int y, OglForCLI* ogl);

  void MouseMove(int x, int y, OglForCLI* ogl);

  void Step(); // Update�֐�
};
#pragma managed
