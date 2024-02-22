#pragma once

#include "OglForCLI.h"

class Ball
{
private:
	EVec3f _pos;
	float _theta_x, _theta_y, _theta_z;
	Ball();

public:
	void step();
	void draw();

};

