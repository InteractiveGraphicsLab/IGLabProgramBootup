#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
    m_isL = m_isR = m_isM = false;

    const float radi = 0.5f;

    EVec3f bt_pos = BilliardTable::GetInst()->GetPos();
    float bt_width = BilliardTable::GetInst()->GetWidth();
    float bt_height = BilliardTable::GetInst()->GetHeight();
    float bt_depth = BilliardTable::GetInst()->GetDepth();

    for (int i = 0; i < 1000; ++i)
    {
        const float div = 100.0f;
        float posx = (std::rand() % (int)(2 * div * (bt_width  - radi) + 1) - div * (bt_width  - radi)) / div + bt_pos[0];
        float posy = (std::rand() % (int)(2 * div * (bt_height - radi) + 1) - div * (bt_height - radi)) / div + bt_pos[1];
        float posz = (std::rand() % (int)(2 * div * (bt_depth  - radi) + 1) - div * (bt_depth  - radi)) / div + bt_pos[2];

        const float velox_max = 10.0;
        const float veloy_max = 0.0;
        const float veloz_max = 10.0;
        float velox = (std::rand() % (int)(div * ((velox_max + 1) - velox_max / 2))) / div;
        float veloy = (std::rand() % (int)(div * ((veloy_max + 1) - veloy_max / 2))) / div;
        float veloz = (std::rand() % (int)(div * ((veloz_max + 1) - veloz_max / 2))) / div;

        m_balls.push_back(Ball(
            radi,
            EVec3f(posx, posy, posz),
            EVec3f(velox, veloy, veloz)));
    }

    /*
    m_cuboids.push_back(Cuboid(EVec3f(-10.7f, 2, 0), 0.5f, 2, 10, EVec3f(0, 0, 0)));
    m_cuboids.push_back(Cuboid(EVec3f(10.7f, 2, 0), 0.5f, 2, 10, EVec3f(0, 0, 0)));
    m_cuboids.push_back(Cuboid(EVec3f(0, 2, -10.7f), 10, 2, 0.5f, EVec3f(0, 0, 0)));
    m_cuboids.push_back(Cuboid(EVec3f(0, 2, 10.7f), 10, 2, 0.5f, EVec3f(0, 0, 0)));
    m_cuboids.push_back(Cuboid(EVec3f(0, -0.5f, 0), 10, 0.5f, 10, EVec3f(0, 0, 0)));
    */
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

    BilliardTable::GetInst()->Draw();
    for (int i = 0; i < m_balls.size(); ++i)
    {
        m_balls[i].Draw();
    }
    //for (int i = 0; i < m_cuboids.size(); ++i)
    //{
    //    m_cuboids[i].Draw();
    //}
}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
    m_isL = true;
    EVec3f ray_pos, ray_dir;

    ogl->GetCursorRay(x, y, ray_pos, ray_dir);
    m_idx = PickBall(ray_pos, ray_dir);

    //ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGLの視点を回転させる準備
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
    if (m_idx != -1)
    {
        EVec3f b_pos = m_balls[m_idx].GetPos();
        EVec3f ray_pos, ray_dir;

        ogl->GetCursorRay(x, y, ray_pos, ray_dir);
        float slope = CalcReleaseDist(b_pos, ray_pos, ray_dir);
        std::cout << slope << "\n";

        EVec3f release_pos = slope * ray_dir + ray_pos;
        EVec3f nor_vec = b_pos - release_pos;
        EVec3f b_velo = m_balls[m_idx].GetVelo();
        b_velo += nor_vec;
        m_balls[m_idx].SetVelo(b_velo);
    }

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
    if (!(!m_isL && !m_isR && !m_isM))
        ogl->MouseMove(EVec2i(x, y));
}

void EventManager::Step()
{
    int i, j;
    // Step
    for (i = 0; i < m_balls.size(); ++i)
    {
        m_balls[i].Step();
    }
    for (int i = 0; i < m_cuboids.size(); ++i)
    {
        m_cuboids[i].Step();
    }

    // CollideAndSolve
    for (i = 0; i < m_balls.size(); ++i)
    {
        CollideAndSolve(m_balls[i]);
        for (j = i + 1; j < m_balls.size(); ++j)
        {
            CollideAndSolve(m_balls[i], m_balls[j]);
        }
        for (j = 0; j < m_cuboids.size(); ++j)
        {
            CollideAndSolve(m_balls[i], m_cuboids[j]);
        }



        //m_balls[i].HitCuboid(m_cuboids);
        //m_balls[i].HitBall(m_balls);
    }
}

