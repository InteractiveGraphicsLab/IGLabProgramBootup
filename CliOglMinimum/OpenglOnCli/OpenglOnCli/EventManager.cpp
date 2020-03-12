#include "stdafx.h"
#include "MainForm.h"
#include "EventManager.h"

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>





class MyVec3
{
private: 
  //ここに各変数はprivate変数になり外からは見えない
  int m_priv;
  
public: 
  //ここに各変数はpublic変数になり外から参照・修正可能
  int m_publ;

  float m_data[3];
  
  //constructrue
  MyVec3(float x = 0, float y = 0, float z = 0)
  {
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
  }

  MyVec3(const MyVec3 &src)
  {
    //todo copy
    
  }

  MyVec3 &operator=(const MyVec3 &src)
  {
    //todo copy
    return *this;
  }

  //オペレーターオーバーロード
  MyVec3 operator+(const MyVec3 &v){
    MyVec3 p;
    p.m_data[0] = this->m_data[0] + v.m_data[0];
    p.m_data[1] = this->m_data[1] + v.m_data[1];
    p.m_data[2] = this->m_data[2] + v.m_data[2];
    return p;
  }

  void Trace()
  {
    std::cout << m_data[0] << m_data[1] << m_data[2];
  }
};














EventManager::EventManager()
{
  std::cout << "EventManager constructor\n";
  MyVec3 p(1,2,3);
  MyVec3 q(1,2,3);
  auto a = p + q;
  p.Trace();
  q.Trace();
  a.Trace();

  


  m_btn_right = m_btn_left = m_btn_middle = false;
}



void EventManager::BtnDownLeft  (int x, int y, OglForCLI *ogl)
{
  m_btn_left = true;
  ogl->BtnDown_Trans( EVec2i(x,y) );
} 

void EventManager::BtnDownMiddle(int x, int y, OglForCLI *ogl)
{
  m_btn_middle = true;
  ogl->BtnDown_Zoom( EVec2i(x,y) );
}

void EventManager::BtnDownRight (int x, int y, OglForCLI *ogl)
{
  m_btn_right = true;
  ogl->BtnDown_Rot( EVec2i(x,y) );
}



void EventManager::BtnUpLeft  (int x, int y, OglForCLI *ogl)
{
  m_btn_left = false;
  ogl->BtnUp();
}

void EventManager::BtnUpMiddle(int x, int y, OglForCLI *ogl)
{
  m_btn_middle = false;
  ogl->BtnUp();
}

void EventManager::BtnUpRight (int x, int y, OglForCLI *ogl)
{
  m_btn_right = false;
  ogl->BtnUp();
}

void EventManager::MouseMove    (int x, int y, OglForCLI *ogl)
{
  if ( !m_btn_right && !m_btn_middle && !m_btn_left) return;

  ogl->MouseMove( EVec2i(x,y) );
  OpenglOnCli::MainForm_RedrawPanel();
}


static EVec3f GetPosOnSphere(const float &phi, const float &theta)
{
	return EVec3f(	cos(phi) * cos(theta),
					sin(phi),
				   -cos(phi) * sin(theta));
}

static void DrawSphere(const int reso_i, const int reso_j, const float radius)
{
	EVec3f *norms = new EVec3f[reso_i * reso_j];
	EVec3f *verts = new EVec3f[reso_i * reso_j];

	for (int i = 0; i < reso_i; ++i)
	{
		for (int j = 0; j < reso_i; ++j)
		{
			norms[j + i * reso_j] = GetPosOnSphere( M_PI * i / (reso_i - 1.0f) - M_PI / 2.0f,
												2 * M_PI * j / (reso_j - 1.0f));
			verts[j + i * reso_j] = radius * norms[j + i * reso_j];
		}
	}

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < reso_i - 1; ++i)
	{
		for (int j = 0; j < reso_j - 1; ++j)
		{
			int idx0 = reso_j * i + j,		 idx1 = reso_j * i + j + 1;
			int idx2 = reso_j * (i + 1) + j, idx3 = reso_j * (i + 1) + j + 1;
			glNormal3fv(norms[idx0].data()); glVertex3fv(verts[idx0].data());
			glNormal3fv(norms[idx2].data()); glVertex3fv(verts[idx2].data());
			glNormal3fv(norms[idx3].data()); glVertex3fv(verts[idx3].data());

			glNormal3fv(norms[idx0].data()); glVertex3fv(verts[idx0].data());
			glNormal3fv(norms[idx3].data()); glVertex3fv(verts[idx3].data());
			glNormal3fv(norms[idx1].data()); glVertex3fv(verts[idx1].data());
		}
	}
	glEnd();

	delete[] verts;
	delete[] norms;
}


