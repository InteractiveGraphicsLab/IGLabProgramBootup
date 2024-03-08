#include "pch.h"
#include "Stage.h"


Stage::Stage()
{
	point0_ = EVec3f(-10, 3, -5);
	point1_ = EVec3f(10, 3, -5);
	point2_ = EVec3f(-10, 3, 5);
	point3_ = EVec3f(10, 3, 5);
	point4_ = EVec3f(-10, 0, -5);
	point5_ = EVec3f(10, 0, -5);
	point6_ = EVec3f(-10, 0, 5);
	point7_ = EVec3f(10, 0, 5);
};

void Stage::DrawFloor()
{
	glBegin(GL_QUADS);
	glVertex3i(point4_[0], point4_[1], point4_[2]);
	glVertex3i(point6_[0], point6_[1], point6_[2]);
	glVertex3i(point7_[0], point7_[1], point7_[2]);
	glVertex3i(point5_[0], point5_[1], point5_[2]);
	glEnd();
}

void Stage::DrawLeftWall()
{
	glBegin(GL_QUADS);
	glVertex3i(point0_[0], point0_[1], point0_[2]);
	glVertex3i(point2_[0], point2_[1], point2_[2]);
	glVertex3i(point6_[0], point6_[1], point6_[2]);
	glVertex3i(point4_[0], point4_[1], point4_[2]);
	glEnd();
}

void Stage::DrawRightWall()
{
	glBegin(GL_QUADS);
	glVertex3i(point1_[0], point1_[1], point1_[2]);
	glVertex3i(point3_[0], point3_[1], point3_[2]);
	glVertex3i(point7_[0], point7_[1], point7_[2]);
	glVertex3i(point5_[0], point5_[1], point5_[2]);
	glEnd();
}

void Stage::DrawTopWall()
{
	glBegin(GL_QUADS);
	glVertex3i(point0_[0], point0_[1], point0_[2]);
	glVertex3i(point1_[0], point1_[1], point1_[2]);
	glVertex3i(point5_[0], point5_[1], point5_[2]);
	glVertex3i(point4_[0], point4_[1], point4_[2]);
	glEnd();
}

void Stage::DrawBottomWall()
{
	glBegin(GL_QUADS);
	glVertex3i(point2_[0], point2_[1], point2_[2]);
	glVertex3i(point3_[0], point3_[1], point3_[2]);
	glVertex3i(point7_[0], point7_[1], point7_[2]);
	glVertex3i(point6_[0], point6_[1], point6_[2]);
	glEnd();
}

float Stage::GetLeftPoint()
{
	return point4_[0];
}

float Stage::GetRightPoint()
{
	return point3_[0];
}

float Stage::GetTopPoint()
{
	return point4_[2];
}

float Stage::GetBottomPoint()
{
	return point3_[2];
}