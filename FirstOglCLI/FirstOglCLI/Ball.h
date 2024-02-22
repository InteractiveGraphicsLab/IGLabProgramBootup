#pragma once

#include "OglForCLI.h"

class Ball
{
private:
    float  _radi;
    EVec3f _pos, _rot, _velo, _veloangle;
    
public:
    Ball(float radi, EVec3f& pos, EVec3f& rot, EVec3f& velo, EVec3f& veloangle);
    Ball(const Ball& src);
    void Step();
    void Draw();
};