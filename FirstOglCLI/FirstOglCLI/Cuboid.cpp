#include "pch.h"
#include "Cuboid.h"


Cuboid::Cuboid(EVec3f& pos, float width, float height, float length, EVec3f& velo)
{
    m_pos = pos;
    m_width = width;
    m_height = height;
    m_depth = length;
    m_velo = velo;
    m_bounce = 0.9f; // îΩî≠åWêî
}

Cuboid::Cuboid(const Cuboid& src)
{
    m_pos = src.m_pos;
    m_width = src.m_width;
    m_height = src.m_height;
    m_depth = src.m_depth;
    m_velo = src.m_velo;
    m_bounce = src.m_bounce;
}

void Cuboid::Step()
{
    float dt = 0.33f;
    static float t = 0.33f;
    static EVec3f acc = EVec3f(0, 0, 0);/*
    if (t > 30.0f && t < 60.0f) // é¸ä˙â^ìÆ
    {
        m_velo[1] = 0.2f;
    }
    else if (t > 60.0f)
    {
        t = 0;
    }
    else
    {
        m_velo[1] = -0.2f;
    }*/
    m_velo += acc * dt;
    m_pos += m_velo * dt;
    m_velo *= 1.0f; // 0.99f
    t += dt;
}

void Cuboid::Draw()
{
    DrawCuboid();
}

void Cuboid::DrawCuboid()
{
    glEnable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);

    EVec3f twoPos[2];
    twoPos[0] = m_pos - EVec3f(m_width, m_height, m_depth);
    twoPos[1] = m_pos + EVec3f(m_width, m_height, m_depth);

    // ç≈è¨ì_Ç∆ç≈ëÂì_Ç©ÇÁíºï˚ëÃÇï`âÊ
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            glVertex3f(twoPos[x][0], twoPos[    y][1], twoPos[    y][2]);
            glVertex3f(twoPos[x][0], twoPos[1 - y][1], twoPos[    y][2]);
            glVertex3f(twoPos[x][0], twoPos[1 - y][1], twoPos[1 - y][2]);

            glVertex3f(twoPos[    y][0], twoPos[x][1], twoPos[    y][2]);
            glVertex3f(twoPos[1 - y][0], twoPos[x][1], twoPos[    y][2]);
            glVertex3f(twoPos[1 - y][0], twoPos[x][1], twoPos[1 - y][2]);

            glVertex3f(twoPos[    y][0], twoPos[    y][1], twoPos[x][2]);
            glVertex3f(twoPos[1 - y][0], twoPos[    y][1], twoPos[x][2]);
            glVertex3f(twoPos[1 - y][0], twoPos[1 - y][1], twoPos[x][2]);
        }
    }
    glEnd();
}

EVec3f Cuboid::GetPos()
{
    return m_pos;
}

float Cuboid::GetWidth()
{
    return m_width;
}

float Cuboid::GetHeight()
{
    return m_height;
}

float Cuboid::GetDepth()
{
    return m_depth;
}

float Cuboid::GetBounce()
{
    return m_bounce;
}
