#pragma once
#include "tmath.h"

class Ball

{
private:
	EVec3d pos_; // 中心座標
	EVec3d v_; // 速度
public:
	Ball();
	~Ball();
	void setPos(EVec3d pos); // 中心座標をセット
	void setVelocity(EVec3d v); // 速度をセット
	EVec3d getPos(); // 中心座標を取得
	EVec3d getVelocity(); //速度を取得
	EVec3d CalcVelocity(EVec3d v); //速度を計算
	void Step();
	void Draw(); 
};

