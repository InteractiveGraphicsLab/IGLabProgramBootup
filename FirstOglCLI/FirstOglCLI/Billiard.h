#include "OglForCLI.h"

class Billiard
{
public:
	Billiard();
	void DrawSquare(const EVec3f& corner1, const EVec3f& corner2) const;
	void DrawTable();
};