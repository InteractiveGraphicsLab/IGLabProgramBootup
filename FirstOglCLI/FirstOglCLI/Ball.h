#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "Cuboid.h"

class Ball
{
private:
    EVec3f m_pos, m_velo;
    float  m_radi;

public:
    Ball(float radi, EVec3f& pos, EVec3f& velo);
    Ball(const Ball& src);
    void Step();
    void Draw();
    void DrawSphere();
    /*void HitCuboid(std::vector<Cuboid> cuboids);
    void HitBall(std::vector<Ball> balls);*/
    EVec3f GetPos();
    EVec3f GetVelo();
    float GetRadi();
    void SetPos(EVec3f pos);
    void SetVelo(EVec3f velo);
};
