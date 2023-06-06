#include "pch.h"
#include "Green.h"
#include "OglForCLI.h"
#include "Green.h"
#include <fstream>
#include <iostream>
#include <string>

#define M_PI 3.141592

Green::Green()
{
	m_polys = std::vector<YPolygon>(0);

	/*EVec3f p0 = EVec3f(16.0f, 0, 4.0f);
	EVec3f p1 = EVec3f(-14.0f, -7.0f, -1.0f);
	EVec3f p2 = EVec3f(-14.0f, 7.0f, -1.0f);

	m_polys.push_back(YPolygon(p0, p1, p2, (p1-p0).cross(p2-p0)));*/
	
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


//Split関数
static std::vector<std::string> Split(const std::string& str, const std::string& sep)
{
	std::vector<std::string> list;  //返す文字列
	int offset;						//一つ前のsepの位置
	std::string::size_type pos;		//sepの発見位置

	if (sep.length() == 0) {
		list.push_back(str);
	}
	else {
		offset = std::string::size_type(0);	//offset初期化(0)
		while (1) {
			pos = str.find(sep, offset);	//offsetの位置からsepの場所を探す
			if (pos == std::string::npos) {		//sepを発見できなくなったら(つまり次が最後の要素)
				list.push_back(str.substr(offset));	//最後の要素をlistに追加してbreak;
				break;
			}
			list.push_back(str.substr(offset, pos - offset));	//offsetからposまで文字列をlistに追加
			offset = pos + sep.length();	//offsetを更新
		}
	}

	return list;

}


bool Green::LoadObj(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Could not open file: " << path << std::endl;
		return false;
	}

	std::vector<EVec3f> vs;
	std::vector<EVec3f> vns;

	std::string line;
	while (std::getline(file, line)) {
		//std::istringstream iss(line);
		//std::string type;

		std::vector<std::string> data = Split(line, " ");

		if (data[0] == "v") //頂点格納
		{
			double x = std::stof(data[1]) * 50;
			double y = (cos(M_PI / 2) * std::stof(data[2]) - sin(M_PI / 2) * std::stof(data[3])) * 50;
			double z = (sin(M_PI / 2) * std::stof(data[2]) + cos(M_PI / 2) * std::stof(data[3])) * 50 - 10.0f;

			vs.push_back(EVec3f(x, y, z));
		}
		//else if (data[0], "vt") == 0)
		//{
		//	EVec2f vt;
		//	int matches = fscanf(file, "%f %f\n", &vt[0], &vt[1]);
		//	m_vt.push_back(vt);
		//}
		else if (data[0] == "vn")
		{
			vns.push_back(EVec3f(std::stod(data[1]), std::stod(data[2]), std::stod(data[3])));
		}
		else if (data[0] == "f")
		{
					
			std::vector<std::string> p1 = Split(data[1], "//");
			std::vector<std::string> p2 = Split(data[2], "//");
			std::vector<std::string> p3 = Split(data[3], "//");

			EVec3i fv(std::stoi(p1[0])-1, std::stoi(p2[0])-1, std::stoi(p3[0])-1);
			EVec3i fn(std::stoi(p1[1])-1, std::stoi(p2[1])-1, std::stoi(p3[1])-1);
			
			//EVec3f normal = (vns[fn[0]] + vns[fn[1]] + vns[fn[2]]) / 3;
			EVec3f normal = (vs[fv[1]] - vs[fv[0]]).cross(vs[fv[2]] - vs[fv[0]]);

			m_polys.push_back(YPolygon(vs[fv[0]], vs[fv[1]], vs[fv[2]], normal.normalized()));
		}
	}
}


void Green::DrawGreen(){

	for (int i = 0; i < m_polys.size(); ++i) {
		m_polys[i].DrawMesh();
	}

	//glEnable(GL_DEPTH_TEST);
	////Material 
	//float   shin[1] = { 64 };
	//EVec4f  spec(1, 1, 1, 0.5);
	//EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f); //色調整
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
