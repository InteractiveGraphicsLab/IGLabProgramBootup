#pragma once
#include "Cuboid.h"
#include "OglForCLI.h"

class BilliardTable
{
private:
	std::vector<Cuboid> m_cuboids;

public:
	BilliardTable();
	static BilliardTable* GetInst() {
		static BilliardTable p;
		return &p;
	}
	void GenerateBilliardTable();
};

