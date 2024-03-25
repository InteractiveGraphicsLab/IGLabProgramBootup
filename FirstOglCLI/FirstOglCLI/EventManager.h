#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "Box.h"
#include <vector>


class EventManager
{

private:
    EVec3f rayp_, rayd_;
    bool m_isL, m_isR, m_isM; //�}�E�X�{�^���̏��
    Box  box1_;               //���𐶐�
    std::vector<Ball> m_balls; //�{�[���𐶐�
    
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


    bool isCollision(const int& n1, const int& n2);
    void UpdateVelocity(const int& n1, const int& n2);

    void Step();
};
#pragma managed