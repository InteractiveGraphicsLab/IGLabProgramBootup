#pragma once

#pragma unmanaged
#include "OglForCLI.h"

class Cuboid
{
private:
    EVec3f m_pos, m_velo;
    float m_width, m_height, m_depth, m_bounce;
    void DrawCuboid();

public:
    Cuboid(EVec3f& pos, float width, float height, float depth, EVec3f& velo);
    Cuboid(const Cuboid& src);
    void Step();
    void Draw();
    EVec3f GetPos();
    float GetWidth();
    float GetHeight();
    float GetDepth();
    float GetBounce();
};
