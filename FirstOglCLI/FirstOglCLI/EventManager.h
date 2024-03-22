#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "Box.h"
#include <vector>

//#define M_PI 3.141592 //�~����
//#define R 2.0f        //���̔��a
//#define DT 0.01f      //step��1�t���[��������̎��Ԃ�����
//#define G -9.8f       //�d�͉����x
//#define E 0.99f        // �����W��

class EventManager
{

private:
    EVec3f rayp_, rayd_;
    bool m_isL, m_isR, m_isM; //�}�E�X�{�^���̏��
    Ball b1_, b2_, b3_;       //�����R����
    Box  box1_;               //���𐶐�
    std::vector<Ball> m_balls; //////////////////////////////////////
    
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


    // isCollision();
    //EVec3d isBBCollision(EVec3d pos1, EVec3d pos2, EVec3d pos3);

    void Step();
};
#pragma managed