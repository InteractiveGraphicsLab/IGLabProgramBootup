#pragma once

#include "OglForCLI.h"

class Ball
{
private:
    EVec3f _pos, _rot, _velo;
    float _veloangle, _radi;
    
public:
    Ball(EVec3f& pos, EVec3f& rot, EVec3f& velo, float veloangle, float radi);
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