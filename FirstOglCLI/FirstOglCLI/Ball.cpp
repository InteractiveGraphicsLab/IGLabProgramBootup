#include "pch.h"
#include "EventManager.h"
#include "Ball.h"

Ball::Ball(const EVec3f& pos, const EVec3f& rot, const EVec3f& velo, const EVec3f& veloangle, float radi)
{
    pos_ = pos;
    rot_ = rot;
    velo_ = velo;
    veloangle_ = veloangle;
    radi_ = radi;
}

Ball::Ball(const Ball& src)
{
    pos_ = src.pos_;
    rot_ = src.rot_;
    velo_ = src.velo_;
    veloangle_ = src.veloangle_;
    radi_ = src.radi_;
}

EVec3f Ball::GetPos()
{
    return pos_;
}

EVec3f Ball::GetVelo()
{
    return velo_;
}

float Ball::GetRadi()
{
    return radi_;
}

void Ball::SetPos(const EVec3f& pos)
{
    pos_ = pos;
}

void Ball::SetVelo(const EVec3f& velo)
{
    pos_ = velo;
}

void Ball::Step()
{
    float dt = 0.33f;
    //_velo += EVec3f(0.0f, -1.0f, 0.0f) * dt;
    pos_ += velo_ * dt;
}

void Ball::Draw()
{
    glPushMatrix();
    //glMultMatrix();
    glTranslated(pos_[0], pos_[1], pos_[2]);
    DrawSphere();
    glPopMatrix();
}

void Ball::DrawSphere()
{
    const int N = 20;
    const double PI = 3.141562;

    glEnable(GL_DEPTH_TEST);
    //Material 
    float   shin[1] = { 64 };
    EVec4f  spec(1, 1, 1, 0.5);
    EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);
    EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glBegin(GL_TRIANGLES);
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            double t1 = (x) / (double)N * 2.0 * PI;
            double t2 = (x + 1) / (double)N * 2.0 * PI;
            double p1 = (y) / (double)N * 1.0 * PI - 0.5 * PI;
            double p2 = (y + 1) / (double)N * 1.0 * PI - 0.5 * PI;

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3d(cos(t1) * cos(p1) * radi_, sin(p1) * radi_, sin(t1) * cos(p1) * radi_);
            glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glVertex3d(cos(t2) * cos(p2) * radi_, sin(p2) * radi_, sin(t2) * cos(p2) * radi_);
            glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
            glVertex3d(cos(t2) * cos(p1) * radi_, sin(p1) * radi_, sin(t2) * cos(p1) * radi_);

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3d(cos(t1) * cos(p1) * radi_, sin(p1) * radi_, sin(t1) * cos(p1) * radi_);
            glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
            glVertex3d(cos(t1) * cos(p2) * radi_, sin(p2) * radi_, sin(t1) * cos(p2) * radi_);
            glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glVertex3d(cos(t2) * cos(p2) * radi_, sin(p2) * radi_, sin(t2) * cos(p2) * radi_);

        }
    }
    glEnd();
}