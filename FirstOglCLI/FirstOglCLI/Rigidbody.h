#include "OglForCLI.h"
#ifndef __Rigidbody__
#define __Rigidbody__
struct Rigidbody
{
	float mass;//����
	float e;//������
	EMat3f moment;//�����e���\��
	int type;//���̂�type
};
#endif //Rigidbody