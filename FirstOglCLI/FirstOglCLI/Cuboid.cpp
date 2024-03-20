#include "pch.h"
#include "Cuboid.h"
#include "EventManager.h"
#include <cmath>

Cuboid::Cuboid(const EVec3f& pos, const float(& size)[3])
{
    _pos = pos;
    //size‚Íwidth, height, depth
    _size[0] = size[0];
    _size[1] = size[1];
    _size[2] = size[2];
};

Cuboid::Cuboid(const Cuboid& src)
{
    _pos = src._pos;
    _size[0] = src._size[0];
    _size[1] = src._size[1];
    _size[2] = src._size[2];
};

void Cuboid::Draw()
{
    glTranslated(_pos[0], _pos[1], _pos[2]);
    DrawCuboid();
    glTranslated(-_pos[0], -_pos[1], -_pos[2]);
};

void Cuboid::DrawCuboid()
{
    
};