#pragma once
#include "tmath.h"

class Ball

{
private:
	EVec3f pos_; 
	EVec3f v_; 
	float radius_;
	bool separate_;
public:
	Ball();
	~Ball();
	void setPos(const EVec3f &pos); 
	void setVelocity(EVec3f v); 
	EVec3f getPos() const; 
	EVec3f getVelocity() const; 
	float getRadius() const;
	void Step(float dt = 0.01f);
	void Draw();
};
