#include "OglForCLI.h"
#ifndef __Transform__
#define __Transform__

// �v���R���p�C������w�b�_�[�������ɒǉ����܂�

struct Transform
{
	EVec3f position;//�d�S�̈ʒu
	//EVec4f quaternion;//�N�H�[�^�j�I��
	EVec3f euler;//�I�C���[�p�i�p���j
	EVec3f linearVelocity;//���i���x
	EVec3f rotateVelocity;//��]���x
};
#endif //Transform