void EventManager::CollideAndSolve(Ball& b)
{
    EVec3f bt_pos = BilliardTable::GetInst()->GetPos();
    float bt_width = BilliardTable::GetInst()->GetWidth();
    float bt_height = BilliardTable::GetInst()->GetHeight();
    float bt_depth = BilliardTable::GetInst()->GetDepth();

    EVec3f b_pos = b.GetPos();
    float b_radi = b.GetRadi();

    if (fabsf(b_pos[0] - bt_pos[0]) > bt_width - b_radi)
    {
        EVec3f b_velo = b.GetVelo();
        float bt_bounce = BilliardTable::GetInst()->GetBounce();
        b_pos[0] = bt_pos[0] + (bt_width - b_radi) * (b_pos[0] - bt_pos[0]) / fabsf(b_pos[0] - bt_pos[0]);
        b_velo[0] *= -bt_bounce;
        b.SetVelo(b_velo);
        b.SetPos(b_pos);
    }
    if (fabsf(b_pos[1] - bt_pos[1]) > bt_height - b_radi)
    {
        EVec3f b_velo = b.GetVelo();
        float bt_bounce = BilliardTable::GetInst()->GetBounce();
        b_pos[1] = bt_pos[1] + (bt_height - b_radi) * (b_pos[1] - bt_pos[1]) / fabsf(b_pos[1] - bt_pos[1]);
        b_velo[1] *= -bt_bounce;
        b.SetVelo(b_velo);
        b.SetPos(b_pos);
    }
    if (fabsf(b_pos[2] - bt_pos[2]) > bt_depth - b_radi)
    {
        EVec3f b_velo = b.GetVelo();
        float bt_bounce = BilliardTable::GetInst()->GetBounce();
        b_pos[2] = bt_pos[2] + (bt_depth - b_radi) * (b_pos[2] - bt_pos[2]) / fabsf(b_pos[2] - bt_pos[2]);
        b_velo[2] *= -bt_bounce;
        b.SetVelo(b_velo);
        b.SetPos(b_pos);
    }
}

void EventManager::CollideAndSolve(Ball& b1, Ball& b2) // ball to ball
{
    float bounce = 1.0f; // 球の反発係数(未定)

    EVec3f pos1 = b1.GetPos();
    EVec3f pos2 = b2.GetPos();
    float radi1 = b1.GetRadi();
    float radi2 = b2.GetRadi();

    EVec3f diff = pos2 - pos1; // p1p2ベクトル
    float d_size = diff.norm(); // p1p2ベクトルの大きさ
    if (radi1 + radi2 >= d_size) // 衝突判定
    { // 衝突処理
        EVec3f dir = diff.normalized(); // p1p2ベクトルの正規化
        EVec3f velo1 = b1.GetVelo();
        EVec3f velo2 = b2.GetVelo();

        // ベクトルの分割
        EVec3f v1 = dir * velo1.dot(dir);
        EVec3f v2 = velo1 - v1;
        EVec3f v3 = dir * velo2.dot(dir);
        EVec3f v4 = velo2 - v3;

        EVec3f temp = v1;
        v1 = v3;
        v3 = temp;

        pos1 += -dir * (radi1 + radi2 - d_size) / 2;
        pos2 += dir * (radi1 + radi2 - d_size) / 2;

        velo1 = v1 + v2;
        velo2 = v3 + v4;

        b1.SetPos(pos1);
        b2.SetPos(pos2);

        b1.SetVelo(velo1);
        b2.SetVelo(velo2);
    }
}

