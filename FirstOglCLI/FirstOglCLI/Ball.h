#pragma once

#include "OglForCLI.h"
#include "Stage.h"
#include "math.h"

class Ball
{
private:
    EVec3f pos_;        //球の位置
    EVec3f rot_;        //回転軸
    EVec3f vel_;        //速度
    float  ang_;        //回転角度
    float  rad_;        //半径(cm)
    float  rad_vel_;    //角速度
    float  wgh_;        //重さ(g)

public:
    Ball(const EVec3f& p, const EVec3f& v)
    {
        pos_ = p;               
        rot_ << 0, 0, -1;;          //速度に対して垂直な軸になるように変更する必要あり
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