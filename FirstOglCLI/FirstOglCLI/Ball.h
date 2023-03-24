#pragma once

#include "GL/glew.h"
#include "tmath.h"

class Ball {
    double m_position;
    double m_velocity;

    Ball(const EVec3d& pos, const EVec3d& force);

    void step();
    void draw();

};

