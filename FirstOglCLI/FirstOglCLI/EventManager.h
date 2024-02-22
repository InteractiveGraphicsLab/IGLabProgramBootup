#pragma once

#pragma unmanaged
#include "OglForCLI.h"

class Ball
{
private:    
    EVec3f pos_;
    EVec3f rot_;
    EVec3f vel_;
    EVec3f rad_vel_;

public:
    Ball(const EVec3f &p)
    {
        pos_ = p;
        rot_ << 0, 0, 0;;
        vel_ << 0, 0, 0;;
        rad_vel_ << 0, 0, 0;; 
    };

    void Step(float t);
    void DrawSphere();
    /*EVec3f GetPos();
    EVec3f GetVelo();
    EVec3f SetPos();*/
};

class EventManager
{
private:
  bool isL_, isR_, isM_; //�}�E�X�{�^���̏��
  EventManager();

  std::vector<Ball> balls_;

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
