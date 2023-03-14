#include "OglForCLI.h"
#include <cmath>

class Ball
{
private:
    EVec3f m_pos, m_velo;
    float  m_radi;

public:
    Ball(float radi, EVec3f& pos, EVec3f& velo)
    {
        m_pos = pos;
        m_velo = velo;
        m_radi = radi;
    }

    Ball(const Ball& src)
    {
        m_pos = src.m_pos;
        m_velo = src.m_velo;
        m_radi = src.m_radi;
    }

    void Step()
    {
        float dt = 0.33;

        const float max_width = 127.0 - m_radi;
        const float max_height = 63.5 - m_radi;

        m_pos += m_velo * dt;

        
        m_velo += EVec3f(0, -1.0, 0) * dt;
        m_velo *= 0.99;
        if (m_pos[1] < 0)
        {
            m_velo[1] *= -0.97;
            m_pos[1] = 0.00001;
        }
        

        m_velo *= 1.0;
        //壁に反射
        if (std::fabs(m_pos[0])>max_width)
        {
            m_velo[0] *= -1.0;        
        }
        if (std::fabs(m_pos[2]) > max_height)
        {
            m_velo[2] *= -1.0;
        }


    }

    void Draw()
    {
        glTranslated(m_pos[0], m_pos[1], m_pos[2]);
        DrawSphere();
        glTranslated(-m_pos[0], -m_pos[1], -m_pos[2]);
    }

    void DrawSphere()
    {
        const int    N = 5;
        const double M_PI = 3.141592;

        glEnable(GL_DEPTH_TEST);
        //Material 
        float   shin[1] = { 64 };
        EVec4f  spec(1, 1, 1, 0.5); //拡散
        EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);   //ハイライト
        EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);   //ベースカラー
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec.data());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff.data());
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi.data());
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

        glEnable(GL_LIGHTING);  //ライトスイッチオン
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);

        

        glBegin(GL_TRIANGLES);
        for (int y = 0; y < N; ++y)
        {
            for (int x = 0; x < N; ++x)
            {
                double t1 = (x) / (double)N * 2.0 * M_PI;
                double t2 = (x + 1) / (double)N * 2.0 * M_PI;
                double p1 = (y) / (double)N * 1.0 * M_PI - 0.5 * M_PI;
                double p2 = (y + 1) / (double)N * 1.0 * M_PI - 0.5 * M_PI;

                glNormal3d(cos(t1) * cos(p1), sin(p1), sin(t1) * cos(p1) );
                glVertex3d(cos(t1) * cos(p1) * 2.855, sin(p1) * 2.855, sin(t1) * cos(p1) * 2.855);
                glNormal3d(cos(t2) * cos(p2), sin(p2) , sin(t2) * cos(p2) );
                glVertex3d(cos(t2) * cos(p2) * 2.855, sin(p2) * 2.855, sin(t2) * cos(p2) * 2.855);
                glNormal3d(cos(t2) * cos(p1) , sin(p1) , sin(t2) * cos(p1) );
                glVertex3d(cos(t2) * cos(p1) * 2.855, sin(p1) * 2.855, sin(t2) * cos(p1) * 2.855);

                glNormal3d(cos(t1) * cos(p1) , sin(p1) , sin(t1) * cos(p1) );
                glVertex3d(cos(t1) * cos(p1) * 2.855, sin(p1) * 2.855, sin(t1) * cos(p1) * 2.855);
                glNormal3d(cos(t1) * cos(p2) , sin(p2) , sin(t1) * cos(p2) );
                glVertex3d(cos(t1) * cos(p2) * 2.855, sin(p2) * 2.855, sin(t1) * cos(p2) * 2.855);
                glNormal3d(cos(t2) * cos(p2) , sin(p2) , sin(t2) * cos(p2));
                glVertex3d(cos(t2) * cos(p2) * 2.855, sin(p2) * 2.855, sin(t2) * cos(p2) * 2.855);

            }
        }

        glEnd();
    }

};