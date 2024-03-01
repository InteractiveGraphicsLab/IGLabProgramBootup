#pragma once

#include "OglForCLI.h"

class Ball
{
private:
    EVec3f _pos, _rot, _velo, _veloangle;
    float _radi;
    
public:
    Ball(const EVec3f& pos, const EVec3f& rot, const EVec3f& velo, const EVec3f& veloangle, float radi);
    Ball(const Ball& src);
    EVec3f GetPos();
    EVec3f GetVelo();
    float GetRadi();
    void SetPos(const EVec3f& pos);
    void SetVelo(const EVec3f& velo);
    void Step();
    void Draw();
    void DrawSphere();
};