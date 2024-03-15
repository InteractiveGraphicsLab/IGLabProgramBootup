#include "pch.h"
#include "BilliardTable.h"

BilliardTable::BilliardTable()
{
	cuboids_.push_back(Cuboid(EVec3f(0, -1.0f, 0), 10, 2, 10));
}

void BilliardTable::Draw() const
{
	for (const auto& cuboid : cuboids_)
	{
		cuboid.Draw();
	}
}