#include "pch.h"
#include "Billiard.h"

Billiard::Billiard() {
	m_vertices.push_back(EVec3f(-1, 0, 0.5));
	m_vertices.push_back(EVec3f(1, 0, 0.5));
	m_vertices.push_back(EVec3f(-1, 0, -0.5));
	m_vertices.push_back(EVec3f(1, 0, -0.5));
}

void Billiard::DrawTable()
{
	glBegin(GL_TRIANGLES);
	glColor3d(0, 1, 0);

	glVertex3d(m_vertices[0][0], m_vertices[0][1], m_vertices[0][2]);
	glVertex3d(m_vertices[1][0], m_vertices[1][1], m_vertices[1][2]);
	glVertex3d(m_vertices[2][0], m_vertices[2][1], m_vertices[2][2]);

	glVertex3d(m_vertices[1][0], m_vertices[1][1], m_vertices[1][2]);
	glVertex3d(m_vertices[2][0], m_vertices[2][1], m_vertices[2][2]);
	glVertex3d(m_vertices[3][0], m_vertices[3][1], m_vertices[3][2]);

	glEnd();
}