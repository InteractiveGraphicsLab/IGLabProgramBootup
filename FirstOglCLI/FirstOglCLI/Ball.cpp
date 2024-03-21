#include "pch.h"
#include "Ball.h"
#define _USE_MATH_DEFINES
#define e 1.0
#define offset 0.1f
#include <math.h>


void Ball::Draw()
{
    glPushMatrix();
    glTranslated(pos_[0], pos_[1], pos_[2]);
    glRotated(ang_, rot_[0], rot_[1], rot_[2]);
    DrawSphere();
    glPopMatrix();
}

void Ball::DrawSphere()  //‹…‚ð•`‚­‚¾‚¯
{
    //OpenGL‚Å‹…‚ð•`‚­
    const int N = 50.0;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glBegin(GL_TRIANGLES);
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            double t1 = (x) / (double)N * 2.0 * M_PI;
            double t2 = (x + 1) / (double)N * 2.0 * M_PI;
            double p1 = -(y) / (double)N * 1.0 * M_PI - 0.5 * M_PI;
            double p2 = -(y + 1) / (double)N * 1.0 * M_PI - 0.5 * M_PI;

            glNormal3d(rad_ * cos(t1) * cos(p1), rad_ * sin(p1), rad_ * sin(t1) * cos(p1));
            glVertex3d(rad_ * cos(t1) * cos(p1), rad_ * sin(p1), rad_ * sin(t1) * cos(p1));
            glVertex3d(rad_ * cos(t2) * cos(p1), rad_ * sin(p1), rad_ * sin(t2) * cos(p1));
            glVertex3d(rad_ * cos(t2) * cos(p2), rad_ * sin(p2), rad_ * sin(t2) * cos(p2));

            glNormal3d(rad_ * cos(t1) * cos(p1), rad_ * sin(p1), rad_ * sin(t1) * cos(p1));
            glVertex3d(rad_ * cos(t1) * cos(p1), rad_ * sin(p1), rad_ * sin(t1) * cos(p1));
            glVertex3d(rad_ * cos(t2) * cos(p2), rad_ * sin(p2), rad_ * sin(t2) * cos(p2));
            glVertex3d(rad_ * cos(t1) * cos(p2), rad_ * sin(p2), rad_ * sin(t1) * cos(p2));
        }

    }
    glEnd();
}

void Ball::WallCollision()
{
    float left_point   = Stage::GetInst()->GetLeftPoint();
    float right_point  = Stage::GetInst()->GetRightPoint();
    float Top_point    = Stage::GetInst()->GetTopPoint();
    float Bottom_point = Stage::GetInst()->GetBottomPoint();
    if ((left_point - pos_[0]) >= -1 * (rad_ + offset) || (right_point - pos_[0]) <= (rad_ + offset))       //¶‰E‚Ì•Ç‚Æ‚ÌÕ“Ë”»’è
        vel_[0] = -1 * e * vel_[0];
    if ((Top_point - pos_[2]) >= -1 * (rad_ + offset) || (Bottom_point - pos_[2]) <= (rad_ + offset))       //ã‰º‚Ì•Ç‚Æ‚ÌÕ“Ë”»’è
        vel_[2] = -1 * e * vel_[2];
}

void Ball::BallCollision(Ball& b)
{
    float center_dist = sqrt(pow(pos_[0] - b.pos_[0], 2) + pow(pos_[2] - b.pos_[2], 2));
    if (center_dist <= 2 * (rad_ + offset))
    {
        EVec3f temp = vel_;
        vel_ = b.vel_;
        b.vel_ = temp;
    }
}

void Ball::SetVelo(const EVec3f& v)
{
    vel_ = EVec3f(v);
}

EVec3f Ball::GetVelo()
{
    return vel_;
}

EVec3f Ball::GetPos()
{
    return pos_;
}


void Ball::Step(float dt)
{
    WallCollision();
    pos_ += vel_ * dt;
    //vel_ *= 0.99f;
    ang_ += rad_vel_ * dt;
    Draw();
}