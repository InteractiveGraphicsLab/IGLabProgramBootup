#include "pch.h"
#include "Ball.h"
#define _USE_MATH_DEFINES
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

void Ball::SetVelo(const EVec2i& e)
{
    float dist = sqrt(pow(pos_[0] - e[0], 2) + pow(pos_[1] - e[1], 2));
    vel_ = EVec3f(dist, 0, 0);
}

EVec3f Ball::GetPos()
{
    return pos_;
}


void Ball::Step(float dt)
{
    pos_ += vel_ * dt;
    ang_ += rad_vel_ * dt;
    Draw();
}