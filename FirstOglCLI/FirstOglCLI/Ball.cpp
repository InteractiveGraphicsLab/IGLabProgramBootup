#include "pch.h"
#include "EventManager.h"
#include "Ball.h"

Ball::Ball(float radi, EVec3f& pos, EVec3f& rot, EVec3f& velo, EVec3f& veloangle)
{
    _radi = radi;
    _pos = pos;
    _rot = rot;
    _velo = velo;
    _veloangle = veloangle;
}

Ball::Ball(const Ball& src)
{
    _radi = src._radi;
    _pos = src._pos;
    _rot = src._rot;
    _velo = src._velo;
    _veloangle = src._veloangle;
}