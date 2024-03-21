#pragma once

#include "OglForCLI.h"
#include "Stage.h"
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
    Ball(const EVec3f& p, const EVec3f& v)
    {
        pos_ = p;               
        rot_ << 0, 0, -1;;          //���x�ɑ΂��Đ����Ȏ��ɂȂ�悤�ɕύX����K�v����
        vel_ = v;;
        ang_ = 0;
        rad_ = 0.5f;
        wgh_ = 170;

        float sum = pow(vel_[0], 2) + pow(vel_[1], 2) + pow(vel_[2], 2);
        rad_vel_ = sqrt(sum) / rad_;;
    };

    Ball(const Ball& b)
    {
        pos_ = b.pos_;
        rot_ = b.rot_;
        vel_ = b.vel_;
        ang_ = b.ang_;
        rad_ = b.rad_;
        rad_vel_ = b.rad_vel_;
        wgh_ = b.wgh_;
    }

    void Draw();
    void DrawSphere();
    void Step(float t);
    void WallCollision();
    void BallCollision(Ball& b);

    void SetVelo(const EVec3f& v);
    EVec3f GetVelo();
    void SetPos();
    EVec3f GetPos();
};