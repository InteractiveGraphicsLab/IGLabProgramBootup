#pragma once
#include "tmath.h"

class Ball

{
private:
	EVec3d pos_; // ���S���W
	EVec3d v_; // ���x
public:
	Ball();
	~Ball();
	void setPos(EVec3d pos); // ���S���W���Z�b�g
	void setVelocity(EVec3d v); // ���x���Z�b�g
	EVec3d getPos(); // ���S���W���擾
	EVec3d getVelocity(); //���x���擾
	EVec3d CalcVelocity(EVec3d v); //���x���v�Z
	void Step();
	void Draw(); 
};

