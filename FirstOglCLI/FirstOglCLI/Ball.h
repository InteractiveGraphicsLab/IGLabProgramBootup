#pragma once

#include "pch.h"
#include "EventManager.h"
#include "OglForCLI.h"

class Ball {
private:
	EVec3f _position, _rotation, _velocity, _rotvelocity;

public:
	Ball(const EVec3f& position, const EVec3f& rotation, const EVec3f& velocity, const EVec3f& rotvelocity);
	Ball(const Ball& src);
	EVec3f GetPosition();
	EVec3f GetVelocity();
	void SetPosition(const EVec3f& position);
	void SetVelocity(const EVec3f& velocity);
	void Step();
	void Draw();

};