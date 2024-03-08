#include "pch.h"
#include "Billiard.h"

Billiard::Billiard() {

}

void Billiard::DrawSquare(const EVec3f& corner1, const EVec3f& corner2) const
{
	glBegin(GL_QUADS);
	glColor3d(1, 1, 1);
	
	glVertex3d(corner1[0], corner1[1], corner1[2]);
	glVertex3d(corner1[0], corner2[1], corner1[2]);
	glVertex3d(corner2[0], corner2[1], corner2[2]);
	glVertex3d(corner2[0], corner1[1], corner2[2]);
	glEnd();
}

void Billiard::DrawTable()
{
	DrawSquare(EVec3f(1, 1, 0), EVec3f(-1, -1, 0));
}