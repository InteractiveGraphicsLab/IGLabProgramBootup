#include "OglForCLI.h"
#include <vector>

class Billiard
{
private:
	std::vector<EVec3f> m_vertices;
public:
	Billiard();
	void DrawTable();
};