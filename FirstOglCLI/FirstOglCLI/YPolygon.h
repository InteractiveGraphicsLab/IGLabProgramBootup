#pragma once

#pragma unmanaged
#include "tmath.h"


class YPolygon
{
private:
	EVec3f m_p0, m_p1, m_p2;
	EVec3f m_normal;

public:
	YPolygon(const EVec3f& pos0, const EVec3f& pos1, const EVec3f& pos2, const EVec3f& normal);
	YPolygon(const YPolygon& src);
	YPolygon();
	//Polygon operator=(const Polygon& src);

	void DrawMesh();

	EVec3f GetP0() { return m_p0; }
	EVec3f GetP1() { return m_p1; }
	EVec3f GetP2() { return m_p2; }
	EVec3f GetNormal() { return m_normal.normalized(); }

};
