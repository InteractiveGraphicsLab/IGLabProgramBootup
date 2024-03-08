#include "pch.h"
#include "Ball.h"
#include "Value.h"

Ball::Ball(const EVec3f& pos, const EVec3f& vel)
{
	pos_ = pos;
	vel_ = vel;
	radius_ = 1.0f;
}

Ball::Ball(const Ball& src)
{
	pos_ = src.pos_;
	vel_ = src.vel_;
	radius_ = src.radius_;
}

EVec3f Ball::getPos() const
{
	return pos_;
}

void Ball::draw()
{
	glBegin(GL_TRIANGLES);
	glColor3d(1, 1, 1);
	const int N = 15;
	for (int t = 0; t < N; t++)
	{
		for (int p = 0; p < N; p++)
		{
			float t1 = t / (float)N * 2 * 3.141592;
			float t2 = (t + 1) / (float)N * 2 * 3.141592;
			float p1 = (p / (float)N - 0.5f) * 3.141592;
			float p2 = ((p + 1) / (float)N - 0.5f) * 3.141592;
			glNormal3d(cos(p1) * cos(t1), cos(p1) * sin(t1), sin(p1));

			glVertex3d(radius_ * cos(p1) * cos(t1) + pos_[0], radius_ * cos(p1) * sin(t1) + pos_[1], radius_ * sin(p1) + pos_[2]);
			glVertex3d(radius_ * cos(p2) * cos(t1) + pos_[0], radius_ * cos(p2) * sin(t1) + pos_[1], radius_ * sin(p2) + pos_[2]);
			glVertex3d(radius_ * cos(p2) * cos(t2) + pos_[0], radius_ * cos(p2) * sin(t2) + pos_[1], radius_ * sin(p2) + pos_[2]);

			glVertex3d(radius_ * cos(p1) * cos(t1) + pos_[0], radius_ * cos(p1) * sin(t1) + pos_[1], radius_ * sin(p1) + pos_[2]);
			glVertex3d(radius_ * cos(p2) * cos(t2) + pos_[0], radius_ * cos(p2) * sin(t2) + pos_[1], radius_ * sin(p2) + pos_[2]);
			glVertex3d(radius_ * cos(p1) * cos(t2) + pos_[0], radius_ * cos(p1) * sin(t2) + pos_[1], radius_ * sin(p1) + pos_[2]);
		}
	}
	glEnd();
}

void Ball::Step(float dt)
{
	vel_ += grav_ * dt;
	pos_ += vel_ * dt;
}