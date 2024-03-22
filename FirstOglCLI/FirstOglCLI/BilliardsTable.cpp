#include "pch.h"
#include "BilliardsTable.h"

BilliardsTable::BilliardsTable()
{
	cuboids_.push_back(Cuboid(EVec3f(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f));
}

void BilliardsTable::Draw() const
{
	for (int i = 0; i < cuboids_.size(); i++) 
	{
		cuboids_[i].DrawCuboid();
	}
	std::cout << "aaaaa";
}