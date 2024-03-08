#pragma once
#include "OglForCLI.h"

class Ball
{

	private:
		EVec3f _pos;
		EVec3f _rot;
		EVec3f _velo;
		EVec3f _acc;
		float  _r;
		
		//íËêî
		int    N  = 50;
		float  PI = 3.141592f;
		float  E  = 1;

	public:
		Ball(const EVec3f& pos, const EVec3f& rot, const EVec3f& velo, const EVec3f& acc, const float &r);
		Ball(const Ball& src);
		void Draw();
		void DrawSphere();
		void CalcPos();
		void WallCollision();
		void Step();
};

