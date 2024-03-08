#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include <cmath>

#include "Billiard.h"






Ball::Ball(const EVec3f& pos, const EVec3f& rot, const EVec3f &velo, const EVec3f&acc, const float &r)
{
	_pos  = pos;
	_rot  = rot;
	_velo = velo;
	_acc  = acc;
	_r    =  r;
}

Ball::Ball(const Ball& src)
{
	_pos  = src._pos;
	_rot  = src._rot;
	_velo = src._velo;
	_acc  = src._acc;
	_r    = src._r;
}

void Ball::Draw()
{
	glPushMatrix();
	glTranslated(_pos[0], _pos[1], _pos[2]);
	DrawSphere();
	glPopMatrix();
}

void Ball::DrawSphere()
{
	glEnable(GL_DEPTH_TEST);
	//Material 
	float  shin[1] = { 64 };
	EVec4f spec(1, 1, 1, 0.5);
	EVec4f diff(0.5f, 0.5f, 0.5f, 0.5f);
	EVec4f ambi(0.5f, 0.5f, 0.5f, 0.5f);
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ambi.data());
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, shin);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			float t1 = i / (float)N * 2 * PI;
			float t2 = (i + 1) / (float)N * 2 * PI;
			float p1 = (j / (float)N - 0.5f) * PI;
			float p2 = ((j + 1) / (float)N - 0.5f) * PI;

			glNormal3d(cos(p1) * cos(t1), cos(p1) * sin(t1), sin(p1));

			glVertex3d(_r * cos(p1) * cos(t1), _r * cos(p1) * sin(t1), _r * sin(p1));
			glVertex3d(_r * cos(p2) * cos(t1), _r * cos(p2) * sin(t1), _r * sin(p2));
			glVertex3d(_r * cos(p2) * cos(t2), _r * cos(p2) * sin(t2), _r * sin(p2));

			glVertex3d(_r * cos(p1) * cos(t1), _r * cos(p1) * sin(t1), _r * sin(p1));
			glVertex3d(_r * cos(p2) * cos(t2), _r * cos(p2) * sin(t2), _r * sin(p2));
			glVertex3d(_r * cos(p1) * cos(t2), _r * cos(p1) * sin(t2), _r * sin(p1));
		}
	}
	glEnd();
}


void Ball::CalcPos()
{
	float deltaTime = 0.33f; //‚½‚Ô‚ñ‚Ç‚Á‚©‚©‚çŽ‚Á‚Ä‚±‚ê‚é‚ÆŽv‚¤
	_velo = _velo + _acc * deltaTime;
	_pos = _pos + _velo * deltaTime;
}


void Ball::WallCollision()
{
	if (std::abs(_pos[0] - Billiard::GetInst()->GetLeftWallPos()) <= _r)
	{
		float tempX = -1.0f * _velo[0] * E;
		_velo = { tempX, _velo[1], _velo[2] };
	}
	else if (std::abs(_pos[0] - Billiard::GetInst()->GetRightWallPos()) <= _r)
	{
		float tempX = -1.0f * _velo[0] * E;
		_velo = { tempX, _velo[1], _velo[2] };
	}
	else if (std::abs(_pos[2] - Billiard::GetInst()->GetFrontWallPos()) <= _r)
	{
		float tempZ = -1.0f * _velo[2] * E;
		_velo = { _velo[0], _velo[1], tempZ};
	}
	else if (std::abs(_pos[2] - Billiard::GetInst()->GetBackWallPos()) <= _r)
	{
		float tempZ = -1.0f * _velo[2] * E;
		_velo = { _velo[0], _velo[1], tempZ };
	}
}

void Ball::Step()
{
	WallCollision();
	CalcPos();
}



