#include "pch.h"
#include "Cuboid.h"
#include "EventManager.h"
#include <cmath>

Cuboid::Cuboid(const EVec3f& pos, const float& width, const float&height, const float& depth)
{
    _pos = pos;
    _width = width;
    _height = height;
    _depth = depth;
};

Cuboid::Cuboid(const Cuboid& src)
{
    _pos = src._pos;
    _width = src._width;
    _height = src._height;
    _depth = src._depth;
};

void Cuboid::Draw()
{
    glTranslated(_pos[0], _pos[1], _pos[2]);
    DrawCuboid();
    glTranslated(-_pos[0], -_pos[1], -_pos[2]);
};

void Cuboid::DrawCuboid()
{
    EVec4f  spec(1, 1, 1, 0.5); //拡散
    EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);   //ハイライト
    EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);   //ベースカラー
    float   shin[1] = { 64 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
    glEnable(GL_LIGHTING);  //ライトスイッチオン
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glBegin(GL_TRIANGLES);

    glNormal3d(0.0f, 1.0f, 0.0f);
    glVertex3d(_width / 2, _height / 2, _depth / 2);
    glNormal3d(0.0f, 1.0f, 0.0f);
    glVertex3d(_width / 2, _height / 2, (-_depth / 2));
    glNormal3d(0.0f, 1.0f, 0.0f);
    glVertex3d(-(_width / 2), _height / 2, _depth / 2);
    glNormal3d(0.0f, 1.0f, 0.0f);
    glVertex3d(-(_width / 2), _height / 2, _depth / 2);
    glNormal3d(0.0f, 1.0f, 0.0f);
    glVertex3d(-(_width / 2), _height / 2, -(_depth / 2));
    glNormal3d(0.0f, 1.0f, 0.0f);
    glVertex3d(_width / 2, _height / 2, -(_depth / 2));
    
    glNormal3d(0.0f, -1.0f, 0.0f);
    glVertex3d(_width / 2, -(_height / 2), _depth / 2);
    glNormal3d(0.0f, -1.0f, 0.0f);
    glVertex3d(_width / 2, -(_height / 2), (-_depth / 2));
    glNormal3d(0.0f, -1.0f, 0.0f);
    glVertex3d(-(_width / 2), -(_height / 2), _depth / 2);
    glNormal3d(0.0f, -1.0f, 0.0f);
    glVertex3d(-(_width / 2), -(_height / 2), _depth / 2);
    glNormal3d(0.0f, -1.0f, 0.0f);
    glVertex3d(-(_width / 2), -(_height / 2), -(_depth / 2));
    glNormal3d(0.0f, -1.0f, 0.0f);
    glVertex3d(_width / 2, -(_height / 2), -(_depth / 2));
    

    glNormal3d(1.0f, 0.0f, 0.0f);
    glVertex3d(_width / 2, _height / 2, _depth / 2);
    glNormal3d(1.0f, 0.0f, 0.0f);
    glVertex3d(_width / 2, _height / 2, -(_depth / 2));
    glNormal3d(1.0f, 0.0f, 0.0f);
    glVertex3d(_width / 2, -(_height / 2), _depth / 2);
    glNormal3d(1.0f, 0.0f, 0.0f);
    glVertex3d(_width / 2, -(_height / 2), _depth / 2);
    glNormal3d(1.0f, 0.0f, 0.0f);
    glVertex3d(_width / 2, -(_height / 2), -(_depth / 2));
    glNormal3d(1.0f, 0.0f, 0.0f);
    glVertex3d(_width / 2, _height / 2, -(_depth / 2));

    glNormal3d(-1.0f, 0.0f, 0.0f);
    glVertex3d(-(_width / 2), _height / 2, _depth / 2);
    glNormal3d(-1.0f, 0.0f, 0.0f);
    glVertex3d(-(_width / 2), _height / 2, -(_depth / 2));
    glNormal3d(-1.0f, 0.0f, 0.0f);
    glVertex3d(-(_width / 2), -(_height / 2), _depth / 2);
    glNormal3d(-1.0f, 0.0f, 0.0f);
    glVertex3d(-(_width / 2), -(_height / 2), _depth / 2);
    glNormal3d(-1.0f, 0.0f, 0.0f);
    glVertex3d(-(_width / 2), -(_height / 2), -(_depth / 2));
    glNormal3d(-1.0f, 0.0f, 0.0f);
    glVertex3d(-(_width / 2), _height / 2, -(_depth / 2));


    glNormal3d(0.0f, 0.0f, 1.0f);
    glVertex3d(_width / 2, _height / 2, _depth / 2);
    glNormal3d(0.0f, 0.0f, 1.0f);
    glVertex3d(_width / 2, -(_height / 2), _depth / 2);
    glNormal3d(0.0f, 0.0f, 1.0f);
    glVertex3d(-(_width / 2), _height / 2, _depth / 2);
    glNormal3d(0.0f, 0.0f, 1.0f);
    glVertex3d(-(_width / 2), _height / 2, _depth / 2);
    glNormal3d(0.0f, 0.0f, 1.0f);
    glVertex3d(-(_width / 2), -(_height / 2), _depth / 2);
    glNormal3d(0.0f, 0.0f, 1.0f);
    glVertex3d(_width / 2, -(_height / 2), _depth / 2);

    glNormal3d(0.0f, 0.0f, -1.0f);
    glVertex3d(_width / 2, _height / 2, -(_depth / 2));
    glNormal3d(0.0f, 0.0f, -1.0f);
    glVertex3d(_width / 2, -(_height / 2), -(_depth / 2));
    glNormal3d(0.0f, 0.0f, -1.0f);
    glVertex3d(-(_width / 2), _height / 2, -(_depth / 2));
    glNormal3d(0.0f, 0.0f, -1.0f);
    glVertex3d(-(_width / 2), _height / 2, -(_depth / 2));
    glNormal3d(0.0f, 0.0f, -1.0f);
    glVertex3d(-(_width / 2), -(_height / 2), -(_depth / 2));
    glNormal3d(0.0f, 0.0f, -1.0f);
    glVertex3d(_width / 2, -(_height / 2), -(_depth / 2));
     
    glEnd();
};