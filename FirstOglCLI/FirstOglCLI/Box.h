#pragma once
#include "tmath.h"

class Box
{
private:
	EVec3d max_; // x, y, z�������ꂼ��̍ő�l
	EVec3d min_; // �ŏ��l(0, 0, 0)
public:
	Box();
	~Box();
	//void setPos(EVec3d pos);
	void setMax(EVec3d max); //�@�[�������Z�b�g
	EVec3d getMax();
	EVec3d getMin();         // �Ƃ肠����(0, 0, 0)�Ŏ���
	void Draw();
};

