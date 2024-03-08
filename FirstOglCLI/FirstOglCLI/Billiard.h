#pragma once

#pragma unmanaged
#include "OglForCLI.h"


class Billiard
{
private:
	EVec3f _pos ;
	EVec3f _size;
	float  _leftPos;
	float  _rightPos;
	float  _frontPos;
	float  _backPos;
	float  _floorPos;
	Billiard();
	void DrawBilliardBord();
public:
	static Billiard* GetInst() {
		static Billiard p;
		return &p;
	}
	void Draw();
	float GetLeftWallPos();
	float GetRightWallPos();
	float GetFrontWallPos();
	float GetBackWallPos();

};

