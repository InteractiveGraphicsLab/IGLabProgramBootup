#include "pch.h"
#include "Billiard.h"

Billiard::Billiard() 
{
	_pos   = EVec3f(0, 0, 0);
	_size  = EVec3f(10, 3, 15);
	_leftPos  = _pos[0] - _size[0] / 2.0f;
	_rightPos = _pos[0] + _size[0] / 2.0f;
	_frontPos = _pos[2] - _size[2] / 2.0f;
	_backPos  = _pos[2] + _size[2] / 2.0f;
	_floorPos = _pos[1];
}


void Billiard::Draw() 
{
	DrawBilliardBord();
}


float Billiard::GetLeftWallPos() 
{
	return _leftPos;
}


float Billiard::GetRightWallPos()
{
	return _rightPos;
}


float Billiard::GetFrontWallPos()
{
	return _frontPos;
}


float Billiard::GetBackWallPos()
{
	return _backPos;
}


void Billiard::DrawBilliardBord()
{
	glEnable(GL_DEPTH_TEST);
	//Material 
	float  shin[1] = { 64 };
	EVec4f spec(1, 1, 1, 0.5);
	EVec4f diff(0.5f, 0.5f, 0.5f, 0.5f);
	EVec4f ambi(0.5f, 0.5f, 0.5f, 0.5f);
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ambi.data());
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, shin);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	//���_
	EVec3f p1 = { _pos[0] + _size[0] / 2.0f, 0 , _pos[2] + _size[2] / 2.f }; //�E��
	EVec3f p2 = { _pos[0] + _size[0] / 2.0f, 0 , _pos[2] - _size[2] / 2.f }; //�E��
	EVec3f p3 = { _pos[0] - _size[0] / 2.f, 0 , _pos[2] - _size[2] / 2.f }; //����
	EVec3f p4 = { _pos[0] - _size[0] / 2.f, 0 , _pos[2] + _size[2] / 2.f }; //����
	
	EVec3f p5 = { _pos[0] + _size[0] / 2.f, _size[1] , _pos[2] + _size[2] / 2.f }; //�E��
	EVec3f p6 = { _pos[0] + _size[0] / 2.f, _size[1] , _pos[2] - _size[2] / 2.f }; //�E��
	EVec3f p7 = { _pos[0] - _size[0] / 2.f, _size[1] , _pos[2] - _size[2] / 2.f }; //����
	EVec3f p8 = { _pos[0] - _size[0] / 2.f, _size[1] , _pos[2] + _size[2] / 2.f }; //����

	glBegin(GL_TRIANGLES);
	
	//floar
	glVertex3d(p1[0],p1[1],p1[2]);
	glVertex3d(p2[0],p2[1],p2[2]);
	glVertex3d(p3[0],p3[1],p3[2]);

	glVertex3d(p1[0],p1[1],p1[2]);
	glVertex3d(p3[0],p3[1],p3[2]);
	glVertex3d(p4[0],p4[1],p4[2]);
	

	//rightwall
	glVertex3d(p1[0], p1[1], p1[2]);
	glVertex3d(p2[0], p2[1], p2[2]);
	glVertex3d(p6[0], p6[1], p6[2]);

	glVertex3d(p1[0], p1[1], p1[2]);
	glVertex3d(p5[0], p5[1], p5[2]);
	glVertex3d(p6[0], p6[1], p6[2]);


	//frontwall
	glVertex3d(p2[0], p2[1], p2[2]);
	glVertex3d(p3[0], p3[1], p3[2]);
	glVertex3d(p7[0], p7[1], p7[2]);

	glVertex3d(p2[0], p2[1], p2[2]);
	glVertex3d(p6[0], p6[1], p6[2]);
	glVertex3d(p7[0], p7[1], p7[2]);
	

	//leftwall
	glVertex3d(p3[0], p3[1], p3[2]);
	glVertex3d(p7[0], p7[1], p7[2]);
	glVertex3d(p8[0], p8[1], p8[2]);

	glVertex3d(p3[0], p3[1], p3[2]);
	glVertex3d(p4[0], p4[1], p4[2]);
	glVertex3d(p8[0], p8[1], p8[2]);


	//backwall
	glVertex3d(p1[0], p1[1], p1[2]);
	glVertex3d(p4[0], p4[1], p4[2]);
	glVertex3d(p8[0], p8[1], p8[2]);
	
	glVertex3d(p1[0], p1[1], p1[2]);
	glVertex3d(p5[0], p5[1], p5[2]);
	glVertex3d(p8[0], p8[1], p8[2]);

	glEnd();


}




