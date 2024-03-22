#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "BilliardsTable.h"
#include "Cuboid.h"
#include "MainForm.h"

class EventManager
{
private:
    bool m_isL, m_isR, m_isM; //マウスボタンの状態
    EventManager();
    void Collision();
    void CollideBall();
    void CollideTable();
    std::vector<Ball> balls_;

public:
    //シングルトンクラス（see デザインパターン, シングルトン）
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
    void MouseForce(int x, int y, OglForCLI* ogl);
    void Step();
    void Init();
};
#pragma managed