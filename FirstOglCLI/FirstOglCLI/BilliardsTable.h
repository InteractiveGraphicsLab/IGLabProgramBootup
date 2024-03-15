#pragma once

#include "OglForCLI.h"
#include "Cuboid.h"

class BilliardsTable
{
private:
	BilliardsTable();
	std::vector<Cuboid> cuboids_;

public:
	static BilliardsTable* GetInst() {
		static BilliardsTable p;
		return &p;
	}
};

