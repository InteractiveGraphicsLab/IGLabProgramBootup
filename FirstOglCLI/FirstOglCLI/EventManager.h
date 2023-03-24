#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Ball.h"
#include "Cuboid.h"
#include "BilliardTable.h"

class EventManager
{
private:
    bool m_isL, m_isR, m_isM; //マウスボタンの状態
    EventManager();

    std::vector<Ball> m_balls;
    std::vector<Cuboid> m_cuboids;

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

    void Step();

    static void CollideAndSolve(Ball& b1, Ball& b2);
    static void CollideAndSolve(Ball& b, Cuboid& c);
    static void CollideAndSolve(Ball& b);
};
#pragma managed
