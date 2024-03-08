#pragma once

#include "OglForCLI.h"

class Stage
{
private:
	EVec3f point0_;
	EVec3f point1_;
	EVec3f point2_;
	EVec3f point3_;
	EVec3f point4_;
	EVec3f point5_;
	EVec3f point6_;
	EVec3f point7_;
	//     0				1
	//     4				5
	// 2				3
	// 6				7

	Stage();

public:
	static Stage* GetInst()
	{
		static Stage s;
		return &s;
	}

	void DrawFloor();
	void DrawLeftWall();
	void DrawRightWall();
	void DrawTopWall();
	void DrawBottomWall();
	float GetLeftPoint();
	float GetRightPoint();
	float GetTopPoint();
	float GetBottomPoint();
};