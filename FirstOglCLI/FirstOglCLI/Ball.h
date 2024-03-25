#pragma once
#include "tmath.h"

class Ball

{
private:
	EVec3f pos_; 
	EVec3f v_; 
	float radius_;
public:
	Ball();
	Ball(const EVec3f& pos, const EVec3f& v);
	~Ball();
	void setPos(const EVec3f& pos); 
	void setVelocity(const EVec3f &v); 
	EVec3f getPos() const; 
	EVec3f getVelocity() const; 
	float getRadius() const;
	void Step(float dt = 0.01f);
	void Draw();
};
