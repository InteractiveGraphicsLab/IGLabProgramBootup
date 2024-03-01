#pragma once
#include "OglForCLI.h"

class Ball
{

	private:
		EVec3f _pos;
		EVec3f _rot;
		EVec3f  _velo;
		float  _acc;
		int    _rad;
		
		//íËêî
		int    N  = 20;
		float  PI = 3.141592f;

	public:
		Ball(const EVec3f& pos, const EVec3f& rot, const EVec3f& velo, const float& acc, const int &rad);
		Ball(const Ball& src);
		void Draw();
		void DrawSphere();
		void Step();
};

