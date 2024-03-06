#pragma once

#pragma unmanaged
#include "OglForCLI.h"


class Billiard
{
private:
	EVec3f _pos ;
	EVec3f _size;
	Billiard();
	void DrawBilliardBord();
public:
	static Billiard* GetInst() {
		static Billiard p;
		return &p;
	}
	void Draw();

};

