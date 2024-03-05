#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "Box.h"

#define N 20.0f       //���������ۂ̕�����
#define M_PI 3.141592 //�~����
#define R 2.0f        //���̔��a
#define DT 0.01f      //step��1�t���[��������̎��Ԃ�����
#define G -9.8f       //�d�͉����x
#define E 0.99f        // �����W��

class EventManager
{
private:
  bool m_isL, m_isR, m_isM; //�}�E�X�{�^���̏��
  Ball b1_, b2_, b3_;       //�����R����
  Box  box1_;               //���𐶐�
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

  EVec3d isCollision1();  //���P�ƕǂ̏Փ˔���
  EVec3d isCollision2();  //���Q�ƕ�
  EVec3d isCollision3();  //���R�ƕ�

  void Step();
};
#pragma managed
