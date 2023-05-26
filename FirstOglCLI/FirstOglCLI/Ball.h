#pragma once

#pragma unmanaged
#include "tmath.h"
#include "Green.h"
#include "YPolygon.h"

class Ball
{
private:
    EVec3f m_pos;
    EVec3f m_velo;

    float m_radi;


public:
    Ball(float radi, EVec3f& pos, EVec3f& velo);

    Ball(const Ball& src);

    EVec3f GetPos() const { return m_pos; }
    EVec3f GetVelo() const { return m_velo; }
    float GetRadi() const { return m_radi; }

    void SetPos(EVec3f pos) { m_pos = pos; }
    void SetVelo(EVec3f velo) { m_velo = velo; }
    void SetRadi(float radi) { m_radi = radi; }


    void Step();
    void Draw() const;
};

#pragma managed

