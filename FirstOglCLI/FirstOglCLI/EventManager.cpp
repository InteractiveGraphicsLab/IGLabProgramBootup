#include "pch.h"
#include "EventManager.h"
#include <iostream>
#include <random>
#define R 0.57/2//�������Ȃ�Ƃ�����

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
	graspedBallIdx = -1;
	m_isL = m_isR = m_isM = false;
	glEnable(GL_LIGHTING);//������L���ɂ���
	glEnable(GL_LIGHT0);//����(0~8�܂ł���)��L���ɂ���ݒ�
	glEnable(GL_COLOR_MATERIAL);//���̂̎�����L���ɂ���ݒ�
	float light0_position[4] = { 0.0, 10000.0, 0.0, 1.0 };//�����̈ʒu
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_DEPTH_TEST);//�[�x���𔽉f
	rayPos = EVec3f::Zero();
	hitPos = EVec3f::Zero();
	rayDir = EVec3f::Zero();
	//����Ȃ��S�~��z�u���Ȃ��ƁA���W�ϊ��������Ȃ�?
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
	Restart();
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
	//�v���~�e�B�u�I�u�W�F�N�g��`�ʂ���
	for (auto& object : objects)
	{
		object->Draw();
	}
	//�{�[���������Ă���Ƃ��̃{�[���ƃ}�E�X���Ȃ���
	if (graspedBallIdx != -1)
	{
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3fv(rayPos.data());
		glVertex3fv(hitPos.data());
	}
	glEnd();
	std::cout << hitDist << std::endl;
}

/// <summary>
/// ���N���b�N���̏���
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="ogl"></param>
void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  EVec3f rayPos = EVec3f(0,0,0);
  EVec3f rayDir = EVec3f(0, 0, 0);
  //�}�E�X�̈ʒu��ray���擾,z�����Ɋւ��Ă͐[�x0.2 to 0.01�̕����ŌŒ�
  ogl->GetCursorRay(x,y,rayPos,rayDir);
  for (int i = 0; i < objects.size(); i++)
  {
	  if (objects[i]->shapeType == 0)//���̂̂Ƃ�
	  {
		  //�}�E�X�ƃ{�[�����Փ˂��邩�ǂ������m
		  if (objects[i]->IsHit(rayPos,rayDir))
		  {
			  Ball* ball;
			  ball = dynamic_cast<Ball*>(objects[i].get());
			  //ray�͎��_rayPos�ƕ���rayDir��p���āAp(t) = rayPos + t * rayDir�ƕ\�������
			  //�K�؂�t�����߂�ƁA���Ƃ̏Փˈʒu�����܂�
			  hitPos = rayPos + ball->GetHitDist(rayPos,rayDir) * rayDir;
			  hitDist = ball->GetHitDist(rayPos,rayDir);
			  graspedBallIdx = i;//�������ꂽ�I�u�W�F�N�g��ID
		  }
	  }
  }
  std::cout << graspedBallIdx << std::endl;
  //�{�[���������Ă��Ȃ�������
  if (graspedBallIdx == -1)
  {
	  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGL�̎��_����]�����鏀��
  }
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

  if (graspedBallIdx != -1)
  {
	  EVec3f releasePos = rayPos + hitDist * rayDir;
	  EVec3f tmpforce = hitPos - releasePos;
	  //z�������̗͂�0�ɂ���
	  EVec3f force = EVec3f(tmpforce[0], tmpforce[1], 0);
	  force *= 30;
	  std::cout << force << std::endl;
	  pipeLine.AdaptForce(objects[graspedBallIdx]->transform, objects[graspedBallIdx]->rigidbody,force, 0.2);
	  graspedBallIdx = -1;
  }
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
	if (graspedBallIdx == -1)
	{
		ogl->MouseMove(EVec2i(x, y));
	}
	if (!m_isL && !m_isR && !m_isM)
	{
		return;
	}
	//���N���b�N���̃h���b�O����
	else if(m_isL && !m_isR && !m_isM)
	{
		ogl->GetCursorRay(x,y,rayPos,rayDir);
		return;
	}
}


/// <summary>
/// �{�^��1����������S�ẴI�u�W�F�N�g�ɊO�͂�������
/// </summary>
void EventManager::OnButton1Click()
{
	Restart();
}

