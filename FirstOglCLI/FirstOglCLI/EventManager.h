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

  //�����o�֐��̓����o�ϐ��ɃA�N�Z�X�ł��邩������͂P����
  EVec3f CalcAddforceVelo() const;

  void Step(); // Update�֐�

};
#pragma managed
