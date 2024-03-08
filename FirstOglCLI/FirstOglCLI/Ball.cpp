#include "pch.h"
#include "EventManager.h"
#include "Ball.h"

Ball::Ball(const EVec3f& position, const EVec3f& rotation, const EVec3f& velocity, const EVec3f& rotvelocity) {
	_position = position;
	_rotation = rotation;
	_velocity = velocity;
	_rotvelocity = rotvelocity;
}

Ball::Ball(const Ball& src) {
	_position = src._position;
	_rotation = src._rotation;
	_velocity = src._velocity;
	_rotvelocity = src._rotvelocity;
}

void Ball::Draw() {
	const int N = 20;
	glPointSize(3);
	glBegin(GL_TRIANGLES);
	for (int t = 0; t < N; t++)
	{
		for (int p = 0; p < N; p++)
		{
			float t1 = t / (float)N * 2 * 3.141592;
			float t2 = (t + 1) / (float)N * 2 * 3.141592;
			float p1 = p / ((float)N - 0.5f) * 3.141592;
			float p2 = (p + 1) / ((float)N - 0.5f) * 3.141592;
			glNormal3d(cos(p1) * cos(t1), cos(p1) * sin(t1), sin(p1));
			glVertex3d(2 * cos(p1) * cos(t1) + _position[0], 2 * cos(p1) * sin(t1) + _position[1], 2 * sin(p1) + _position[2]);
			glVertex3d(2 * cos(p2) * cos(t1) + _position[0], 2 * cos(p2) * sin(t1) + _position[1], 2 * sin(p2) + _position[2]);
			glVertex3d(2 * cos(p2) * cos(t2) + _position[0], 2 * cos(p2) * sin(t2) + _position[1], 2 * sin(p2) + _position[2]);
			glVertex3d(2 * cos(p1) * cos(t1) + _position[0], 2 * cos(p1) * sin(t1) + _position[1], 2 * sin(p1) + _position[2]);
			glVertex3d(2 * cos(p2) * cos(t2) + _position[0], 2 * cos(p2) * sin(t2) + _position[1], 2 * sin(p2) + _position[2]);
			glVertex3d(2 * cos(p1) * cos(t2) + _position[0], 2 * cos(p1) * sin(t2) + _position[1], 2 * sin(p1) + _position[2]);
		}
	}
	glEnd();
}

void Ball::SetPosition(const EVec3f& position) {

}

void Ball::SetVelocity(const EVec3f& velocity) {

}

EVec3f Ball::GetPosition() {
	return _position;
}

EVec3f Ball::GetVelocity() {
	return _velocity;
}

void Ball::Step() {

}