void EventManager::CollideAndSolve(Ball& b, Cuboid& c) // ball to cuboid
{
    EVec3f b_pos = b.GetPos();
    float b_radi = b.GetRadi();
    EVec3f c_pos = c.GetPos();
    float c_width = c.GetWidth();
    float c_height = c.GetHeight();
    float c_depth = c.GetDepth();

    if (fabsf(b_pos[0] - c_pos[0]) < b_radi + c_width && fabsf(b_pos[1] - c_pos[1]) < c_height && fabsf(b_pos[2] - c_pos[2]) < c_depth)
    {
        EVec3f b_velo = b.GetVelo();
        float bounce = c.GetBounce();
        b_velo[0] *= -bounce;
        b_pos[0] = c_pos[0] + (b_radi + c_width) * (b_pos[0] - c_pos[0]) / fabsf(b_pos[0] - c_pos[0]);
        b.SetVelo(b_velo);
        b.SetPos(b_pos);
    }
    if (fabsf(b_pos[0] - c_pos[0]) < c_width && fabsf(b_pos[1] - c_pos[1]) < b_radi + c_height && fabsf(b_pos[2] - c_pos[2]) < c_depth)
    {
        EVec3f b_velo = b.GetVelo();
        float bounce = c.GetBounce();
        b_velo[1] *= -bounce;
        b_pos[1] = c_pos[1] + (b_radi + c_height) * (b_pos[1] - c_pos[1]) / fabsf(b_pos[1] - c_pos[1]);
        b.SetVelo(b_velo);
        b.SetPos(b_pos);
    }
    if (fabsf(b_pos[0] - c_pos[0]) < c_width && fabsf(b_pos[1] - c_pos[1]) < c_height && fabsf(b_pos[2] - c_pos[2]) < b_radi + c_depth)
    {
        EVec3f b_velo = b.GetVelo();
        float bounce = c.GetBounce();
        b_velo[2] *= -bounce;
        b_pos[2] = c_pos[2] + (b_radi + c_depth) * (b_pos[2] - c_pos[2]) / fabsf(b_pos[2] - c_pos[2]);
        b.SetVelo(b_velo);
        b.SetPos(b_pos);
    }





    /*
    int check[3] = { 1, 1, 1 };
    int count = 0;
    EVec3f b_pos, b_velo, c_pos, c_length;
    float b_radi, c_bounce;

    b_pos = b.GetPos();
    b_radi = b.GetRadi();
    c_pos = c.GetPos();
    c_depth = c.GetDepth();
    c_bounce = c.GetBounce();

    for (int i = 0; i < 3; ++i) { // 衝突判定
        if (c_pos[i] - c_depth[i] <= b_pos[i] && b_pos[i] <= c_pos[i] + c_depth[i])
        {
            check[i] = 0;
            count += 1;
        }
    }
    switch (count) { // 衝突処理
    case 0:
        // 頂点の延長上
        break;
    case 1:
        // 辺の延長上
        break;
    case 2:
        // 面の延長上
        for (int i = 0; i < 3; ++i)
        {
            if (check[i] == 1)
            {
                if (c_pos[i] <= b_pos[i])
                {
                    if (b_pos[i] - c_pos[i] <= b_radi + c_depth[i])
                    {
                        b_pos[i] = c_pos[i] + b_radi + c_depth[i];
                        b.SetPos(b_pos);
                        b_velo = b.GetVelo();
                        b_velo[i] *= -c_bounce;
                        b.SetVelo(b_velo);
                    }
                }
                else
                {
                    if (c_pos[i] - b_pos[i] <= b_radi + c_depth[i])
                    {
                        b_pos[i] = c_pos[i] - b_radi - c_depth[i];
                        b.SetPos(b_pos);
                        b_velo = b.GetVelo();
                        b_velo[i] *= -c_bounce;
                        b.SetVelo(b_velo);
                    }
                }
            }
        }
        break;
    case 3:
        //直方体内部
        break;
    default:
        break;
    }
    */
}

int EventManager::PickBall(EVec3f RayPos, EVec3f RayDir)
{
    float dis = 10000.0;
    int pick_idx = -1;
    for (int i = 0; i < m_balls.size(); ++i)
    {
        EVec3f b_pos = m_balls[i].GetPos();
        float b_radi = m_balls[i].GetRadi();
        float d = (float)pow(RayDir.dot(RayPos - b_pos), 2) - (pow((RayPos - b_pos).norm(), 2) - pow(b_radi, 2));
        if (d > 0 && (RayPos - b_pos).norm() < dis) // 接触
        {
            pick_idx = i;
            dis = (RayPos - b_pos).norm();
        }
    }
    if (pick_idx != -1)
    {
        m_balls[pick_idx].SetVelo(EVec3f(0, 0, 0));
    }
    return pick_idx;
}

float EventManager::CalcReleaseDist(EVec3f TargetPos, EVec3f RayPos, EVec3f RayDir)
{
    float slope = (TargetPos - RayPos).dot(RayDir);
    return slope;
}

