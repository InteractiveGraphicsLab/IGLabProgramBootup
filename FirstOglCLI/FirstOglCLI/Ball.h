#pragma once

#pragma unmanaged
#include "tmath.h"

class Ball
{
private:
    EVec3f m_pos;
    EVec3f m_velo;

    double m_radi;


public:
    Ball(double radi, EVec3f& pos, EVec3f& velo);

    Ball(const Ball& src);

    void Step();
    void Draw() const;
    void Bound();
};

#pragma managed