//四角形を描画(配列の隣り合う要素は隣接する頂点であるように入力する)
static void DrawSquare(const EVec3f *verts){
	if (verts->size() < 3)
	{
		printf("DrawSquare : 頂点が4つ以下です．");
		return;
	}

	EVec3f v1 = verts[0] - verts[1], v2 = verts[2] - verts[1];
	EVec3f normal1 = v2.cross(v1);
	glBegin(GL_TRIANGLES);
	glNormal3f(normal1[0], normal1[1], normal1[2]);
	glVertex3fv(verts[0].data());
	glVertex3fv(verts[1].data());
	glVertex3fv(verts[2].data());
	glEnd();

	EVec3f v3 = verts[0] - verts[3], v4 = verts[2] - verts[3];
	EVec3f normal2 = v3.cross(v4);
	glBegin(GL_TRIANGLES);
	glNormal3f(normal2[0], normal2[1], normal2[2]);
	glVertex3fv(verts[0].data());
	glVertex3fv(verts[2].data());
	glVertex3fv(verts[3].data());
	glEnd();
}

//ビルヤード台を描画（xz平面の辺に高さがwall_heightの壁を付けたもの）
static void DrawBilliardTable(const EVec3f *verts, const float wall_height) {
	if (verts->size() < 3)
	{
		printf("DrawBilliardTable : 頂点が4つ以下です．");
		return;
	}

	//底面作成
	DrawSquare(verts);

	//壁作成
	EVec3f wall_verts1[4] = { verts[0], verts[1], {verts[1][0],wall_height,verts[1][2]}, {verts[0][0],wall_height,verts[0][2]} };
	EVec3f wall_verts2[4] = { verts[1], verts[2], {verts[2][0],wall_height,verts[2][2]}, {verts[1][0],wall_height,verts[1][2]} };
	EVec3f wall_verts3[4] = { verts[2], verts[3], {verts[3][0],wall_height,verts[3][2]}, {verts[2][0],wall_height,verts[2][2]} };
	EVec3f wall_verts4[4] = { verts[3], verts[0], {verts[0][0],wall_height,verts[0][2]}, {verts[3][0],wall_height,verts[3][2]} };
	DrawSquare(wall_verts1);
	DrawSquare(wall_verts2);
	DrawSquare(wall_verts3);
	DrawSquare(wall_verts4);
}

void EventManager::DrawScene(){
  //ここにレンダリングルーチンを書く
  glBegin(GL_LINES );
  glColor3d(1,0,0); glVertex3d(0,0,0); glVertex3d(10,0,0);
  glColor3d(0,1,0); glVertex3d(0,0,0); glVertex3d(0,10,0);
  glColor3d(0,0,1); glVertex3d(0,0,0); glVertex3d(0,0,10);
  glEnd();

  
  const static float diff[4] = { 1.0f, 0.2f, 0, 0.3f };
  const static float ambi[4] = { 1.0f, 0.2f, 0, 0.3f };
  const static float spec[4] = { 1,1,1,0.3f };
  const static float shin[1] = { 64.0f };

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR  , spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , ambi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
  
  //DrawSphere(20, 20, 3.0f);

  EVec3f verts[4] = { {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1} };
  //DrawSquare(verts);
  DrawBilliardTable(verts, 0.5f);

}


