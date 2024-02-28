#include "OglForCLI.h"
#ifndef __Util__
#define __Util__
/*
色々まとめてあるUtilクラス
*/
typedef Eigen::Quaternionf Quat;
inline Quat rpy2q(EVec3f rpy) {
    Quat q = Eigen::AngleAxisd(rpy[0], EVec3f::UnitX())
        * Eigen::AngleAxisd(rpy[1], EVec3f::UnitY())
        * Eigen::AngleAxisd(rpy[2], EVec3f::UnitZ());
    return q;
}
#endif