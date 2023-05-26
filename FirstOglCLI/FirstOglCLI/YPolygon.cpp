#include "pch.h"
#include "YPolygon.h"
#include "OglForCLI.h"


YPolygon::YPolygon(const EVec3f& pos0, const EVec3f& pos1, const EVec3f& pos2, const EVec3f& normal)
{
	m_p0 = pos0;
	m_p1 = pos1;
	m_p2 = pos2;
	m_normal = normal;
};

YPolygon::YPolygon(const YPolygon& src)
{
	m_p0 = src.m_p0;
	m_p1 = src.m_p1;
	m_p2 = src.m_p2;
	m_normal = src.m_normal;
};

YPolygon::YPolygon() 
{
	m_p0 = EVec3f(0, 0, 0);
	m_p1 = EVec3f(0, 0, 0);
	m_p2 = EVec3f(0, 0, 0);
	m_normal = EVec3f(0, 0, 0);

}

void YPolygon::DrawMesh()
{
	//glEnable(GL_DEPTH_TEST);
	////Material 
	//float   shin[1] = { 64 };
	//EVec4f  spec(1, 1, 1, 0.5);
	//EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f); //êFí≤êÆ
	//EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);

	glColor3d(0.4, 0.51, 0);
	glBegin(GL_TRIANGLES);

	glVertex3fv(m_p0.data());
	glVertex3fv(m_p1.data());
	glVertex3fv(m_p2.data());

	glEnd();

};

