#include <math.h>
#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "Box.h"



EventManager::EventManager()
{
	m_isL = m_isR = m_isM = false;

	m_balls.push_back(Ball(EVec3f(5, 0, 5), EVec3f(10, 2, 30)));
	m_balls.push_back(Ball(EVec3f(5, 0, 15), EVec3f(30, 2, 10)));
	m_balls.push_back(Ball(EVec3f(15, 0, 10), EVec3f(5, 2, 30)));
	m_balls.push_back(Ball(EVec3f(15, 0, 15), EVec3f(40, 2, 80)));



	//箱の大きさを設定
	EVec3f max1 = { 20.0f, 10.0f, 20.0f }, min1 = { 0.0f, 0.0f, 0.0f };
	box1_.setMax(max1);
	box1_.setMin(min1);

	/*
	//球の初期位置をセット
	EVec3f pos1 = { 1.0f, 0.0f, 3.0f }, pos2 = { 6.0f, 0.0f, 8.0f }, pos3 = { 11.0f, 0.0f, 13.0f };
	b1_.setPos(pos1);
	b2_.setPos(pos2);
	b3_.setPos(pos3);

	//球の初速をセット
	EVec3f v1 = { -5.0f, 0.0f, -85.0f }, v2 = { 26.0f, 0.0f, 26.0f }, v3 = { -70.0f, 0.0f, 50.0f };
	b1_.setVelocity(v1);
	b2_.setVelocity(v2);
	b3_.setVelocity(v3);
	*/

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

	for (int i = 0; i < m_balls.size(); i++) {
		m_balls[i].Draw();
	}

	/*
	//球を描く
	b1_.Draw();
	b2_.Draw();
	b3_.Draw();
	*/

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
bool isCollision(Ball& b1, Ball& b2)
{
	float t = b1.getRadius() + b2.getRadius();
	if ((b1.getPos() - b2.getPos()).norm() <= t && b1.getCollision() == false && b2.getCollision() == false) {
		b1.setCollision(true);
		b2.setCollision(true);
		return true; // 衝突する
	}
	else if ((b1.getPos() - b2.getPos()).norm() <= t && (b1.getCollision() == true || b2.getCollision() == true)) { // 接触中に接触
		return false;
	}
	else { //離れたら
		b1.setCollision(false);
		b2.setCollision(false);
		return false; // 衝突しない
	}
}




// 衝突時の速度を更新
// 法線方向だけにしたい
void UpdateVelocity(EVec3f& v1, EVec3f& v2)
{
	/*
	float E = 0.99f;
	EVec3f temp_v1 = v1, temp_v2 = v2;
	v1 = (1.0f - E) / 2.0f * temp_v1 + (1.0f + E) / 2.0f * temp_v2;
	v2 = (1.0f + E) / 2.0f * temp_v1 + (1.0f - E) / 2.0f * temp_v2; 
	*/
}

void EventManager::Step()
{
	float dt = 0.01f;
	for (int i = 0; i < m_balls.size(); i++) {
		m_balls[i].Step();
	}


	//球が壁と衝突
	float E = 0.99f;
	for (int i = 0; i < m_balls.size(); i++) {
		EVec3f distance1 = m_balls[i].getPos() - box1_.getMin(); // 名前変えたい...
		EVec3f distance2 = box1_.getMax() - m_balls[i].getPos();
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
			if (isCollision(m_balls[j], m_balls[i]) == true) 
			{
				EVec3f j_velocity = m_balls[j].getVelocity(), i_velocity = m_balls[i].getVelocity();

				//UpdateVelocity(j_velocity, i_velocity);///////////
				m_balls[j].setVelocity(j_velocity);
				m_balls[i].setVelocity(i_velocity);
			}
		}
	}
	

	/*                
	//球同士の衝突
	if (isCollision(b1_, b2_) == true) {
		UpdateVelocity(v1, v2);
		b1_.setVelocity(v1);
		b2_.setVelocity(v2);
	}
	if (isCollision(b2_, b3_) == true) {
		UpdateVelocity(v2, v3);
		b2_.setVelocity(v2);
		b3_.setVelocity(v3);
	}
	if (isCollision(b3_, b1_) == true) {
		UpdateVelocity(v3, v1);
		b3_.setVelocity(v3);
		b1_.setVelocity(v1);
	}
	*/
}



/* 座標軸（必要に応じてコメントアウト）
	//x:red, y:green, z:blue
	glLineWidth(2.0f);
	glDisable(GL_LIGHTING);//電気を消す

	//OpenGLで3本の直線を描く
	glBegin(GL_LINES);
	glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
	glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
	glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
	glEnd();
	*/


/*
* //レイと球の接触判定
bool isRayHit(const Ball& b1, const EVec3f& ray_d)
{
	EVec3f diff = b1.getPos() - ray_d; 
	if (diff.norm() <= b1.getRadius())
		return true;
}

//球がYZ平面の壁と衝突するかを判定
bool isCollisionWallYZ(const Ball& b1, const Box& box1)
{
	// yz平面の衝突判定
	if ((b1.getPos()[0] - box1.getMin()[0] <= b1.getRadius() && b1.getVelocity()[0] < 0) || (box1.getMax()[0] - b1.getPos()[0] <= b1.getRadius())) { // (左面で衝突 || 右面で衝突)
		return true;
	}
	else {
		return false;
	}
}

//球がXZ平面の壁と衝突するかを判定
bool isCollisionWallXZ(const Ball& b1, const Box& box1)
{
	// xz平面の衝突判定
	if ((b1.getPos()[1] - box1.getMin()[1] <= b1.getRadius() && b1.getVelocity()[1] < 0) || (box1.getMax()[1] - b1.getPos()[1] <= b1.getRadius())) { // (下面で衝突 || 上面で衝突)
		return true;
	}
	else {
		return false;
	}
}

bool isCollisionWallXY(const Ball& b1, const Box& box1) {
	// xy平面の衝突判定
	if ((b1.getPos()[2] - box1.getMin()[2] <= b1.getRadius() && b1.getVelocity()[2] < 0) || (box1.getMax()[2] - b1.getPos()[2] <= b1.getRadius())) { // (奥面で衝突 || 手前面で衝突)
		return true;
	}
	else {
		return false;
	}
}
*/

