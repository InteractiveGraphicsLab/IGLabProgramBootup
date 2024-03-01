#include "pch.h"
#include "EventManager.h"
#include "Ball.h"







Ball::Ball(const EVec3f& pos, const EVec3f& rot, const EVec3f &velo, const float &acc, const int &rad)
{
	_pos  = pos;
	_rot  = rot;
	_velo = velo;
	_acc  = acc;
	_rad =  rad;
}

Ball::Ball(const Ball& src)
{
	_pos  = src._pos;
	_rot  = src._rot;
	_velo = src._velo;
	_acc  = src._acc;
	_rad  = src._rad;
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

			glVertex3d(2 * cos(p1) * cos(t1), _rad * cos(p1) * sin(t1), _rad * sin(p1));
			glVertex3d(2 * cos(p2) * cos(t1), _rad * cos(p2) * sin(t1), _rad * sin(p2));
			glVertex3d(2 * cos(p2) * cos(t2), _rad * cos(p2) * sin(t2), _rad * sin(p2));

			glVertex3d(2 * cos(p1) * cos(t1), _rad * cos(p1) * sin(t1), _rad * sin(p1));
			glVertex3d(2 * cos(p2) * cos(t2), _rad * cos(p2) * sin(t2), _rad * sin(p2));
			glVertex3d(2 * cos(p1) * cos(t2), _rad * cos(p1) * sin(t2), _rad * sin(p1));
		}
	}
	glEnd();
}

void Ball::Step()
{
	float deltaTime = 0.33f;
	_pos = _pos + _velo * deltaTime;
	Draw();
	std::cout << _pos;
}

