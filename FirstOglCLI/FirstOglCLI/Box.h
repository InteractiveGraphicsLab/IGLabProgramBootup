#pragma once
#include "tmath.h"

class Box
{
private:
	EVec3f max_; // x, y, z�������ꂼ��̍ő�l
	EVec3f min_; // �ŏ��l(0, 0, 0)
public:
	Box();
	~Box();
	//void setPos(EVec3d pos);
	void setMax(EVec3f max); //�@�[�������Z�b�g
	void setMin(EVec3f min);
	EVec3f getMax() const;
	EVec3f getMin() const;         // �Ƃ肠����(0, 0, 0)�Ŏ���
	void Draw();
};