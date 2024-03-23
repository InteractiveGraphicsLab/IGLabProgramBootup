#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
    m_isL = m_isR = m_isM = false;

    balls_.push_back(Ball(EVec3f(0.0f, 0.5f, 0.0f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.5f, 0.0f, 0.0f), EVec3f(0.0f, 0.0f, 0.0f), 0.5f));
    balls_.push_back(Ball(EVec3f(7.0f, 0.5f, 0.0f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(-0.5f, 0.0f, 0.0f), EVec3f(0.0f, 0.0f, 0.0f), 0.5f));
}

void EventManager::DrawScene()
{
    glLineWidth(2.0f);
    glDisable(GL_LIGHTING);//電気を消す
    
    //OpenGLで3本の直線を描く
    glBegin(GL_LINES);
    glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
    glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
    glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
    glEnd();
    
    for (int i = 0; i < balls_.size(); i++)
    {
        balls_[i].Draw();
    }
    BilliardsTable::GetInst()->Draw();
}

void EventManager::CollideBall()
{
    return;
}

void EventManager::CollideTable()
{
    return;
}

void EventManager::Collision()
{
    const float E = 1.0;

    for (int i = 0; i < balls_.size(); i++)
    {
        for (int j = i+1; j < balls_.size(); j++)
        {
            EVec3f d = balls_[j].GetPos() - balls_[i].GetPos();
            EVec3f dn = d.normalized();
            float radi = balls_[i].GetRadi() + balls_[j].GetRadi();

            if (d.norm() > radi) continue;

            EVec3f vec_par1 = balls_[i].GetVelo().dot(dn) * dn;
            EVec3f vec_ver1 = balls_[i].GetVelo() - vec_par1;
            EVec3f vec_par2 = balls_[j].GetVelo().dot(dn) * dn;
            EVec3f vec_ver2 = balls_[j].GetVelo() - vec_par2;
            balls_[i].SetVelo(vec_par2 + vec_ver1);
            balls_[j].SetVelo(vec_par1 + vec_ver2);

            float distance = (radi - d.norm()) / 2.0f;
            balls_[i].SetPos(balls_[i].GetPos() - dn * distance);
            balls_[j].SetPos(balls_[j].GetPos() + dn * distance);
        }
    }

    /*
    for (int i = 0; i < balls_.size(); i++)
    {
        for (int j = 0; j < cuboids_.size(); j++)
        {

        }
    }
    */
}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
    m_isL = true;
    ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLの視点を回転させる準備

    for (int i = 0; i < balls_.size(); i++) 
    {
        if (isSelectedBall(x, y, ogl, balls_[i])) Stop(balls_[i]);
    }
}

void EventManager::MBtnDown(int x, int y, OglForCLI* ogl)
{
    m_isM = true;
    ogl->BtnDown_Zoom(EVec2i(x, y));
}

void EventManager::RBtnDown(int x, int y, OglForCLI* ogl)
{
    m_isR = true;
    ogl->BtnDown_Rot(EVec2i(x, y));
}

void EventManager::LBtnUp(int x, int y, OglForCLI* ogl)
{
    m_isL = false;
    ogl->BtnUp();
}

void EventManager::MBtnUp(int x, int y, OglForCLI* ogl)
{
    m_isM = false;
    ogl->BtnUp();
}

void EventManager::RBtnUp(int x, int y, OglForCLI* ogl)
{
    m_isR = false;
    ogl->BtnUp();
}

void EventManager::MouseMove(int x, int y, OglForCLI* ogl)
{
    if (!m_isL && !m_isR && !m_isM) return;
    ogl->MouseMove(EVec2i(x, y));
}


void EventManager::MouseForce(int x, int y, OglForCLI* ogl) 
{
    EVec3f ray_pos, ray_dir;
    if (!m_isL && !m_isR && !m_isM) return;
    ogl->GetCursorRay(x, y, ray_pos, ray_dir);
    std::cout << x << " " << y << " " << ray_pos << " " << ray_dir;
}

void EventManager::Step()
{
    for (int i = 0; i < balls_.size(); i++)
    {
        balls_[i].Step();
    }
    Collision();
}

void EventManager::Init()
{

}

void EventManager::Stop(Ball& ball)
{
    ball.SetVelo(EVec3f(0.0f, 0.0f, 0.0f));
}

bool EventManager::isSelectedBall(int x, int y, OglForCLI* ogl, const Ball& ball)
{
    EVec3f ray_pos, ray_dir;
    ogl->GetCursorRay(x, y, ray_pos, ray_dir);

    EVec3f b_pos = ball.GetPos();
    float b_radi = ball.GetRadi();
    float a = ray_dir.dot(ray_dir);
    float b = 2.0f * (ray_pos - b_pos).dot(ray_dir);
    float c = (ray_pos - b_pos).dot(ray_pos - b_pos) - b_radi * b_radi;
    float D = b * b - 4.0f * a * c;
    if (D > 0.0f) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}