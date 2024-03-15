#pragma once

#include "OglForCLI.h"

class Ball
{
private:
	EVec3f pos_;
	EVec3f velo_;
	EVec3f rot_;
	float  radi_;

public:
	Ball(const EVec3f& pos, const EVec3f& velo, const EVec3f& rot, float radi);
	Ball(const EVec3f& pos, const EVec3f& velo, float radi);
	Ball(const Ball& src);

	void Step();

	void Draw() const;
	void DrawSphere() const;

	void SetPos(EVec3f& pos);
	void SetVelo(EVec3f& velo);
	void SetRot(EVec3f& rot);
	void SetRadi(float radi);

	EVec3f GetPos() const;
	EVec3f GetVelo() const;
	EVec3f GetRot() const;
	float  GetRadi() const;
};

