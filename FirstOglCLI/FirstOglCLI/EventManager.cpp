#include "pch.h"
#include "EventManager.h"
#include "Ball.h"
#include "Stage.h"
#define _USE_MATH_DEFINES
#include "math.h"

EventManager::EventManager()
{
    isL_ = isR_ = isM_ = isBtn2_ = false;

    balls_.push_back(Ball(EVec3f(10.0f, 0.5f, 10.0f), EVec3f(0.0f, 0, 0.0f)));
    balls_.push_back(Ball(EVec3f(30.0f, 0.5f, 10.0f), EVec3f(0.0f, 0, 0.0f)));
    //balls_.push_back(Ball(EVec3f(5.0f, 0.5f, 8.0f), EVec3f(-1.5f, 0, -1.0f)));
}

void EventManager::DrawScene()
{
    glLineWidth(2.0f);
    glDisable(GL_LIGHTING);//“d‹C‚ðÁ‚·

    //OpenGL‚Å3–{‚Ì’¼ü‚ð•`‚­
    glBegin(GL_LINES);
    glColor3d(1, 0, 0); glVertex3d(0, 0, 0); glVertex3d(10, 0, 0);
    glColor3d(0, 1, 0); glVertex3d(0, 0, 0); glVertex3d(0, 10, 0);
    glColor3d(0, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, 10);
    glEnd();

    //” •`‰æ
    glColor3d(0, 0.5, 0);
    //stage.DrawFloor();
    Stage::GetInst()->DrawLeftWall();
    Stage::GetInst()->DrawRightWall();
    Stage::GetInst()->DrawTopWall();
    Stage::GetInst()->DrawBottomWall();

    if (ball_index_ != -1 && isBtn2_)
    {
        glColor3d(0.5, 0.5, 0);
        glBegin(GL_LINES);
        glVertex3f(str_p_[0], str_p_[1], str_p_[2]);
        glVertex3f(end_p_[0], end_p_[1], end_p_[2]);
        glEnd();
    }
    

    glEnable(GL_DEPTH_TEST);
    //Material 
    float   shin[1] = { 64 };
    EVec4f  spec(1, 1, 1, 0.5);
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

    
    //balls_[0].SetVelo(end_pos_);
    for (int i = 0; i < balls_.size(); i++)
    {
        balls_[i].Draw();
    }
}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
    isL_ = true;
    if (isBtn2_)
    {
        ray_ = ogl->GetCursorRay1(EVec2i(x, y));
        EVec3f p = std::get<0>(ray_);
        EVec3f d = std::get<1>(ray_);
        float t = (0.5f - p[1]) / d[1];
        str_p_ = EVec3f(p[0] + t * d[0], 0.5f, p[2] + t * d[2]);
        end_p_ = EVec3f(p[0] + t * d[0], 0.5f, p[2] + t * d[2]);
        float dist = 0;
        for (int i = 0; i < balls_.size(); i++)
        {
            ball_p_ = balls_[i].GetPos();
            dist = sqrt(pow(str_p_[0] - ball_p_[0], 2) + pow(str_p_[2] - ball_p_[2], 2));
            if (dist <= 0.5f)
            {
                ball_index_ = i;
                balls_[ball_index_].SetVelo(EVec3f(0, 0, 0));
                break;
            }
            else
                ball_index_ = -1;
        }
    }
    else
        ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGL‚ÌŽ‹“_‚ð‰ñ“]‚³‚¹‚é€”õ
}

void EventManager::MBtnDown(int x, int y, OglForCLI* ogl)
{
    isM_ = true;
    ogl->BtnDown_Zoom(EVec2i(x, y));
}

void EventManager::RBtnDown(int x, int y, OglForCLI* ogl)
{
    isR_ = true;
    ogl->BtnDown_Rot(EVec2i(x, y));
}

void EventManager::LBtnUp(int x, int y, OglForCLI* ogl)
{
    isL_ = false;
    if (ball_index_ != -1 && isBtn2_)
    {
        float d = sqrt(pow(str_p_[0] - end_p_[0], 2) + pow(str_p_[2] - end_p_[2], 2));
        balls_[ball_index_].SetVelo(EVec3f(end_p_[0], 0, end_p_[2]) / d);
    }
    ogl->BtnUp();
}

void EventManager::MBtnUp(int x, int y, OglForCLI* ogl)
{
    isM_ = false;
    ogl->BtnUp();
}

void EventManager::RBtnUp(int x, int y, OglForCLI* ogl)
{
    isR_ = false;
    ogl->BtnUp();
}

void EventManager::MouseMove(int x, int y, OglForCLI* ogl)
{
    if (!isL_ && !isR_ && !isM_) return;
    if (isBtn2_)
    {
        ray_ = ogl->GetCursorRay1(EVec2i(x, y));
        EVec3f p = std::get<0>(ray_);
        EVec3f d = std::get<1>(ray_);
        float t = (0.5f - p[1]) / d[1];
        end_p_ = EVec3f(p[0] + t * d[0], 0.5f, p[2] + t * d[2]);
    }
    else
        ogl->MouseMove(EVec2i(x, y));
}

void EventManager::SetMode(const bool& b)
{
    isBtn2_ = b;
}


void EventManager::Step()
{
    for (int i = 0; i < balls_.size(); i++)
    {
        for (int j = i + 1; j < balls_.size(); j++)
        {
            balls_[i].BallCollision(balls_[j]);
        }
        balls_[i].Step(0.33f);
    }
}
