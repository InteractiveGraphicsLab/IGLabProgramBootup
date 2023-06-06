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
  m_balls.push_back(Ball(2.0f, EVec3f(-10.0f,-20.0f,3.0f), EVec3f(2.0f,2.0f,0)));
  m_green.push_back(Green());
  m_green[0].LoadObj("C:/Users/Taisei Yamazaki/Documents/GitHub/IGLabProgramBootup/FirstOglCLI/kussyon.obj");
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
    //std::cout << m_balls[0].GetPos() << "\n\n\n";
 
}

void EventManager::StepBall()
{
    EVec3f pos = m_balls[0].GetPos();
    EVec3f velo = m_balls[0].GetVelo();
    float radi = m_balls[0].GetRadi();

    //if (pos[2] <= radi && fabs(velo[2]) < 0.04)
    //    velo[2] = 0;

    //重力
    m_balls[0].SetVelo(velo - 9.8 * 0.033 * EVec3f::UnitZ());

    m_balls[0].SetPos(pos + velo);
}


void EventManager::Bound()
{
    std::vector<YPolygon> polys = m_green[0].GetPolys();

    EVec3f pos = m_balls[0].GetPos();
    EVec3f velo = m_balls[0].GetVelo();
    float radi = m_balls[0].GetRadi();


    for (int i = 0; i < polys.size(); i++) {

        EVec3f p0 = polys[i].GetP0();
        EVec3f p1 = polys[i].GetP1();
        EVec3f p2 = polys[i].GetP2();
        EVec3f normal = polys[i].GetNormal();
       
        if ((p0 - pos).norm() <= 10.0f) {
            float dist = (pos - p0).dot(normal); //メッシュとボールの距離

            if (dist > -10.0f) {
                EVec3f b_m_pos = pos - (dist * normal); //メッシュ平面上のボールの位置
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
                        float t = radi / dist;
                        m_balls[0].SetPos(pos + ((radi - dist) * normal)); //+((-velo - ((-velo.dot(normal)) * normal)).normalized() * t));
                        
                        //ボールの速度減衰
                        float u = fabs(velo.dot(normal));
                        if ((u * 0.3) <= 0.4f) {                            
                            if (((velo + normal * u) * 0.9f).norm() <= 0.04f) {
                                m_balls[0].SetVelo(EVec3f(0, 0, 0)); //ボールの速さを０にする
                            }
                            else {
                                m_balls[0].SetVelo((velo + normal * u) * 0.9f);
                            }
                        }

                        else {
                            EVec3f v1 = normal * u * 0.3f;
                            EVec3f v2 = (velo + normal * u) * 0.9f;
                            m_balls[0].SetVelo(v1 + v2);
                        }                   
                        
                    }
                }

            }

            //EVec3f b_m_pos = pos - (dist * normal); //メッシュ平面上のボールの位置
            //EVec3f op1 = (p1 - p0).cross(b_m_pos - p1);
            //EVec3f op2 = (p2 - p1).cross(b_m_pos - p2);
            //EVec3f op3 = (p0 - p2).cross(b_m_pos - p0);

            //float ip1 = op1.dot(op2);
            //float ip2 = op1.dot(op3);


            ////メッシュの内側判定
            //if ((ip1 > 0) && (ip2 > 0)) { //内側
            //    std::cout << "ip1：" << ip1 << "  ip2：" << ip2 << "\n\n\n";

            //    //衝突
            //    if (dist <= radi) {
            //        std::cout << "メッシュ番号：" << i << "\nボールとメッシュの距離：" << dist << "\n\n\n";

            //        //ボールをメッシュ上に戻す
            //        float t = radi / dist;
            //        m_balls[0].SetPos(pos + ((radi - dist) * normal));//  +((-velo - ((-velo.dot(normal)) * normal)).normalized() * t));

            //        //ボールの速度減衰
            //        float u = fabs(velo.dot(normal));
            //        EVec3f v1 = normal * u * 0.6f;
            //        EVec3f v2 = velo + normal * u;
            //        m_balls[0].SetVelo(v1 + v2);

            //    }
            //}

        }

        
        //float dist = (pos - p0).dot(normal); //メッシュとボールの距離

        //EVec3f b_m_pos = pos - (dist * normal); //メッシュ平面上のボールの位置
        //EVec3f op1 = (p1 - p0).cross(b_m_pos - p1);
        //EVec3f op2 = (p2 - p1).cross(b_m_pos - p2);
        //EVec3f op3 = (p0 - p2).cross(b_m_pos - p0);

        //float ip1 = op1.dot(op2);
        //float ip2 = op1.dot(op3);


        ////メッシュの内側判定
        //if ((ip1 > 0) && (ip2 > 0)) { //内側
        //    //std::cout << "ip1：" << ip1 << "  ip2：" << ip2 << "\n\n\n";

        //    //衝突
        //    if (dist <= radi) {
        //        std::cout << "メッシュ番号：" << i << "\nボールとメッシュの距離：" << dist << "\n\n\n";

        //        //ボールをメッシュ上に戻す
        //        float t = radi / dist;
        //        //m_balls[0].SetPos(pos + ((radi - dist) * normal));//  +((-velo - ((-velo.dot(normal)) * normal)).normalized() * t));

        //        //ボールの速度減衰
        //        float u = fabs(velo.dot(normal));
        //        EVec3f v1 = normal * u * 0.6f;
        //        EVec3f v2 = velo + normal * u;
        //        m_balls[0].SetVelo(v1 + v2);

        //    }
        //}

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
    StepBall();
    Bound();
}
