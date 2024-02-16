#include "pch.h"
#include "Ball.h"
#include "EventManager.h"

void Ball::Draw()
{
	glBegin(GL_TRIANGLES);
	for (int t = 0; t < N; t++)
	{
		for (int p = 0; p < N; p++)
		{
			float t1 = t / (float)N * 2 * 3.141592;
			float t2 = (t + 1) / (float)N * 2 * 3.141592;
			float p1 = (p / (float)N - 0.5f) * 3.141592;
			float p2 = ((p + 1) / (float)N - 0.5f) * 3.141592;
			glNormal3d(cos(p1) * cos(t1), cos(p1) * sin(t1), sin(p1));
			glVertex3d(2 * cos(p1) * cos(t1), 2 * cos(p1) * sin(t1), 2 * sin(p1));
			glVertex3d(2 * cos(p2) * cos(t1), 2 * cos(p2) * sin(t1), 2 * sin(p2));
			glVertex3d(2 * cos(p2) * cos(t2), 2 * cos(p2) * sin(t2), 2 * sin(p2));
			glVertex3d(2 * cos(p1) * cos(t1), 2 * cos(p1) * sin(t1), 2 * sin(p1));
			glVertex3d(2 * cos(p1) * cos(t2), 2 * cos(p1) * sin(t2), 2 * sin(p1));
			glVertex3d(2 * cos(p2) * cos(t2), 2 * cos(p2) * sin(t2), 2 * sin(p2));
		}
	}
}