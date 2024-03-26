#include <math.h>
#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "Box.h"



EventManager::EventManager()
{
	m_isL = m_isR = m_isM = false;

	// 球
	m_balls.push_back(Ball(EVec3f(16.0f, 2.0f, 42.0f), EVec3f(0.0f, 0.0f,   500.0f)));

	m_balls.push_back(Ball(EVec3f(16.0f, 2.0f, 32.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(13.0f, 2.0f, 26.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(19.0f, 2.0f, 26.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(10.0f, 2.0f, 20.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(16.0f, 2.0f, 20.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(22.0f, 2.0f, 20.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f( 7.0f, 2.0f, 14.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(13.0f, 2.0f, 14.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(19.0f, 2.0f, 14.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(25.0f, 2.0f, 14.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f( 4.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(10.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(16.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(22.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));
	m_balls.push_back(Ball(EVec3f(28.0f, 2.0f,  8.0f), EVec3f(0.0f, 0.0f,   0.0f)));

	//箱の大きさを設定
	EVec3f max1 = { 31.0f, 10.0f, 46.0f }, min1 = { 0.0f, 0.0f, 0.0f };
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
	rayp_ = p; // 始点(視点)pの座標 ?
	rayd_ = d; // 方向ベクトルd ?

	m_isL = true;
	ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLの視点を回転させる準備

	// レイで外力を加える
	float discriminant; // 判別式
	float distance, min_distance = 10000.0f;
	int min_ball_num = -1; //最もレイに近い球番号

	for (int i = 0; i < m_balls.size(); i++) {
		discriminant = pow(d.dot(p - m_balls[i].getPos()), 2) - (pow((p - m_balls[i].getPos()).norm(), 2) - pow(m_balls[i].getRadius(), 2)); // D = (d, p - pos)^2 - (||p - pos||^2 - r^2)　で判別式を計算
		if (discriminant > 0 ) { //レイと球が交差するなら
			distance = (p - m_balls[i].getPos()).norm(); //始点と球の中心の距離
			if (distance < min_distance) {
				min_ball_num = i;
				min_distance = distance;
			}
		}
	}

	//レイから最も近い球のみ外力を与える
	float dt = 0.02f; //接触時間
	if (min_ball_num != -1) { // min_ball_num == -1 ⇒ レイとの接触なし
		discriminant = pow(d.dot(p - m_balls[min_ball_num].getPos()), 2) - (pow((p - m_balls[min_ball_num].getPos()).norm(), 2) - pow(m_balls[min_ball_num].getRadius(), 2)); // D = (d, p - pos)^2 - (||p - pos||^2 - r^2)　で判別式を計算
		float t1 = -pow(d.dot(p - m_balls[min_ball_num].getPos()), 2) - sqrt(discriminant); // 視点からみて手前の接点
		float t2 = -pow(d.dot(p - m_balls[min_ball_num].getPos()), 2) + sqrt(discriminant); // 視点からみて奥側の接点
		EVec3f to_vector; // 接点から球の中心にかけてのベクトル
		EVec3f force; //レイによる外力
		EVec3f force_vertical; //外力の垂直成分
		EVec3f force_parallel; //外力の接線成分
		EVec3f velocity = m_balls[min_ball_num].getVelocity();

		force = 1000.0f * d;
		to_vector = m_balls[min_ball_num].getPos() - (p + t1 * d); //pos - 接点ベクトル
		force_vertical = force.dot(to_vector) / pow(to_vector.norm(), 2) * to_vector;
		force_parallel = force - force_vertical; // 回転で使うかも

		//EVec3f tmp_vector = { 1000.0f, 0.0f, 1000.0f };
		velocity += dt * force_vertical / m_balls[min_ball_num].getMass(); // 加速度と接触時間から速度を更新
		m_balls[min_ball_num].setVelocity(velocity);
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
	if ((m_balls[n1].getPos() - m_balls[n2].getPos()).norm() <= t)
		return true; // 衝突あり

	return false; // 衝突なし
}



// 球同士衝突時の速度を更新
void EventManager::UpdateVelocity(const int& n1, const int& n2)
{
	float E = 0.8f;
	EVec3f v1_before = m_balls[n1].getVelocity();
	EVec3f v2_before = m_balls[n2].getVelocity();
	EVec3f v1_parallel_before, v2_parallel_before, v1_vertical, v2_vertical; //衝突に対して垂直成分は変化しない
	EVec3f pos1 = m_balls[n1].getPos(), pos2 = m_balls[n2].getPos();
	EVec3f p = pos1 - pos2;

	// 正射影を用いてv_beforeの平行成分を求める
	v1_parallel_before = v1_before.dot(p) / pow(p.norm(), 2) * p;
	v2_parallel_before = v2_before.dot(p) / pow(p.norm(), 2) * (p); // p? -p?

	v1_vertical = v1_before - v1_parallel_before;
	v2_vertical = v2_before - v2_parallel_before;

	EVec3f v1_parallel_after = (1.0f - E) / 2.0f * v1_parallel_before + (1.0f + E) / 2.0f * v2_parallel_before;
	EVec3f v2_parallel_after = (1.0f + E) / 2.0f * v1_parallel_before + (1.0f - E) / 2.0f * v2_parallel_before;

	// 平行成分と垂直成分を合成
	EVec3f v1_after = v1_parallel_after + v1_vertical;
	EVec3f v2_after = v2_parallel_after + v2_vertical;
	m_balls[n1].setVelocity(v1_after);
	m_balls[n2].setVelocity(v2_after);



	// 連続衝突を避けるためにposも更新
	pos1 += 0.01f * v1_after;
	pos2 += 0.01f * v2_after;
	m_balls[n1].setPos(pos1);
	m_balls[n2].setPos(pos2);
	
}

void EventManager::Step()
{

	float E = 0.9f; //壁の反発係数
	for (int i = 0; i < m_balls.size(); i++) {
		//球が壁と衝突
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

		//球同士の衝突
		for (int j = i + 1; j < m_balls.size(); j++)
		{
			if (isCollision(i, j) == true)
				UpdateVelocity(i, j);
		}

		float dt = 0.01f;
		m_balls[i].Step(dt);
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