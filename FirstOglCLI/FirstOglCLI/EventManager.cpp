#include <math.h>
#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "Box.h"



EventManager::EventManager()
{
	m_isL = m_isR = m_isM = false;

	m_balls.push_back(Ball(EVec3f(5, 2, 5), EVec3f(10, 0, 30)));
	m_balls.push_back(Ball(EVec3f(5, 2, 15), EVec3f(30, 0, 10)));
	m_balls.push_back(Ball(EVec3f(15, 2, 10), EVec3f(5, 0, 30)));
	m_balls.push_back(Ball(EVec3f(15, 2, 15), EVec3f(40, 0, 80)));

	/*m_balls.push_back(Ball(EVec3f(5, 2, 5), EVec3f(0, 0, 30)));
	m_balls.push_back(Ball(EVec3f(5, 2, 45), EVec3f(0, 0, 80)));
	m_balls.push_back(Ball(EVec3f(15, 2, 5), EVec3f(0, 0, 40)));
	m_balls.push_back(Ball(EVec3f(15, 2, 35), EVec3f(0, 0, 70)));*/
	

	//箱の大きさを設定
	EVec3f max1 = { 20.0f, 10.0f, 20.0f }, min1 = { 0.0f, 0.0f, 0.0f };
	//EVec3f max1 = { 50.0f, 10.0f, 50.0f }, min1 = { 0.0f, 0.0f, 0.0f };
	box1_.setMax(max1);
	box1_.setMin(min1);

}


