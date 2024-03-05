#pragma once

#include "OglForCLI.h"

class Ball
{
private:
    EVec3f pos_;
    EVec3f rot_;
    EVec3f vel_;
    float  rad_vel_;
    float  ang_;

public:
    Ball(const EVec3f& p)
    {
        pos_ = p;               //‹…‚ÌˆÊ’u
        vel_ << 0.5, 0, 0;;     //‘¬“x
        rot_ << 0, 0, -1;;       //‰ñ“]Ž²
        rad_vel_ = 50;;   //Šp‘¬“x
        ang_ = 0;
    };

    void Draw();
    void DrawSphere();
    void Step(float t);
    /*EVec3f GetPos();
    EVec3f GetVelo();
    EVec3f SetPos();*/
};