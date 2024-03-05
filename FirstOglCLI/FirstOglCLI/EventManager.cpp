#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "Box.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;

  //箱の大きさを設定
  EVec3d max1 = { 20.0f, 8.0f, 20.0f }, min1 = { 0.0f, 0.0f, 0.0f };
  box1_.setMax(max1);
  box1_.setMin(min1);

  //球の初期位置をセット
  EVec3d pos1 = { 1.0f, 2.0f, 3.0f }, pos2 = { 2.0f, 3.0f, 4.0f }, pos3 = { 3.0f, 4.0f, 5.0f };
  b1_.setPos(pos1);
  b2_.setPos(pos2);
  b3_.setPos(pos3);

  //球の初速をセット
  EVec3d v1 = { 20.0f, 20.0f, 20.0f }, v2 = { 30.0f, 30.0f, 30.0f }, v3 = { 40.0f, 40.0f, 40.0f };
  b1_.setVelocity(v1);
  b2_.setVelocity(v2);
  b3_.setVelocity(v3);
}

//球１が壁と衝突するかを判定
EVec3d EventManager::isCollision1() 
{
	EVec3d isCollision1 = { 0, 0, 0 }; //1のとき衝突

	// x座標の衝突判定
	if ((b1_.getPos()[0] - box1_.getMin()[0] <= R && b1_.getVelocity()[0] < 0) || (box1_.getMax()[0] - b1_.getPos()[0] <= R)) { // (左面で衝突 || 右面で衝突)
		isCollision1[0] = 1;
	}
	else {
		isCollision1[0] = 0;
	}
	// y座標の衝突判定
	if ((b1_.getPos()[1] - box1_.getMin()[1] <= R && b1_.getVelocity()[1] < 0) || (box1_.getMax()[1] - b1_.getPos()[1] <= R)) { // (下面で衝突 || 上面で衝突)
		isCollision1[1] = 1;
	}
	else {
		isCollision1[1] = 0;
	}
	// z座標の衝突判定
	if ((b1_.getPos()[2] - box1_.getMin()[2] <= R && b1_.getVelocity()[2] < 0) || (box1_.getMax()[2] - b1_.getPos()[2] <= R)) { // (奥面で衝突 || 手前面で衝突)
		isCollision1[2] = 1;
	}
	else {
		isCollision1[2] = 0;
	}

	return isCollision1;
}

//球2が壁と衝突するかを判定
EVec3d EventManager::isCollision2()
{
	EVec3d isCollision2 = { 0, 0, 0 }; //1のとき衝突

	// x座標の衝突判定
	if ((b2_.getPos()[0] - box1_.getMin()[0] <= R && b2_.getVelocity()[0] < 0) || (box1_.getMax()[0] - b2_.getPos()[0] <= R)) { // (左面で衝突 || 右面で衝突)
		isCollision2[0] = 1;
	}
	else {
		isCollision2[0] = 0;
	}
	// y座標の衝突判定
	if ((b2_.getPos()[1] - box1_.getMin()[1] <= R && b2_.getVelocity()[1] < 0) || (box1_.getMax()[1] - b2_.getPos()[1] <= R)) { // (下面で衝突 || 上面で衝突)
		isCollision2[1] = 1;
	}
	else {
		isCollision2[1] = 0;
	}
	// z座標の衝突判定
	if ((b3_.getPos()[2] - box1_.getMin()[2] <= R && b3_.getVelocity()[2] < 0) || (box1_.getMax()[2] - b3_.getPos()[2] <= R)) { // (奥面で衝突 || 手前面で衝突)
		isCollision2[2] = 1;
	}
	else {
		isCollision2[2] = 0;
	}

	return isCollision2;
}

//球3が壁と衝突するかを判定
EVec3d EventManager::isCollision3()
{
	EVec3d isCollision3 = { 0, 0, 0 }; //1のとき衝突

	// x座標の衝突判定
	if ((b3_.getPos()[0] - box1_.getMin()[0] <= R && b3_.getVelocity()[0] < 0) || (box1_.getMax()[0] - b3_.getPos()[0] <= R)) { // (左面で衝突 || 右面で衝突)
		isCollision3[0] = 1;
	}
	else {
		isCollision3[0] = 0;
	}

	// y座標の衝突判定
	if ((b3_.getPos()[1] - box1_.getMin()[1] <= R && b3_.getVelocity()[1] < 0) || (box1_.getMax()[1] - b3_.getPos()[1] <= R)) { // (下面で衝突 || 上面で衝突)
		isCollision3[1] = 1;
	}
	else {
		isCollision3[1] = 0;
	}

	// z座標の衝突判定
	if ((b3_.getPos()[2] - box1_.getMin()[2] <= R && b3_.getVelocity()[2] < 0) || (box1_.getMax()[2] - b3_.getPos()[2] <= R)) { // (奥面で衝突 || 手前面で衝突)
		isCollision3[2] = 1;
	}
	else {
		isCollision3[2] = 0;
	}

	return isCollision3;
}



void EventManager::DrawScene()
{
  //箱を書く
  box1_.Draw();

  //x:red, y:green, z:blue 
  glLineWidth(2.0f);
  glDisable(GL_LIGHTING);//電気を消す

  //OpenGLで3本の直線を描く
  glBegin(GL_LINES);
  glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
  glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
  glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
  glEnd();

  //電気をつける
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  //球を描く
  b1_.Draw();
  b2_.Draw();
  b3_.Draw();


  //電気を消す
  glDisable(GL_LIGHTING);

}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLの視点を回転させる準備
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
	EVec3d v1 = b1_.CalcVelocity(b1_.getVelocity()); // V1_beforeを取得　→　dt秒後のV1_afterを計算
	EVec3d v2 = b2_.CalcVelocity(b2_.getVelocity()); // V2_beforeを取得　→　dt秒後のV2_afterを計算
	EVec3d v3 = b3_.CalcVelocity(b3_.getVelocity()); // V3_beforeを取得　→　dt秒後のV3_afterを計算
	EVec3d isHit1 = isCollision1(), isHit2 = isCollision2(), isHit3 = isCollision3(); // 関数の呼び出し回数を減らすためにあらかじめ代入

	//球１が壁に衝突していたら
	for (int i = 0; i < 3; i++) {
		if (isHit1[i] == 1)
			v1[i] *= -E; 
	}
	//球2が壁に衝突していたら
	for (int i = 0; i < 3; i++) {
		if (isHit2[i] == 1)
			v2[i] *= -E;
	}
	//球3が壁に衝突していたら
	for (int i = 0; i < 3; i++) {
		if (isHit3[i] == 1)
			v3[i] *= -E;
	}

	b1_.setVelocity(v1); // 球１ V_afterをset
	b2_.setVelocity(v2); // 球２
	b3_.setVelocity(v3); // 球３

	b1_.Step();//球１の位置を更新
	b2_.Step();//球２
	b3_.Step();//球３
}
