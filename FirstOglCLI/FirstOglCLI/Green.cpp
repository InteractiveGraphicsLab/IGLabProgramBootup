#include "pch.h"
#include "Green.h"
#include "OglForCLI.h"
#include "Green.h"
#include <fstream>
#include <iostream>
#include <string>

Green::Green()
{
	m_polys = std::vector<YPolygon>(0);

	EVec3f p0 = EVec3f(16.0f, 0, 1.0f);
	EVec3f p1 = EVec3f(-14.0f, -7.0f, -1.0f);
	EVec3f p2 = EVec3f(-14.0f, 7.0f, -1.0f);

	m_polys.push_back(YPolygon(p0, p1, p2, -(p1-p0).cross(p2-p0)));
	
	/*mesh_pos_a = pos_a;
	mesh_pos_b = pos_b;
	mesh_pos_c = pos_c;*/
}


//Green::Green(const Green& src)
//{
//	mesh_pos_a = src.mesh_pos_a;
//	mesh_pos_b = src.mesh_pos_b;
//	mesh_pos_c = src.mesh_pos_c;
//}

//Object Green::LoadObj(const char* path)
//{
//	std::ifstream file(path);
//	if (!file.is_open()) {
//		std::cerr << "Could not open file " << path << std::endl;
//		return Object();
//	}
//
//	std::vector<YPolygon> polygons;
//
//	std::string line;
//	while (std::getline(file, line)) {
//		std::istringstream iss(line);
//		std::string type;
//	}
//}


void Green::DrawGreen(){

	m_polys[0].DrawMesh();

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

	////glColor3d(0.4, 0.7, 0.15);
	//glBegin(GL_TRIANGLES);

	//std::cout << mesh_pos_a << "\n" << mesh_pos_b << "\n" << mesh_pos_c << "\n\n\n";
	//
	//glVertex3fv(mesh_pos_a.data()); 
	//glVertex3fv(mesh_pos_b.data());
	//glVertex3fv(mesh_pos_c.data());

	//glEnd();

}
