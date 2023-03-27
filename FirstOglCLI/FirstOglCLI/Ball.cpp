#include "pch.h"
#include "Ball.h"
#include <math.h>


Ball::Ball(float radi, EVec3f& pos, EVec3f& velo)
{
    m_pos = pos;
    m_velo = velo;
    m_radi = radi;
}

Ball::Ball(const Ball& src)
{
    m_pos = src.m_pos;
    m_velo = src.m_velo;
    m_radi = src.m_radi;
}

void Ball::Step()
{
    float dt = 0.33f;
    const EVec3f acc = EVec3f(0, -0.2f, 0);/* //EVec3f(0, -0.2f, 0)
    static float angle;
    static bool check[3];*/
    m_velo += acc * dt;
    m_pos += m_velo * dt;
    if (sqrt(m_velo[0] * m_velo[0] + m_velo[2] * m_velo[2]) < 0.001f)
    {
        m_velo[0] = 0.0f;
        m_velo[2] = 0.0f;
    }
    else
    {
        m_velo[0] *= 0.99f; // 0.99f
        m_velo[2] *= 0.99f; // 0.99f
    }
    m_velo[1] *= 0.99f;
}

void Ball::Draw()
{
    glTranslated(m_pos[0], m_pos[1], m_pos[2]);
    /*glRotated(m_radi, 1, 1, 1);*/
    DrawSphere();
    glTranslated(-m_pos[0], -m_pos[1], -m_pos[2]);
    /*glRotated(m_radi, 1, 1, 1);*/
}

void Ball::DrawSphere()
{
    const int    N = 10;
    const float M_PI = 3.141592f;

    glEnable(GL_DEPTH_TEST);
    //Material 
    float   shin[1] = { 64 };
    EVec4f  spec(1, 1, 1, 0.5f);
    EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);
    EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glBegin(GL_TRIANGLES);
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            float t1 = (x) / (float)N * 2.0f * M_PI;
            float t2 = (x + 1) / (float)N * 2.0f * M_PI;
            float p1 = (y) / (float)N * 1.0f * M_PI - 0.5f * M_PI;
            float p2 = (y + 1) / (float)N * 1.0f * M_PI - 0.5f * M_PI;

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3d(m_radi * cos(t1) * cos(p1), m_radi * sin(p1), m_radi * sin(t1) * cos(p1));
            glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glVertex3d(m_radi * cos(t2) * cos(p2), m_radi * sin(p2), m_radi * sin(t2) * cos(p2));
            glNormal3d(cos(t2) * cos(p1), sin(p1), sin(t2) * cos(p1));
            glVertex3d(m_radi * cos(t2) * cos(p1), m_radi * sin(p1), m_radi * sin(t2) * cos(p1));

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3d(m_radi * cos(t1) * cos(p1), m_radi * sin(p1), m_radi * sin(t1) * cos(p1));
            glNormal3d(cos(t1) * cos(p2), sin(p2), sin(t1) * cos(p2));
            glVertex3d(m_radi * cos(t1) * cos(p2), m_radi * sin(p2), m_radi * sin(t1) * cos(p2));
            glNormal3d(cos(t2) * cos(p2), sin(p2), sin(t2) * cos(p2));
            glVertex3d(m_radi * cos(t2) * cos(p2), m_radi * sin(p2), m_radi * sin(t2) * cos(p2));

        }
    }
    glEnd();
}

//void Ball::HitCuboid(std::vector<Cuboid> cuboids)
//{
//    int check[3] = {1, 1, 1};
//    int count;
//    EVec3f pos, length;
//    float bounce;
//    for (auto cuboid:cuboids)
//    {
//        check[0] = check[1] = check[2] = 1;
//        count = 0;
//
//        pos = cuboid.GetPos();
//        length = cuboid.GetLength();
//        bounce = cuboid.GetBounce();
//
//        for (int i = 0; i < 3; ++i) {
//            if (pos[i] - length[i] <= m_pos[i] && m_pos[i] <= pos[i] + length[i])
//            {
//                check[i] = 0;
//                count += 1;
//            }
//        }
//        switch (count) {
//        case 0:
//            break;
//        case 1:
//            break;
//        case 2:
//            for (int i = 0; i < 3; ++i)
//            {
//                if (check[i] == 1)
//                {
//                    if (pos[i] <= m_pos[i])
//                    {
//                        if (m_pos[i] - pos[i] <= m_radi + length[i])
//                        {
//                            m_pos[i] = pos[i] + m_radi + length[i];
//                            m_velo[i] *= -bounce;
//                        }
//                    }
//                    else
//                    {
//                        if (pos[i] - m_pos[i] <= m_radi + length[i])
//                        {
//                            m_pos[i] = pos[i] - m_radi - length[i];
//                            m_velo[i] *= -bounce;
//                        }
//                    }
//                }
//            }
//            break;
//        case 3:
//            //’¼•û‘Ì“à•”
//            break;
//        default:
//            break;
//        }
//    }
//}
//
//void Ball::HitBall(std::vector<Ball> balls)
//{
//    EVec3f pos, diff, normal;
//    float radi;
//    for (auto ball : balls)
//    {
//        if (this != &ball)
//        {
//            pos = ball.GetPos();
//            radi = ball.GetRadi();
//            diff = m_pos - pos;
//            if(m_radi + radi >= pow())
//        }
//    }
//}


EVec3f Ball::GetPos()
{
    return m_pos;
}


EVec3f Ball::GetVelo()
{
    return m_velo;
}

float Ball::GetRadi()
{
    return m_radi;
}

void Ball::SetPos(EVec3f pos)
{
    m_pos = pos;
}

void Ball::SetVelo(EVec3f velo)
{
    m_velo = velo;
}