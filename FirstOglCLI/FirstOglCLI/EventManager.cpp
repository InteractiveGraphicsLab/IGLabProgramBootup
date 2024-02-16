#include "pch.h"
#include "EventManager.h"
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}

//�P�ʂ�*10������cm
const float BOARD_WIDTH = 29;
const float BOARD_HEIGHT = 16;
const float BOARD_TALL = 8;
const float BOARD_THIN = 1;
/// <summary>
/// ���������s��
/// </summary>
EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  glEnable(GL_LIGHTING);//������L���ɂ���
  glEnable(GL_LIGHT0);//����(0~8�܂ł���)��L���ɂ���ݒ�
  glEnable(GL_COLOR_MATERIAL);//���̂̎�����L���ɂ���ݒ�
  float light0_position[4] = { 0.0, 10000.0, 0.0, 1.0 };//�����̈ʒu
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glEnable(GL_DEPTH_TEST);//�[�x���𔽉f
  //����Ȃ��S�~��z�u���Ȃ��ƁA���W�ϊ��������Ȃ�
  objects.push_back(std::make_unique<Floor>(0.01,0.01,0.01));
  //���̔z�u
  auto leg1 = std::make_unique<Floor>(1, 1, BOARD_TALL);
  leg1->SetPosition(0,0, BOARD_TALL/2);
  //leg1->SetColor(brown);
  auto leg2 = std::make_unique<Floor>(1, 1, BOARD_TALL);
  leg2->SetPosition(BOARD_WIDTH,0, BOARD_TALL / 2);
  //leg2->SetColor(brown);
  auto leg3 = std::make_unique<Floor>(1, 1, BOARD_TALL);
  leg3->SetPosition(BOARD_WIDTH,BOARD_HEIGHT, BOARD_TALL / 2);
  //leg3->SetColor(brown);
  auto leg4 = std::make_unique<Floor>(1, 1, BOARD_TALL);
  leg4->SetPosition(0,BOARD_HEIGHT, BOARD_TALL / 2);
  //leg4->SetColor(brown);
  auto board = std::make_unique<Floor>(BOARD_WIDTH, BOARD_HEIGHT, BOARD_THIN);
  board->SetPosition(BOARD_WIDTH/2,BOARD_HEIGHT/2,BOARD_TALL);
  board->rigidbody.e = 0.25;
  //WIDTH�̕�
  auto board_part1 = std::make_unique<Floor>(BOARD_WIDTH, BOARD_THIN, BOARD_THIN*2);
  board_part1->SetPosition(BOARD_WIDTH/2, 0, BOARD_TALL + BOARD_THIN);
  auto board_part2 = std::make_unique<Floor>(BOARD_WIDTH, BOARD_THIN, BOARD_THIN*2);
  board_part2->SetPosition(BOARD_WIDTH / 2, BOARD_HEIGHT, BOARD_TALL + BOARD_THIN);
  //HEIGHT�̕�
  auto board_part3 = std::make_unique<Floor>(BOARD_THIN, BOARD_HEIGHT, BOARD_THIN*2);
  board_part3->SetPosition(BOARD_WIDTH , BOARD_HEIGHT / 2, BOARD_TALL + BOARD_THIN);
  auto board_part4 = std::make_unique<Floor>(BOARD_THIN, BOARD_HEIGHT, BOARD_THIN*2);
  board_part4->SetPosition(0, BOARD_HEIGHT / 2, BOARD_TALL + BOARD_THIN);
  objects.push_back(std::move(leg1));
  objects.push_back(std::move(leg2));
  objects.push_back(std::move(leg3));
  objects.push_back(std::move(leg4));
  objects.push_back(std::move(board));
  objects.push_back(std::move(board_part1));
  objects.push_back(std::move(board_part2));
  objects.push_back(std::move(board_part3));
  objects.push_back(std::move(board_part4));
  //objects.push_back(std::make_unique<Ball>());
}

void EventManager::DrawScene()
{
	glEnable(GL_DEPTH_TEST);//�[�x���𔽉f
	glLineWidth(2.0f);
	//OpenGL��3�{�̒�����`��
	glBegin(GL_LINES);
	glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
	glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
	glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
	//glEnable(GL_DEPTH_TEST);
	const static float diff[4] = { 1.0f, 0.2f, 0, 0.3f };
	const static float ambi[4] = { 1.0f, 0.2f, 0, 0.3f };
	const static float spec[4] = { 1,1,1,0.3f };
	const static float shin[1] = { 64.0f };
	const static float diffG[4] = { 0.4f, 1.0f, 0.4f, 0.3f };
	const static float ambiG[4] = { 0.4f, 1.0f, 0.4f, 0.3f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffG);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiG);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

	//render floor 
	glEnable(GL_CULL_FACE);
	//�{�[���̕`�ʂ��s������
	for (auto& object : objects)
	{
		//SetColr(object->c);//�ݒ肳�ꂽ�F
		object->Draw();
	}
	glEnd();
}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGL�̎��_����]�����鏀��
}

void EventManager::MBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isM = true;
  ogl->BtnDown_Zoom(EVec2i(x, y));
}

void EventManager::RBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isR = true;
  ogl->BtnDown_Rot(EVec2i(x, y));
}

void EventManager::LBtnUp(int x, int y, OglForCLI* ogl)
{
  m_isL = false;
  ogl->BtnUp();
}

void EventManager::MBtnUp(int x, int y, OglForCLI* ogl)
{
  m_isM = false;
  ogl->BtnUp();
}

void EventManager::RBtnUp(int x, int y, OglForCLI* ogl)
{
  m_isR = false;
  ogl->BtnUp();
}

void EventManager::MouseMove(int x, int y, OglForCLI* ogl)
{
  if (!m_isL && !m_isR && !m_isM) return;
  ogl->MouseMove(EVec2i(x, y));
}


/// <summary>
/// �{�^��1����������S�ẴI�u�W�F�N�g�ɊO�͂�������
/// </summary>
void EventManager::OnButton1Click()
{
	EVec3f power = {0,15,0};
	for (auto& object : objects)
	{
		pipeLine.AdaptForce(object->transform,object->rigidbody,power,0.2);
	}
}

/// <summary>
/// �{�^��2�����������̃��\�b�h,�{�^���𐶐�����
/// </summary>
void EventManager::OnButton2Click()
{
	EVec3f power = { 15,0,0 };
	for (auto& object : objects)
	{
		pipeLine.AdaptForce(object->transform, object->rigidbody, power, 0.2);
	}
}

/// <summary>
/// �{�^��3�����������̃��\�b�h,�{�^���𐶐�����
/// </summary>
void EventManager::OnButton3Click()
{
	auto ball = std::make_unique<Ball>();
	ball->SetPosition(BOARD_WIDTH / 2 + 10 + random(-3,3), BOARD_HEIGHT / 2 + random(-3,3), BOARD_TALL + BOARD_THIN + 2);
	EVec3f power = {0,-50,-100 };
	pipeLine.AdaptForce(ball->transform, ball->rigidbody, power, 0.2);
	objects.push_back(std::move(ball));
}

/// <summary>
/// 1�t���[���Ŏ��s����郁�\�b�h
/// </summary>
void EventManager::Step()
{
	//�d��
	static EVec3f gravity = { 0,0,-2 };
	for (auto& object : objects)
	{
		pipeLine.AdaptForce(object->transform, object->rigidbody, gravity, 0.2);
	}
	pipeLine.DetectCollisions(objects);
	//�S���\���o�[�K�{
	pipeLine.Integrate(objects, 0.033);
}
