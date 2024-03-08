#include "OglForCLI.h"

class Ball
{
private:
    float radius_;
    EVec3f pos_;
    //EVec3f rot_;
    EVec3f vel_;
    //EVec3f ang_;

public:
    Ball(const EVec3f& pos, const EVec3f& vel);
    Ball(const Ball& src);
    EVec3f getPos() const;
    void draw();
    void Step(float dt);
};