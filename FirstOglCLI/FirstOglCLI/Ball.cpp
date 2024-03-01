#include "pch.h"
#include "EventManager.h"
#include "Ball.h"

Ball::Ball(const EVec3f& pos, const EVec3f& rot, const EVec3f& velo, const EVec3f& veloangle, float radi)
{
    _pos = pos;
    _rot = rot;
    _velo = velo;
    _veloangle = veloangle;
    _radi = radi;
}

Ball::Ball(const Ball& src)
{
    _pos = src._pos;
    _rot = src._rot;
    _velo = src._velo;
    _veloangle = src._veloangle;
    _radi = src._radi;
}

EVec3f Ball::GetPos()
{
    return _pos;
}

EVec3f Ball::GetVelo()
{
    return _velo;
}

float Ball::GetRadi()
{
    return _radi;
}

void Ball::SetPos(const EVec3f& pos)
{
    _pos = pos;
}

void Ball::SetVelo(const EVec3f& velo)
{
    _pos = velo;
}

void Ball::Step()
{
    float dt = 0.33f;
    //_velo += EVec3f(0.0f, -1.0f, 0.0f) * dt;
    _pos += _velo * dt;
}

void Ball::Draw()
{
    glPushMatrix();
    //glMultMatrix();
    glTranslated(_pos[0], _pos[1], _pos[2]);
    DrawSphere();
    glPopMatrix();
}

void Ball::DrawSphere()
{
    const int N = 20;
    const double _PI = 3.141562;

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
            double t1 = (x) / (double)N * 2.0 * _PI;
            double t2 = (x + 1) / (double)N * 2.0 * _PI;
            double p1 = (y) / (double)N * 1.0 * _PI - 0.5 * _PI;
            double p2 = (y + 1) / (double)N * 1.0 * _PI - 0.5 * _PI;

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3d(cos(t1) * cos(p1) * _radi, sin(p1) * _radi, sin(t1) * cos(p1) * _radi);
            glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glVertex3d(cos(t2) * cos(p2) * _radi, sin(p2) * _radi, sin(t2) * cos(p2) * _radi);
            glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
            glVertex3d(cos(t2) * cos(p1) * _radi, sin(p1) * _radi, sin(t2) * cos(p1) * _radi);

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3d(cos(t1) * cos(p1) * _radi, sin(p1) * _radi, sin(t1) * cos(p1) * _radi);
            glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
            glVertex3d(cos(t1) * cos(p2) * _radi, sin(p2) * _radi, sin(t1) * cos(p2) * _radi);
            glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glVertex3d(cos(t2) * cos(p2) * _radi, sin(p2) * _radi, sin(t2) * cos(p2) * _radi);

        }
    }
    glEnd();
}