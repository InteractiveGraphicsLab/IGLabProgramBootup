#pragma once

#pragma unmanaged
#include "OglForCLI.h"

class BilliardTable
{
private:
    EVec3f m_pos;
    float m_width, m_height, m_depth;
    float m_bounce;

    BilliardTable();

    void DrawBilliardTable();

public:
    static BilliardTable* GetInst() {
        static BilliardTable p;
        return &p;
    }

    void Draw();

    EVec3f GetPos();
    float GetWidth();
    float GetHeight();
    float GetDepth();
    float GetBounce();
};
