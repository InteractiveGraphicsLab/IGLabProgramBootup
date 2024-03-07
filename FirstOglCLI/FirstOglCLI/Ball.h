#pragma once

#include "OglForCLI.h"
#include "math.h"

class Ball
{
private:
    EVec3f pos_;        //���̈ʒu
    EVec3f rot_;        //��]��
    EVec3f vel_;        //���x
    float  ang_;        //��]�p�x
    float  rad_;        //���a(cm)
    float  rad_vel_;    //�p���x
    float  wgh_;        //�d��(g)

public:
    Ball(const EVec3f& p)
    {
        pos_ = p;               
        rot_ << 0, 0, -1;;
        vel_ << 0.5f, 0, 0;;
        ang_ = 0;
        rad_ = 0.5f;
        wgh_ = 170;

        float sum = pow(vel_[0], 2) + pow(vel_[1], 2) + pow(vel_[2], 2);
        rad_vel_ = sqrt(sum) / rad_;;
    };

    void Draw();
    void DrawSphere();
    void Step(float t);
    void SetVelo(const EVec2i& e);
    EVec3f GetPos();
    EVec3f GetVelo();
    EVec3f SetPos();
};