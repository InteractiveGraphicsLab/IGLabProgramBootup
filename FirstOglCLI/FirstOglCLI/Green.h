#pragma once

#pragma unmanaged
#include "tmath.h"
#include "YPolygon.h"

class Green
{
private:
	std::vector<YPolygon> m_polys;
	

public:
	Green();

	void DrawGreen();
	std::vector<YPolygon> GetPolys() const { return m_polys; }
	
	bool LoadObj(const std::string& path);

};