void EventManager::DrawScene()
{
	glEnable(GL_DEPTH_TEST);
	//箱を書く
	box1_.Draw();

	glBegin(GL_LINES);
		glVertex3fv(rayp_.data()); //glVertex3f(rayp_[0], rayp_[1], rayp_[2]);
		EVec3f tmp = rayp_ + 10.0f * rayd_;
		glVertex3fv(tmp.data());
	glEnd();

	//電気をつける
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	//球を描く
	for (int i = 0; i < m_balls.size(); i++) {
		m_balls[i].Draw();
	}

	//電気を消す
	glDisable(GL_LIGHTING);

}	

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
	// クリックでレイを飛ばす
	EVec3f p, d;
	ogl->GetCursorRay(EVec2i(x, y), p, d);
	rayp_ = p;
	rayd_ = d;

	m_isL = true;
	ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLの視点を回転させる準備

	// (仮)レイがヒットしたときに
	EVec3f update_velocity;
	for (int i = 0; i < m_balls.size(); i++) {
		EVec3f diff = m_balls[i].getPos() - d;
		if (diff.norm() <= m_balls[i].getRadius()) {
			update_velocity *= 2;//p + 10.0f * d;
			m_balls[i].setVelocity(update_velocity);
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


//球同士の衝突判定
bool EventManager::isCollision(const int& n1, const int& n2)
{
	float t = m_balls[n1].getRadius() + m_balls[n2].getRadius();
	if ((m_balls[n1].getPos() - m_balls[n2].getPos()).norm() <= t && m_balls[n1].getCollision() == false && m_balls[n2].getCollision() == false) {
		m_balls[n1].setCollision(true);
		m_balls[n2].setCollision(true);
		return true; // 衝突する
	}
	else if ((m_balls[n1].getPos() - m_balls[n2].getPos()).norm() <= t && (m_balls[n1].getCollision() == true || m_balls[n2].getCollision() == true)) { // 接触中に接触
		return false;
	}
	else { //離れたら
		m_balls[n1].setCollision(false);
		m_balls[n2].setCollision(false);
		return false; // 衝突しない
	}
}

// 球同士衝突時の速度を更新
void EventManager::UpdateVelocity(const int& n1, const int& n2)
{
	float E = 0.99f;
	EVec3f v1_before = m_balls[n1].getVelocity();
	EVec3f v2_before = m_balls[n2].getVelocity();
	EVec3f v1_parallel_before, v2_parallel_before, v1_vertical, v2_vertical;

	EVec3f p = m_balls[n1].getPos() - m_balls[n2].getPos();
	//p.normalize();

	//v1_parallel_before = v1_before.dot(p) * p;
	//v2_parallel_before = v2_before.dot(-p) * (-p);

	v1_parallel_before = v1_before.dot(p) / pow(p.norm(), 2) * p;
	v2_parallel_before = v2_before.dot(-p) / pow(-p.norm(), 2) * (-p);

	v1_vertical = v1_before - v1_parallel_before;
	v2_vertical = v2_before - v2_parallel_before;

	EVec3f v1_parallel_after = (1.0f - E) / 2.0f * v1_parallel_before + (1.0f + E) / 2.0f * v2_parallel_before;
	EVec3f v2_parallel_after = (1.0f + E) / 2.0f * v1_parallel_before + (1.0f - E) / 2.0f * v2_parallel_before;

	EVec3f v1_after = v1_parallel_after + v1_vertical;
	EVec3f v2_after = v2_parallel_after + v2_vertical;

	m_balls[n1].setVelocity(v1_after);
	m_balls[n2].setVelocity(v2_after);

}
/*
void UpdateVelocity(Ball& b1, Ball& b2)
{
	float E = 0.99f;
	EVec3f v1_before = b1.getVelocity(), v2_before = b2.getVelocity();
	EVec3f pos1 = b1.getPos(), pos2 = b2.getPos();
	pos1[1] -= b1.getRadius();
	pos2[1] -= b2.getRadius();

	// 垂直成分方向
	EVec3f oc_vector1 = pos1.cross(pos2);// + pos1;
	EVec3f oc_vector2 = pos1.cross(pos2);// + pos2;

	// v_beforeの垂直成分(衝突前後で変化しない)
	EVec3f v1_vertical = v1_before.dot(oc_vector1) / pow(oc_vector1.norm(), 2) * oc_vector1;
	EVec3f v2_vertical = v2_before.dot(oc_vector2) / pow(oc_vector2.norm(), 2) * oc_vector2;
	
	// v_beforeの平行成分(衝突で変化)
	EVec3f v1_parallel_before = v1_before - v1_vertical;
	EVec3f v2_parallel_before = v2_before - v2_vertical;

	// v_afterの平行成分(衝突で変化)
	EVec3f v1_parallel_after = (1.0f - E) / 2.0f * v1_parallel_before + (1.0f + E) / 2.0f * v2_parallel_before;
	EVec3f v2_parallel_after = (1.0f + E) / 2.0f * v1_parallel_before + (1.0f - E) / 2.0f * v2_parallel_before;

	// 各成分合成
	EVec3f v1_after = v1_vertical + v1_parallel_after;
	EVec3f v2_after = v2_vertical + v2_parallel_after; 

	b1.setVelocity(v1_after);
	b2.setVelocity(v2_after);
}
*/
void EventManager::Step()
{

	float dt = 0.01f;
	for (int i = 0; i < m_balls.size(); i++) {
		m_balls[i].Step();
	}


	//球が壁と衝突
	float E = 0.99f;
	for (int i = 0; i < m_balls.size(); i++) {
		EVec3f distance1 = m_balls[i].getPos() - box1_.getMin(); // 球と壁minの距離
		EVec3f distance2 = box1_.getMax() - m_balls[i].getPos(); // 球と壁maxの距離
		EVec3f vi = m_balls[i].getVelocity();
		if ((distance1[0] <= m_balls[i].getRadius() && vi[0] < 0) || (distance2[0] <= m_balls[i].getRadius() && vi[0] > 0)) {
			vi[0] *= -E;
		}
		if ((distance1[1] <= m_balls[i].getRadius() && vi[1] < 0)) { // 天井との衝突は無くした
			vi[1] *= -E;
		}
		if ((distance1[2] <= m_balls[i].getRadius() && vi[2] < 0) || (distance2[2] <= m_balls[i].getRadius() && vi[2] > 0)) {
			vi[2] *= -E;
		}
		m_balls[i].setVelocity(vi);
	}

	//球同士の衝突
	for (int j = 0; j < m_balls.size() - 1; j++) 
	{
		for (int i = j + 1; i < m_balls.size(); i++) 
		{
			if (isCollision(j, i) == true)
			{
				UpdateVelocity(j, i);
			}
		}
	}

}



/* 座標軸
	//x:red, y:green, z:blue
	glLineWidth(2.0f);
	glDisable(GL_LIGHTING);//電気を消す

	//OpenGLで3本の直線を描く
	glBegin(GL_LINES);
	glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
	glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
	glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
	glEnd();

 //レイと球の接触判定
bool isRayHit(const Ball& b1, const EVec3f& ray_d)
{
	EVec3f diff = b1.getPos() - ray_d; 
	if (diff.norm() <= b1.getRadius())
		return true;
}
	*/