void EventManager::Restart()
{
	objects.clear();
	//����Ȃ��S�~��z�u���Ȃ��ƁA���W�ϊ��������Ȃ�?
	objects.push_back(std::make_unique<Floor>(0.01, 0.01, 0.01));
	//���̔z�u
	auto leg1 = std::make_unique<Floor>(1, 1, BOARD_TALL);
	leg1->SetPosition(0, 0, BOARD_TALL / 2);
	//leg1->SetColor(brown);
	auto leg2 = std::make_unique<Floor>(1, 1, BOARD_TALL);
	leg2->SetPosition(BOARD_WIDTH, 0, BOARD_TALL / 2);
	//leg2->SetColor(brown);
	auto leg3 = std::make_unique<Floor>(1, 1, BOARD_TALL);
	leg3->SetPosition(BOARD_WIDTH, BOARD_HEIGHT, BOARD_TALL / 2);
	//leg3->SetColor(brown);
	auto leg4 = std::make_unique<Floor>(1, 1, BOARD_TALL);
	leg4->SetPosition(0, BOARD_HEIGHT, BOARD_TALL / 2);
	//leg4->SetColor(brown);
	auto board = std::make_unique<Floor>(BOARD_WIDTH, BOARD_HEIGHT, BOARD_THIN);
	board->SetPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2, BOARD_TALL);
	board->rigidbody.e = 0.25;
	//WIDTH�̕�
	auto board_part1 = std::make_unique<Floor>(BOARD_WIDTH, BOARD_THIN, BOARD_THIN * 2);
	board_part1->SetPosition(BOARD_WIDTH / 2, 0, BOARD_TALL + BOARD_THIN);
	auto board_part2 = std::make_unique<Floor>(BOARD_WIDTH, BOARD_THIN, BOARD_THIN * 2);
	board_part2->SetPosition(BOARD_WIDTH / 2, BOARD_HEIGHT, BOARD_TALL + BOARD_THIN);
	//HEIGHT�̕�
	auto board_part3 = std::make_unique<Floor>(BOARD_THIN, BOARD_HEIGHT, BOARD_THIN * 2);
	board_part3->SetPosition(BOARD_WIDTH, BOARD_HEIGHT / 2, BOARD_TALL + BOARD_THIN);
	auto board_part4 = std::make_unique<Floor>(BOARD_THIN, BOARD_HEIGHT, BOARD_THIN * 2);
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
	//�{�[���̔z�u
	auto ball = std::make_unique<Ball>();
	ball->SetPosition(3 * BOARD_WIDTH / 4, BOARD_HEIGHT / 2, BOARD_TALL + BOARD_THIN);
	auto ball1 = std::make_unique<Ball>();
	ball1->SetPosition(BOARD_WIDTH / 4 - 2 * R, BOARD_HEIGHT / 2 + R, BOARD_TALL + BOARD_THIN);
	auto ball2 = std::make_unique<Ball>();
	ball2->SetPosition(BOARD_WIDTH / 4 - 2 * R, BOARD_HEIGHT / 2 - R, BOARD_TALL + BOARD_THIN);
	auto ball3 = std::make_unique<Ball>();
	ball3->SetPosition(BOARD_WIDTH / 4 - 4 * R, BOARD_HEIGHT / 2 + 2 * R, BOARD_TALL + BOARD_THIN);
	auto ball4 = std::make_unique<Ball>();
	ball4->SetPosition(BOARD_WIDTH / 4 - 4 * R, BOARD_HEIGHT / 2, BOARD_TALL + BOARD_THIN);
	auto ball7 = std::make_unique<Ball>();
	ball7->SetPosition(BOARD_WIDTH / 4 - 4 * R, BOARD_HEIGHT / 2 - 2 * R, BOARD_TALL + BOARD_THIN);
	auto ball5 = std::make_unique<Ball>();
	ball5->SetPosition(BOARD_WIDTH / 4 - 6 * R, BOARD_HEIGHT / 2 + R, BOARD_TALL + BOARD_THIN);
	auto ball6 = std::make_unique<Ball>();
	ball6->SetPosition(BOARD_WIDTH / 4 - 6 * R, BOARD_HEIGHT / 2 - R, BOARD_TALL + BOARD_THIN);
	auto ball8 = std::make_unique<Ball>();
	ball8->SetPosition(BOARD_WIDTH / 4 - 8 * R, BOARD_HEIGHT / 2, BOARD_TALL + BOARD_THIN);
	auto ball9 = std::make_unique<Ball>();
	ball9->SetPosition(BOARD_WIDTH / 4, BOARD_HEIGHT / 2, BOARD_TALL + BOARD_THIN);
	objects.push_back(std::move(ball));
	objects.push_back(std::move(ball1));
	objects.push_back(std::move(ball2));
	objects.push_back(std::move(ball3));
	objects.push_back(std::move(ball4));
	objects.push_back(std::move(ball5));
	objects.push_back(std::move(ball6));
	objects.push_back(std::move(ball7));
	objects.push_back(std::move(ball8));
	objects.push_back(std::move(ball9));
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
	static EVec3f gravity = { 0,0,0 };
	for (auto& object : objects)
	{
		pipeLine.AdaptForce(object->transform, object->rigidbody, gravity, 0.2);
	}
	pipeLine.DetectCollisions(objects);
	//TODO�S���\���o�[�K�{
	pipeLine.Integrate(objects, 0.033);
}
