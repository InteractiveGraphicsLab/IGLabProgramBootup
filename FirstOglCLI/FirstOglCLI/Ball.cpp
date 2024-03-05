#include "pch.h"
#include "Ball.h"
#include "OglForCLI.h"
#include "EventManager.h"
#define N 20.0f       //���������ۂ̕�����
#define M_PI 3.141592 //�~����
#define R 0.2f        //���̔��a
#define DT 0.01f      //step��1�t���[��������̎��Ԃ�����
#define G -9.8f       //�d�͉����x
#define E 0.8f        // �����W��

Ball::Ball() {
}

Ball::~Ball() {

}

//���W���Z�b�g
void Ball::setPos(EVec3d pos)
{
	pos_ << pos;
}

//���x���Z�b�g
void Ball::setVelocity(EVec3d v)
{
	v_ << v;
}

//dt�b��̑��x���v�Z
EVec3d Ball::CalcVelocity(EVec3d v)
{
	//v[0] = v[0];
	v[1] += G * DT; // vy�ɏd�͉����x���l��
	//v[2] = 

	if (v[1] < 0 && getPos()[1] <= R ) { // ���Ƃ̏Փ˔��� (Vy�������̂ݓK��)
		v[1] *= -E; // ���x���t����e�{��
	}

	return v;
}

//���S���W���擾
EVec3d Ball::getPos()
{
	return pos_;
}

//���x���擾
EVec3d Ball::getVelocity()
{
	return v_;
}

void Ball::Draw() {
	glBegin(GL_TRIANGLES);
	for (int j = 0; j < N; j++) 
	{
		for (int i = 0; i < N; i++) 
		{
			// theta��N����
			float t1 =   i   / N * 2 * M_PI;
			float t2 = (i+1) / N * 2 * M_PI;
			// phi��N����
			float p1 =   j   / N * 2 * M_PI - M_PI;
			float p2 = (j+1) / N * 2 * M_PI - M_PI;
			//�O�p�`1��
			glNormal3d(cos(t1) * cos(p1), sin(t1) * cos(p1), sin(p1));
			glVertex3d(R * cos(t2) * cos(p1) + pos_[0], R * sin(t2) * cos(p1) + pos_[1], R * sin(p1) + pos_[2]);
			glVertex3d(R * cos(t1) * cos(p2) + pos_[0], R * sin(t1) * cos(p2) + pos_[1], R * sin(p2) + pos_[2]);
			glVertex3d(R * cos(t1) * cos(p1) + pos_[0], R * sin(t1) * cos(p1) + pos_[1], R * sin(p1) + pos_[2]);
			//�O�p�`�Q��
			glNormal3d(cos(t1) * cos(p1), sin(t1) * cos(p1), sin(p1));
			glVertex3d(R * cos(t1) * cos(p2) + pos_[0], R * sin(t1) * cos(p2) + pos_[1], R * sin(p2) + pos_[2]);
			glVertex3d(R * cos(t2) * cos(p1) + pos_[0], R * sin(t2) * cos(p1) + pos_[1], R * sin(p1) + pos_[2]);
			glVertex3d(R * cos(t2) * cos(p2) + pos_[0], R * sin(t2) * cos(p2) + pos_[1], R * sin(p2) + pos_[2]);
		}
	}
	glEnd();
} 

void Ball::Step()
{
	
	pos_[0] += v_[0] * DT;
	pos_[1] += v_[1] * DT + (1/2) * G * DT * DT; 
	pos_[2] += v_[2] * DT;
}