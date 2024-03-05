#pragma once
#include "tmath.h"

class Box
{
private:
	EVec3d max_; // x, y, z方向それぞれの最大値
	EVec3d min_; // 最小値(0, 0, 0)
public:
	Box();
	~Box();
	//void setPos(EVec3d pos);
	void setMax(EVec3d max); //　端っこをセット
	EVec3d getMax();
	EVec3d getMin();         // とりあえず(0, 0, 0)で実装
	void Draw();
};

