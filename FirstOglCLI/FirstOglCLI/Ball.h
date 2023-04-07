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

    EVec3f GetPos()
    {
        return m_pos;
    }

    void SetPos(EVec3f pos)
    {
        m_pos = pos;
    }

    EVec3f GetVelo()
    {
        return m_velo;
    }

    void SetVelo(EVec3f velo)
    {
        m_velo = velo;
    }

    void Step()
    {
        float dt = 0.33f;

        const float max_width = 127.0f - m_radi;
        const float max_height = 63.5f - m_radi;
        m_velo += EVec3f(0, -1.0, 0) * dt; //v=v+at
        m_pos += m_velo * dt;   //x=x+vt

        
       
        //床に反射
        if (m_pos[1] <= m_radi)
        {
            m_pos[1] = m_radi;
            m_velo[1] *= -0.8f; //反射減衰
            
            if (std::fabs(m_velo[1]) < 0.01f) m_velo[1] = 0.0f;
        }
        
        
        //m_velo *= 1.0;
        //壁に反射
        if (std::fabs(m_pos[0]) >= max_width)
        {
            m_velo[0] *= -1.0f; //反射減衰
        }

        if (std::fabs(m_pos[2]) >= max_height)
        {
            m_velo[2] *= -1.0f; //反射減衰
        }

        m_velo[1] *= 0.99f; //速度減衰(動きを見たいためx,zはそのまま)
    }

    bool Collision(Ball& other)
    {
        float e = 1.0f; //反発係数
        EVec3f m2_pos = other.GetPos();
        EVec3f m2_velo = other.GetVelo();
        
        std::cout << m_pos[0] << "\n";
        std::cout << m2_pos[0] << "\n";

        //2点間の距離
        float distance = sqrt(pow(m_pos[0] - m2_pos[0], 2.0f) + pow(m_pos[1] - m2_pos[1], 2.0f) + pow(m_pos[2] - m2_pos[2], 2.0f));

        std::cout << "dis:" << distance<< "\n";

        //m1の方向ベクトル
        EVec3f m1_direction;
        for (int i = 0; i < 3; ++i) {
            m1_direction[i] = (m2_pos[i] - m_pos[i]) / distance;
        }
        
        //m2の方向ベクトル
        EVec3f m2_direction = -1* m1_direction;

        //m1のm2に対しての垂直・平行方向速度成分
        float dot = m_velo.dot(m1_direction);
        EVec3f v1_vertical = dot * m1_direction;
        EVec3f v1_parallel = m_velo - v1_vertical;

        //m2のm1に対しての垂直・平行方向速度成分
        dot = m2_velo.dot(m2_direction);
        EVec3f v2_vertical = dot * m2_direction;
        EVec3f v2_parallel = m2_velo - v2_vertical;


        //衝突判定
        if (distance < 2.0f * m_radi) {

            std::cout << "--------------------------" << "\n";

            EVec3f V1 = v1_vertical + v2_vertical;
            EVec3f V2 = v1_vertical - v2_vertical;
            
            EVec3f v1_aftervertical = (V1 - e * V2) / 2.0f;
            EVec3f v2_aftervertical = ((V1 + e * V2) / 2.0f);



            m_velo = v1_aftervertical + v1_parallel;
            other.SetVelo(v2_aftervertical + v2_parallel);
            
            return true;
        }

        return 0;
    }

    void Draw()
    {
        glTranslated(m_pos[0], m_pos[1], m_pos[2]);
        DrawSphere();
        glTranslated(-m_pos[0], -m_pos[1], -m_pos[2]);
    }

    void DrawSphere()
    {
        const int    N = 20;
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
                glVertex3d(cos(t1) * cos(p1) * m_radi, sin(p1) * m_radi, sin(t1) * cos(p1) * m_radi);
                glNormal3d(cos(t2) * cos(p2), sin(p2) , sin(t2) * cos(p2) );
                glVertex3d(cos(t2) * cos(p2) * m_radi, sin(p2) * m_radi, sin(t2) * cos(p2) * m_radi);
                glNormal3d(cos(t2) * cos(p1) , sin(p1) , sin(t2) * cos(p1) );
                glVertex3d(cos(t2) * cos(p1) * m_radi, sin(p1) * m_radi, sin(t2) * cos(p1) * m_radi);

                glNormal3d(cos(t1) * cos(p1) , sin(p1) , sin(t1) * cos(p1) );
                glVertex3d(cos(t1) * cos(p1) * m_radi, sin(p1) * m_radi, sin(t1) * cos(p1) * m_radi);
                glNormal3d(cos(t1) * cos(p2) , sin(p2) , sin(t1) * cos(p2) );
                glVertex3d(cos(t1) * cos(p2) * m_radi, sin(p2) * m_radi, sin(t1) * cos(p2) * m_radi);
                glNormal3d(cos(t2) * cos(p2) , sin(p2) , sin(t2) * cos(p2));
                glVertex3d(cos(t2) * cos(p2) * m_radi, sin(p2) * m_radi, sin(t2) * cos(p2) * m_radi);

            }
        }

        glEnd();
    }

};