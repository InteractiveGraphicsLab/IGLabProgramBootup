#pragma once

#include "OglForCLI.h"

class Table
{
private:
	EVec3f _pos;
	float _height, _width, _depth;
	Table();

public:
	static Table* GetInst() {
		static Table p;
		return &p;
	}
	void draw();

};

