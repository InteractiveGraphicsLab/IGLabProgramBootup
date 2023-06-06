#include "pch.h"
#include "Ball.h"
#include "OglForCLI.h"
#include "Green.h"
#include "YPolygon.h"

#define M_PI 3.141592


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

//void Ball::Step()
//{
//    //èdóÕ
//    m_velo[2] -= 0.98f * 0.033f;       
//}


static EVec3d sCalcShperePos(double t, double p)
{
    double x = cos(t) * cos(p);
    double y = sin(t) * cos(p);
    double z = sin(p);

    return EVec3d(x, y, z);
}


static void DrawSphere()
{
    glEnable(GL_DEPTH_TEST);
    //Material 
    float   shin[1] = { 32 };
    EVec4f  spec(1, 1, 1, 0.5);
    EVec4f  diff(1.0f, 1.0f, 1.0f, 1.0f);
    EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);


    int N = 20;

    glBegin(GL_TRIANGLES);
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            double t1 =  (x    ) / (double)N * 2.0 * M_PI;
            double t2 =  (x + 1) / (double)N * 2.0 * M_PI;
            double p1 = -(y    ) / (double)N * 1.0 * M_PI - 0.5 * M_PI;
            double p2 = -(y + 1) / (double)N * 1.0 * M_PI - 0.5 * M_PI;

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3dv(sCalcShperePos(t1, p1).data());
            glVertex3dv(sCalcShperePos(t2, p1).data());
            glVertex3dv(sCalcShperePos(t2, p2).data());

            glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1));
            glVertex3dv(sCalcShperePos(t1, p1).data());
            glVertex3dv(sCalcShperePos(t2, p2).data());
            glVertex3dv(sCalcShperePos(t1, p2).data());
        }
    }
    glEnd();
}

void Ball::Draw() const 
{
    glTranslated(m_pos[0], m_pos[1], m_pos[2]);
    DrawSphere();
    glTranslated(-m_pos[0], -m_pos[1], -m_pos[2]);
}

