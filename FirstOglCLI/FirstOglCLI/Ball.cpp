#include "pch.h"
#include "Ball.h"
#include "OglForCLI.h"
#include "EventManager.h"


Ball::Ball() {
	radius_ = 2.0f;
	collision_ = true;
}

Ball::~Ball() {

}

void Ball::setPos(const EVec3f &pos)
{
	pos_ = pos;
}


void Ball::setVelocity(const EVec3f &v)
{
	v_ = v;
}

void Ball::setCollision(const bool& collision)
{
	collision_ = collision;
}


EVec3f Ball::getPos() const
{
	return pos_;
}


EVec3f Ball::getVelocity() const
{
	return v_;
}

float Ball::getRadius() const
{
	return radius_;
}

bool Ball::getCollision() const
{
	return collision_;
}



void Ball::Draw() {
	const int N = 10;
	glBegin(GL_TRIANGLES);
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			// theta‚ðN•ªŠ„
			float t1 = (float) (2 * M_PI *    i    / N);
			float t2 = (float) (2 * M_PI * (i + 1) / N);
			// phi‚ðN•ªŠ„
			float p1 = (float) (M_PI *    j    / N - M_PI/2);
			float p2 = (float) (M_PI * (j + 1) / N - M_PI/2);
			//ŽOŠpŒ`1‚Â–Ú
			glNormal3d(cos(t1) * cos(p1), sin(t1) * cos(p1), sin(p1));
			glVertex3d(radius_ * cos(t2) * cos(p1) + pos_[0], radius_ * sin(t2) * cos(p1) + pos_[1], radius_ * sin(p1) + pos_[2]);
			glVertex3d(radius_ * cos(t1) * cos(p2) + pos_[0], radius_ * sin(t1) * cos(p2) + pos_[1], radius_ * sin(p2) + pos_[2]);
			glVertex3d(radius_ * cos(t1) * cos(p1) + pos_[0], radius_ * sin(t1) * cos(p1) + pos_[1], radius_ * sin(p1) + pos_[2]);
			//ŽOŠpŒ`‚Q‚Â–Ú
			glNormal3d(cos(t1) * cos(p1), sin(t1) * cos(p1), sin(p1));
			glVertex3d(radius_ * cos(t1) * cos(p2) + pos_[0], radius_ * sin(t1) * cos(p2) + pos_[1], radius_ * sin(p2) + pos_[2]);
			glVertex3d(radius_ * cos(t2) * cos(p1) + pos_[0], radius_ * sin(t2) * cos(p1) + pos_[1], radius_ * sin(p1) + pos_[2]);
			glVertex3d(radius_ * cos(t2) * cos(p2) + pos_[0], radius_ * sin(t2) * cos(p2) + pos_[1], radius_ * sin(p2) + pos_[2]);
		}
	}
	glEnd();
}

void Ball::Step(float dt)
{
	static const EVec3f Grav{ 0, -9.8f, 0 };
	v_   = v_ + dt * Grav;
	pos_ = pos_ + dt * v_;
}