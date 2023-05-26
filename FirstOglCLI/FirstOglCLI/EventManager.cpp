#include "pch.h"
#include "EventManager.h"
#include <fstream>
#include <iostream>
#include <string>
//using namespace std;

static double M_PI = 3.141592;



EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  m_balls.push_back(Ball(1.0f, EVec3f(-3.0f,-2.0f,15.0f), EVec3f(0.2f,0.01f,0.01f)));
  m_green.push_back(Green());
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

    m_green[0].DrawGreen();
    m_balls[0].Draw();
 
}

void EventManager::StepBall()
{
    EVec3f pos = m_balls[0].GetPos();
    EVec3f velo = m_balls[0].GetVelo();
    float radi = m_balls[0].GetRadi();

    /*if (pos[2] <= radi && fabs(velo[2]) < 0.03)
        velo[2] = 0;
    else*/
    
    m_balls[0].SetPos(pos + velo);
}


void EventManager::Bound()
{
    std::vector<YPolygon> polys = m_green[0].GetPolys();

    EVec3f p0 = polys[0].GetP0();
    EVec3f p1 = polys[0].GetP1();
    EVec3f p2 = polys[0].GetP2();
    EVec3f normal = polys[0].GetNormal();
    float t, u;

    EVec3f pos = m_balls[0].GetPos();
    EVec3f velo = m_balls[0].GetVelo();
    float radi = m_balls[0].GetRadi();
    float dist = (pos - p0).dot(normal);
    
    EVec3f b_m_pos = pos - (dist * normal);
    EVec3f op1 = (p1 - p0).cross(b_m_pos - p1);
    EVec3f op2 = (p2 - p1).cross(b_m_pos - p2);
    EVec3f op3 = (p0 - p2).cross(b_m_pos - p0);
    
    float ip1 = op1.dot(op2);
    float ip2 = op1.dot(op3);

    //メッシュの内側判定
    if ((ip1 > 0) && (ip2 > 0)) { //内側

        //衝突
        if (dist <= radi) {

            //ボールをメッシュ上に戻す
            t = radi / dist;
            m_balls[0].SetPos(pos + ((radi - dist) * normal));// +((-velo - ((-velo.dot(normal)) * normal)).normalized() * t));

            //ボールの速度減衰
            u = fabs(velo.dot(normal.normalized()));
            EVec3f v1 = normal.normalized() * u * 0.6f;
            EVec3f v2 = velo + normal.normalized() * u;
            m_balls[0].SetVelo(v1 + v2);

        }
    }
}




void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLの視点を回転させる準備
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


void EventManager::Step()
{
    m_balls[0].Step();
    StepBall();
    Bound();
}
