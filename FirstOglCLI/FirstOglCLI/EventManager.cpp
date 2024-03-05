#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "Box.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  //���̑傫����ݒ�
  EVec3d max1 = { 20.0f, 8.0f, 20.0f }, min1 = { 0.0f, 0.0f, 0.0f };
  box1_.setMax(max1);
  box1_.setMin(min1);

  //���̏����ʒu���Z�b�g
  EVec3d pos1 = { 1.0f, 2.0f, 3.0f }, pos2 = { 2.0f, 3.0f, 4.0f }, pos3 = { 3.0f, 4.0f, 5.0f };
  b1_.setPos(pos1);
  b2_.setPos(pos2);
  b3_.setPos(pos3);

  //���̏������Z�b�g
  EVec3d v1 = { 20.0f, 20.0f, 20.0f }, v2 = { 30.0f, 30.0f, 30.0f }, v3 = { 40.0f, 40.0f, 40.0f };
  b1_.setVelocity(v1);
  b2_.setVelocity(v2);
  b3_.setVelocity(v3);
}

//���P���ǂƏՓ˂��邩�𔻒�
EVec3d EventManager::isCollision1() 
{
	EVec3d isCollision1 = { 0, 0, 0 }; //1�̂Ƃ��Փ�

	// x���W�̏Փ˔���
	if ((b1_.getPos()[0] - box1_.getMin()[0] <= R && b1_.getVelocity()[0] < 0) || (box1_.getMax()[0] - b1_.getPos()[0] <= R)) { // (���ʂŏՓ� || �E�ʂŏՓ�)
		isCollision1[0] = 1;
	}
	else {
		isCollision1[0] = 0;
	}
	// y���W�̏Փ˔���
	if ((b1_.getPos()[1] - box1_.getMin()[1] <= R && b1_.getVelocity()[1] < 0) || (box1_.getMax()[1] - b1_.getPos()[1] <= R)) { // (���ʂŏՓ� || ��ʂŏՓ�)
		isCollision1[1] = 1;
	}
	else {
		isCollision1[1] = 0;
	}
	// z���W�̏Փ˔���
	if ((b1_.getPos()[2] - box1_.getMin()[2] <= R && b1_.getVelocity()[2] < 0) || (box1_.getMax()[2] - b1_.getPos()[2] <= R)) { // (���ʂŏՓ� || ��O�ʂŏՓ�)
		isCollision1[2] = 1;
	}
	else {
		isCollision1[2] = 0;
	}

	return isCollision1;
}

//��2���ǂƏՓ˂��邩�𔻒�
EVec3d EventManager::isCollision2()
{
	EVec3d isCollision2 = { 0, 0, 0 }; //1�̂Ƃ��Փ�

	// x���W�̏Փ˔���
	if ((b2_.getPos()[0] - box1_.getMin()[0] <= R && b2_.getVelocity()[0] < 0) || (box1_.getMax()[0] - b2_.getPos()[0] <= R)) { // (���ʂŏՓ� || �E�ʂŏՓ�)
		isCollision2[0] = 1;
	}
	else {
		isCollision2[0] = 0;
	}
	// y���W�̏Փ˔���
	if ((b2_.getPos()[1] - box1_.getMin()[1] <= R && b2_.getVelocity()[1] < 0) || (box1_.getMax()[1] - b2_.getPos()[1] <= R)) { // (���ʂŏՓ� || ��ʂŏՓ�)
		isCollision2[1] = 1;
	}
	else {
		isCollision2[1] = 0;
	}
	// z���W�̏Փ˔���
	if ((b3_.getPos()[2] - box1_.getMin()[2] <= R && b3_.getVelocity()[2] < 0) || (box1_.getMax()[2] - b3_.getPos()[2] <= R)) { // (���ʂŏՓ� || ��O�ʂŏՓ�)
		isCollision2[2] = 1;
	}
	else {
		isCollision2[2] = 0;
	}

	return isCollision2;
}

//��3���ǂƏՓ˂��邩�𔻒�
EVec3d EventManager::isCollision3()
{
	EVec3d isCollision3 = { 0, 0, 0 }; //1�̂Ƃ��Փ�

	// x���W�̏Փ˔���
	if ((b3_.getPos()[0] - box1_.getMin()[0] <= R && b3_.getVelocity()[0] < 0) || (box1_.getMax()[0] - b3_.getPos()[0] <= R)) { // (���ʂŏՓ� || �E�ʂŏՓ�)
		isCollision3[0] = 1;
	}
	else {
		isCollision3[0] = 0;
	}

	// y���W�̏Փ˔���
	if ((b3_.getPos()[1] - box1_.getMin()[1] <= R && b3_.getVelocity()[1] < 0) || (box1_.getMax()[1] - b3_.getPos()[1] <= R)) { // (���ʂŏՓ� || ��ʂŏՓ�)
		isCollision3[1] = 1;
	}
	else {
		isCollision3[1] = 0;
	}

	// z���W�̏Փ˔���
	if ((b3_.getPos()[2] - box1_.getMin()[2] <= R && b3_.getVelocity()[2] < 0) || (box1_.getMax()[2] - b3_.getPos()[2] <= R)) { // (���ʂŏՓ� || ��O�ʂŏՓ�)
		isCollision3[2] = 1;
	}
	else {
		isCollision3[2] = 0;
	}

	return isCollision3;
}



void EventManager::DrawScene()
{
  //��������
  box1_.Draw();

  //x:red, y:green, z:blue 
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//�d�C������

  //OpenGL��3�{�̒�����`��
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();

  //�d�C������
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  //����`��
  b1_.Draw();
  b2_.Draw();
  b3_.Draw();


  //�d�C������
  glDisable(GL_LIGHTING);

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


void EventManager::Step()
{
	EVec3d v1 = b1_.CalcVelocity(b1_.getVelocity()); // V1_before���擾�@���@dt�b���V1_after���v�Z
	EVec3d v2 = b2_.CalcVelocity(b2_.getVelocity()); // V2_before���擾�@���@dt�b���V2_after���v�Z
	EVec3d v3 = b3_.CalcVelocity(b3_.getVelocity()); // V3_before���擾�@���@dt�b���V3_after���v�Z
	EVec3d isHit1 = isCollision1(), isHit2 = isCollision2(), isHit3 = isCollision3(); // �֐��̌Ăяo���񐔂����炷���߂ɂ��炩���ߑ��

	//���P���ǂɏՓ˂��Ă�����
	for (int i = 0; i < 3; i++) {
		if (isHit1[i] == 1)
			v1[i] *= -E; 
	}
	//��2���ǂɏՓ˂��Ă�����
	for (int i = 0; i < 3; i++) {
		if (isHit2[i] == 1)
			v2[i] *= -E;
	}
	//��3���ǂɏՓ˂��Ă�����
	for (int i = 0; i < 3; i++) {
		if (isHit3[i] == 1)
			v3[i] *= -E;
	}

	b1_.setVelocity(v1); // ���P V_after��set
	b2_.setVelocity(v2); // ���Q
	b3_.setVelocity(v3); // ���R

	b1_.Step();//���P�̈ʒu���X�V
	b2_.Step();//���Q
	b3_.Step();//���R
}