/*
//球１が壁と衝突
EVec3f distance1 = b1_.getPos() - box1_.getMin();
EVec3f distance2 = box1_.getMax() - b1_.getPos();
EVec3f v1 = b1_.getVelocity();
for (int i = 0; i < 3; i++) {
	if ((distance1[i] <= b1_.getRadius() && v1[i] < 0) || (distance2[i] <= b1_.getRadius() && v1[i] > 0)) {
		v1[i] *= -E;
	}
}
b1_.setVelocity(v1);

//球２が壁と衝突
EVec3f distance3 = b2_.getPos() - box1_.getMin();
EVec3f distance4 = box1_.getMax() - b2_.getPos();
EVec3f v2 = b2_.getVelocity();
for (int i = 0; i < 3; i++) {
	if ((distance3[i] <= b2_.getRadius() && v2[i] < 0) || (distance4[i] <= b2_.getRadius() && v2[i] > 0)) {
		v2[i] *= -E;
	}
}
b2_.setVelocity(v2);

//球３が壁と衝突
EVec3f distance5 = b3_.getPos() - box1_.getMin();
EVec3f distance6 = box1_.getMax() - b3_.getPos();
EVec3f v3 = b3_.getVelocity();
for (int i = 0; i < 3; i++) {
	if ((distance5[i] <= b3_.getRadius() && v3[i] < 0) || (distance6[i] <= b3_.getRadius() && v3[i] > 0)) {
		v3[i] *= -E;
	}
}
b3_.setVelocity(v3);
*/

/*
//球同士の衝突
	if (isCollision(b1_, b2_) == true) {
		EVec3f temp_v1 = b1_.getVelocity(), temp_v2 = b2_.getVelocity();
		UpdateVelocity(temp_v1, temp_v2);
		b1_.setVelocity(temp_v1);
		b2_.setVelocity(temp_v2);
	}
	if (isCollision(b2_, b3_) == true) {
		EVec3f temp_v2 = b2_.getVelocity(), temp_v3 = b3_.getVelocity();
		UpdateVelocity(temp_v2, temp_v3);
		b1_.setVelocity(temp_v2);
		b2_.setVelocity(temp_v3);
	}
	if (isCollision(b3_, b1_) == true) {
		EVec3f temp_v3 = b3_.getVelocity(), temp_v1 = b1_.getVelocity();
		UpdateVelocity(temp_v3, temp_v1);
		b1_.setVelocity(temp_v3);
		b2_.setVelocity(temp_v1);
	}*/




	/*
	//球１が壁と衝突
	float E = 0.99f;
	EVec3f distance1 = b1_.getPos() - box1_.getMin(); // 名前変えたい...
	EVec3f distance2 = box1_.getMax() - b1_.getPos();
	EVec3f v1 = b1_.getVelocity();
	if ((distance1[0] <= b1_.getRadius() && v1[0] < 0) || (distance2[0] <= b1_.getRadius() && v1[0] > 0)) {
		v1[0] *= -E;
	}
	if ((distance1[1] <= b1_.getRadius() && v1[1] < 0)) { // 天井との衝突は無くした
		v1[1] *= -E;
	}
	if ((distance1[2] <= b1_.getRadius() && v1[2] < 0) || (distance2[2] <= b1_.getRadius() && v1[2] > 0)) {
		v1[2] *= -E;
	}
	b1_.setVelocity(v1);

	// 球２と壁
	EVec3f distance3 = b2_.getPos() - box1_.getMin();
	EVec3f distance4 = box1_.getMax() - b2_.getPos();
	EVec3f v2 = b2_.getVelocity();
	if ((distance3[0] <= b2_.getRadius() && v2[0] < 0) || (distance4[0] <= b2_.getRadius() && v2[0] > 0)) {
		v2[0] *= -E;
	}
	if ((distance3[1] <= b2_.getRadius() && v2[1] < 0)) {
		v2[1] *= -E;
	}
	if ((distance3[2] <= b2_.getRadius() && v2[2] < 0) || (distance4[2] <= b2_.getRadius() && v2[2] > 0)) {
		v2[2] *= -E;
	}
	b2_.setVelocity(v2);

	// 球３と壁
	EVec3f distance5 = b3_.getPos() - box1_.getMin();
	EVec3f distance6 = box1_.getMax() - b3_.getPos();
	EVec3f v3 = b3_.getVelocity();
	if ((distance5[0] <= b3_.getRadius() && v3[0] < 0) || (distance6[0] <= b3_.getRadius() && v3[0] > 0)) {
		v3[0] *= -E;
	}
	if ((distance5[1] <= b3_.getRadius() && v3[1] < 0)) {
		v3[1] *= -E;
	}
	if ((distance5[2] <= b3_.getRadius() && v3[2] < 0) || (distance6[2] <= b3_.getRadius() && v3[2] > 0)) {
		v3[2] *= -E;
	}
	b3_.setVelocity(v3);
	*/