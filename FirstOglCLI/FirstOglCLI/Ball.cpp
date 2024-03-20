#pragma once
#include "pch.h"
#include "Ball.h"
#include "EventManager.h"
#include <cmath>

Ball::Ball(const EVec3f& pos, const EVec3f& velo, float radi)
{
    _pos = pos;
    _velo = velo;
    _radi = radi;
};

Ball::Ball(const Ball& src)
{
    _pos = src._pos;
    _velo = src._velo;
    _radi = src._radi;
};

EVec3f Ball::Get_pos()
{
	return _pos;
};

void Ball::Set_pos(EVec3f pos)
{
	_pos = pos;
};

EVec3f Ball::Get_velo()
{
	return _velo;
};

void Ball::Set_velo(EVec3f velo) 
{
	_velo = velo;
};

void Ball::Draw()
{
    glTranslated(_pos[0], _pos[1], _pos[2]);
    DrawSphere();
    glTranslated(-_pos[0], -_pos[1], -_pos[2]);
};

void Ball::DrawSphere()
{
    const int    N = 20;
    const double M_PI = 3.141592;
    glEnable(GL_DEPTH_TEST);
    //Material
    float   shin[1] = { 64 };
    EVec4f  spec(1, 1, 1, 0.5); //拡散
    EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);   //ハイライト
    EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);   //ベースカラー
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
    glEnable(GL_LIGHTING);  //ライトスイッチオン
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glBegin(GL_TRIANGLES);
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            double t1 = (x) / (double)N * 2.0 * M_PI;
            double t2 = (x + 1) / (double)N * 2.0 * M_PI;
            double p1 = (y) / (double)N * 1.0 * M_PI - 0.5 * M_PI;
            double p2 = (y + 1) / (double)N * 1.0 * M_PI - 0.5 * M_PI;
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
};

void Ball::Step()
{
    float dt = 0.33f;
    const float max_width = 127.0f - _radi;
    const float max_height = 63.5f - _radi;
    _velo += EVec3f(0, -1.0, 0) * dt; //v=v+at
    _pos += _velo * dt;   //x=x+vt
    //床に反射
    if (_pos[1] <= _radi)
    {
        _pos[1] = _radi;
        _velo[1] *= -0.8f; //反射減衰
        if (std::fabs(_velo[1]) < 0.01f) _velo[1] = 0.0f;
    }
    //m_velo *= 1.0;
    //壁に反射
    if (_pos[0] >= max_width)
    {
        _pos[0] = max_width;
        _velo[0] *= -1.0f; //反射減衰
    }
    if (_pos[0] <= -max_width)
    {
        _pos[0] = -max_width;
        _velo[0] *= -1.0f; //反射減衰
    }
    if (_pos[2] >= max_height)
    {
        _pos[2] = max_height;
        _velo[2] *= -1.0f; //反射減衰
    }
    if (_pos[2] <= -max_height)
    {
        _pos[2] = -max_height;
        _velo[2] *= -1.0f; //反射減衰
    }
    _velo *= 0.995f; //速度減衰(動きを見たいためx,zはそのまま)
};
