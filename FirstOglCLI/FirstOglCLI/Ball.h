#pragma once
#include "OglForCLI.h"

class Ball
{
private:
	EVec3f _pos;
	EVec3f _velo;
	float _radi;

public:
	Ball(const EVec3f& pos, const EVec3f& velo, float radi);
	Ball(const Ball& src);
	EVec3f Get_pos();
	void Set_pos(EVec3f pos);
	EVec3f Get_velo();
	void Set_velo(EVec3f velo);
	void Step();
	void Draw();
	void DrawSphere();
};