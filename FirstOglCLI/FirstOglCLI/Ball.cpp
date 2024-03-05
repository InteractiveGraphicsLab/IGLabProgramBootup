#include "pch.h"
#include "Ball.h"
#include "OglForCLI.h"
#include "EventManager.h"
#define N 20.0f       //球を書く際の分割数
#define M_PI 3.141592 //円周率
#define R 0.2f        //球の半径
#define DT 0.01f      //stepの1フレームあたりの時間を仮定
#define G -9.8f       //重力加速度
#define E 0.8f        // 反発係数

Ball::Ball() {
}

Ball::~Ball() {

}

//座標をセット
void Ball::setPos(EVec3d pos)
{
	pos_ << pos;
}

//速度をセット
void Ball::setVelocity(EVec3d v)
{
	v_ << v;
}

//dt秒後の速度を計算
EVec3d Ball::CalcVelocity(EVec3d v)
{
	//v[0] = v[0];
	v[1] += G * DT; // vyに重力加速度を考慮
	//v[2] = 

	if (v[1] < 0 && getPos()[1] <= R ) { // 床との衝突判定 (Vy下向きのみ適応)
		v[1] *= -E; // 速度を逆向きe倍に
	}

	return v;
}

//中心座標を取得
EVec3d Ball::getPos()
{
	return pos_;
}

//速度を取得
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
			// thetaをN分割
			float t1 =   i   / N * 2 * M_PI;
			float t2 = (i+1) / N * 2 * M_PI;
			// phiをN分割
			float p1 =   j   / N * 2 * M_PI - M_PI;
			float p2 = (j+1) / N * 2 * M_PI - M_PI;
			//三角形1つ目
			glNormal3d(cos(t1) * cos(p1), sin(t1) * cos(p1), sin(p1));
			glVertex3d(R * cos(t2) * cos(p1) + pos_[0], R * sin(t2) * cos(p1) + pos_[1], R * sin(p1) + pos_[2]);
			glVertex3d(R * cos(t1) * cos(p2) + pos_[0], R * sin(t1) * cos(p2) + pos_[1], R * sin(p2) + pos_[2]);
			glVertex3d(R * cos(t1) * cos(p1) + pos_[0], R * sin(t1) * cos(p1) + pos_[1], R * sin(p1) + pos_[2]);
			//三角形２つ目
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