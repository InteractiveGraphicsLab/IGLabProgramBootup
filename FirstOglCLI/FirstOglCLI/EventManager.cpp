#include <math.h>
#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "Box.h"



EventManager::EventManager()
{
	m_isL = m_isR = m_isM = false;

	// ��
	m_balls.push_back(Ball(EVec3f(16.0f, 2.0f, 40.0f), EVec3f(0.0f, 0.0f, 300.0f)));
	m_balls.push_back(Ball(EVec3f(16.0f, 2.0f, 24.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(14.0f, 2.0f, 20.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(18.0f, 2.0f, 20.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(12.0f, 2.0f, 16.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(16.0f, 2.0f, 16.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(20.0f, 2.0f, 16.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(10.0f, 2.0f, 12.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(14.0f, 2.0f, 12.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(18.0f, 2.0f, 12.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(22.0f, 2.0f, 12.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f( 8.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(12.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(16.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(20.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(24.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));

	//���̑傫����ݒ�
	EVec3f max1 = { 31.0f, 10.0f, 46.0f }, min1 = { 0.0f, 0.0f, 0.0f };
	box1_.setMax(max1);
	box1_.setMin(min1);

}


void EventManager::DrawScene()
{
	glEnable(GL_DEPTH_TEST);
	//��������
	box1_.Draw();

	glBegin(GL_LINES);
		glVertex3fv(rayp_.data()); //glVertex3f(rayp_[0], rayp_[1], rayp_[2]);
		EVec3f tmp = rayp_ + 10.0f * rayd_;
		glVertex3fv(tmp.data());
	glEnd();

	//�d�C������
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	//����`��
	for (int i = 0; i < m_balls.size(); i++) {
		m_balls[i].Draw();
	}

	//�d�C������
	glDisable(GL_LIGHTING);

}	

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
	// �N���b�N�Ń��C���΂�
	EVec3f p, d;
	ogl->GetCursorRay(EVec2i(x, y), p, d);
	rayp_ = p; // �n�_(���_)p�̍��W ?
	rayd_ = d; // �����x�N�g��d ?

	m_isL = true;
	ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGL�̎��_����]�����鏀��

	// ���C�ŊO�͂�������
	EVec3f velocity_after;
	float discriminant; // ���ʎ�
	for (int i = 0; i < m_balls.size(); i++) {
		// D = (d, p - pos)^2 - (||p - pos||^2 - r^2)�@���v�Z
		discriminant = pow(d.dot(p - m_balls[i].getPos()), 2) - (pow((p - m_balls[i].getPos()).norm(), 2) - pow(m_balls[i].getRadius(), 2)); 
		if (discriminant > 0) {
			velocity_after += 10.0f * d;
			m_balls[i].setVelocity(velocity_after);
		}
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


//�����m�̏Փ˔���
bool EventManager::isCollision(const int& n1, const int& n2)
{
	float t = m_balls[n1].getRadius() + m_balls[n2].getRadius();
	if ((m_balls[n1].getPos() - m_balls[n2].getPos()).norm() <= t) {
		return true; // �Փ˂���
	}
	else { 
		return false; // �Փ˂Ȃ�
	}
}


/*
//�����m�̏Փ˔���
bool EventManager::isCollision(const int& n1, const int& n2)
{
	float t = m_balls[n1].getRadius() + m_balls[n2].getRadius();
	if ((m_balls[n1].getPos() - m_balls[n2].getPos()).norm() <= t && m_balls[n1].getCollision() == false && m_balls[n2].getCollision() == false) {
		m_balls[n1].setCollision(true);
		m_balls[n2].setCollision(true);
		return true; // �Փ˂���
	}
	else if ((m_balls[n1].getPos() - m_balls[n2].getPos()).norm() <= t && (m_balls[n1].getCollision() == true || m_balls[n2].getCollision() == true)) { // �ڐG���ɐڐG
		return false;
	}
	else { //���ꂽ��
		m_balls[n1].setCollision(false);
		m_balls[n2].setCollision(false);
		return false; // �Փ˂��Ȃ�
	}
}
*/

// �����m�Փˎ��̑��x���X�V
void EventManager::UpdateVelocity(const int& n1, const int& n2)
{
	float E = 0.99f;
	EVec3f v1_before = m_balls[n1].getVelocity();
	EVec3f v2_before = m_balls[n2].getVelocity();
	EVec3f v1_parallel_before, v2_parallel_before, v1_vertical, v2_vertical; //�Փ˂ɑ΂��Đ��������͕ω����Ȃ�
	EVec3f pos1 = m_balls[n1].getPos(), pos2 = m_balls[n2].getPos();
	EVec3f p = pos1 - pos2;

	// ���ˉe��p����v_before�̕��s���������߂�
	v1_parallel_before = v1_before.dot(p) / pow(p.norm(), 2) * p;
	v2_parallel_before = v2_before.dot(p) / pow(p.norm(), 2) * (p); // p? -p?

	v1_vertical = v1_before - v1_parallel_before;
	v2_vertical = v2_before - v2_parallel_before;

	EVec3f v1_parallel_after = (1.0f - E) / 2.0f * v1_parallel_before + (1.0f + E) / 2.0f * v2_parallel_before;
	EVec3f v2_parallel_after = (1.0f + E) / 2.0f * v1_parallel_before + (1.0f - E) / 2.0f * v2_parallel_before;

	// ���s�����Ɛ�������������
	EVec3f v1_after = v1_parallel_after + v1_vertical;
	EVec3f v2_after = v2_parallel_after + v2_vertical;
	m_balls[n1].setVelocity(v1_after);
	m_balls[n2].setVelocity(v2_after);

	/*
	// �A���Փ˂�����邽�߂�pos���X�V
	pos1 += 0.01f * v1_after;
	pos2 += 0.01f * v2_after;
	m_balls[n1].setPos(pos1);
	m_balls[n2].setPos(pos2);
	*/
}

void EventManager::Step()
{

	float dt = 0.01f;
	
	
	for (int i = 0; i < m_balls.size(); i++) {
		m_balls[i].Step();
	}
	
	
	float E = 0.9f; //�ǂ̔����W��
	for (int i = 0; i < m_balls.size(); i++) {
		//�����ǂƏՓ�
		EVec3f distance1 = m_balls[i].getPos() - box1_.getMin(); // ���ƕ�min�̋���
		EVec3f distance2 = box1_.getMax() - m_balls[i].getPos(); // ���ƕ�max�̋���
		EVec3f vi = m_balls[i].getVelocity();
		if ((distance1[0] <= m_balls[i].getRadius() && vi[0] < 0) || (distance2[0] <= m_balls[i].getRadius() && vi[0] > 0)) {
			vi[0] *= -E;
		}
		if ((distance1[1] <= m_balls[i].getRadius() && vi[1] < 0)) { // �V��Ƃ̏Փ˂͖�������
			vi[1] *= -E;
		}
		if ((distance1[2] <= m_balls[i].getRadius() && vi[2] < 0) || (distance2[2] <= m_balls[i].getRadius() && vi[2] > 0)) {
			vi[2] *= -E;
		}
		m_balls[i].setVelocity(vi);

		//�����m�̏Փ�
		for (int j = i + 1; j < m_balls.size(); j++)
		{
			if (isCollision(i, j) == true)
				UpdateVelocity(i, j);
		}

	}
}



/* ���W��
	//x:red, y:green, z:blue
	glLineWidth(2.0f);
	glDisable(GL_LIGHTING);//�d�C������

	//OpenGL��3�{�̒�����`��
	glBegin(GL_LINES);
	glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
	glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
	glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
	glEnd();

 //���C�Ƌ��̐ڐG����
bool isRayHit(const Ball& b1, const EVec3f& ray_d)
{
	EVec3f diff = b1.getPos() - ray_d; 
	if (diff.norm() <= b1.getRadius())
		return true;
}
	*/