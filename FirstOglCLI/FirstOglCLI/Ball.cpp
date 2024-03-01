#include "pch.h"
#include "Ball.h"

Ball::Ball(const EVec3f& pos, const EVec3f& velo, const EVec3f& rot, float radi)
{
	pos_ = pos;
	velo_ = velo;
	rot_ = rot;
	radi_ = radi;
}

Ball::Ball(const Ball& src)
{
	pos_  = src.pos_;
	velo_ = src.velo_;
	rot_  = src.rot_;
	radi_ = src.radi_;
}

void Ball::Step()
{

}

void Ball::Draw() const
{

}

void Ball::SetPos(EVec3f& pos)
{

}

void Ball::SetVelo(EVec3f& velo)
{

}

void Ball::SetRot(EVec3f& rot)
{

}

void Ball::SetRadi(float radi)
{

}

EVec3f Ball::GetPos() const
{

}

EVec3f Ball::GetVelo() const
{

}

EVec3f Ball::GetRot() const
{

}

float  Ball::GetRadi() const
{

}