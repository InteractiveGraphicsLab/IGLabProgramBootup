#include "OglForCLI.h"
#ifndef __Transform__
#define __Transform__

// プリコンパイルするヘッダーをここに追加します

struct Transform
{
	EVec3f position;//重心の位置
	EVec3f rotation;//姿勢
	EVec3f linearVelocity;//並進速度
	EVec3f rotateVelocity;//回転速度
};
#endif //Transform