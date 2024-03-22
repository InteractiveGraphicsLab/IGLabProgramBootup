#include "pch.h"
#include "BilliardTable.h"
#include "Cuboid.h"

BilliardTable::BilliardTable()
{
	m_cuboids.push_back(Cuboid(EVec3f(0.0f, 0.0f, 0.0f), 290.0f, 160.0f, 15.0f));
}

void BilliardTable::GenerateBilliardTable()
{
	for (int i = 0; i < m_cuboids.size(); ++i) {
		m_cuboids[i].Draw();
	}
}