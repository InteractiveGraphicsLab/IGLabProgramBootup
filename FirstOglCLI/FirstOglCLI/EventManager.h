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
    bool m_isTarget;
    int m_idx;
    EVec3f m_MousePos;
    EventManager();

    std::vector<Ball> m_balls;
    std::vector<Cuboid> m_cuboids;

    void InitializeBalls();
    void InitializeBalls1();

    void CollideAndSolve(Ball& b1, Ball& b2);
    void CollideAndSolve(Ball& b, Cuboid& c);
    void CollideAndSolve(Ball& b);

    int PickBall(EVec3f RayPos, EVec3f RayDir);
    EVec3f CalcMousePos(const EVec3f& TargetPos, const EVec3f& RayPos, const EVec3f& RayDir);
    EVec3f CalcMousePos1(const EVec3f& RayPos, const EVec3f& RayDir);


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

    void Reset();
    void Add();
};
#pragma managed
