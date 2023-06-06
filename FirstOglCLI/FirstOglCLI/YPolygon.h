#pragma once

#pragma unmanaged
#include "tmath.h"


class YPolygon
{
private:
	EVec3f m_p0, m_p1, m_p2;
	EVec3f m_normal;

	//std::vector<EVec3f> m_v;
	//std::vector<EVec3f> m_vn;
	
public:
	//YPolygon(const std::vector<EVec3f>& v, const std::vector<EVec3f>& vn);
	YPolygon(const EVec3f& pos0, const EVec3f& pos1, const EVec3f& pos2, const EVec3f& normal);
	YPolygon(const YPolygon& src);
	YPolygon();
	//Polygon operator=(const Polygon& src);

	

	void DrawMesh();

	std::vector<EVec3f> GetPolygon() const { return std::vector<EVec3f>{m_p0, m_p1, m_p2}; }
	EVec3f GetP0() { return m_p0; }
	EVec3f GetP1() { return m_p1; }
	EVec3f GetP2() { return m_p2; }
	EVec3f GetNormal() { return m_normal.normalized(); }

};
