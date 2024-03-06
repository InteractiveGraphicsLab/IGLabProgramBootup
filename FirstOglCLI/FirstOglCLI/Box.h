#pragma once
#include "tmath.h"

class Box
{
private:
	EVec3f max_; // x, y, z方向それぞれの最大値
	EVec3f min_; // 最小値(0, 0, 0)
public:
	Box();
	~Box();
	//void setPos(EVec3d pos);
	void setMax(EVec3f max); //　端っこをセット
	void setMin(EVec3f min);
	EVec3f getMax() const;
	EVec3f getMin() const;         // とりあえず(0, 0, 0)で実装
	void Draw();
};