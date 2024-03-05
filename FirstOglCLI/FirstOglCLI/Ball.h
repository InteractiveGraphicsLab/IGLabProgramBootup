#pragma once

#include "OglForCLI.h"

class Ball
{
private:
    EVec3f pos_;
    EVec3f rot_;
    EVec3f vel_;
    EVec3f rad_vel_;

public:
    Ball(const EVec3f& p)
    {
        pos_ = p;               //‹…‚ÌˆÊ’u
        rot_ << 1, 0, 0;;       //‰ñ“]Ž²
        vel_ << 0.5, 0, 0;;     //‘¬“x
        rad_vel_ << 0, 0, 0;;   //Šp‘¬“x
    };

    void Draw();
    void DrawSphere();
    void Step(float t);
    /*EVec3f GetPos();
    EVec3f GetVelo();
    EVec3f SetPos();*/
};