#include "pch.h"
#include "EventManager.h"
#include "Value.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  m_balls.push_back(Ball(EVec3f(0, 2, 0), EVec3f(1, 0, 0)));
  m_balls.push_back(Ball(EVec3f(2, 2, 0), EVec3f(-1, 0, 0)));
  m_balls.push_back(Ball(EVec3f(-1, 3, 1), EVec3f(0, 0, 0)));
  m_balls.push_back(Ball(EVec3f(3, 3, 0), EVec3f(-3, 0, 0)));
  billiard = Billiard();
}

void EventManager::DrawScene()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHT2);

	glEnable(GL_LIGHT3);

	m_balls[0].Draw();
	m_balls[1].Draw();
	m_balls[2].Draw();
	m_balls[3].Draw();

	billiard.DrawTable();

	glDisable(GL_LIGHTING);//電気を消す
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

void EventManager::Collision(const int& i,const int& j)
{
	EVec3f pos1 = m_balls[i].GetPos();
	EVec3f pos2 = m_balls[j].GetPos();
	EVec3f vel1 = m_balls[i].GetVel();
	EVec3f vel2 = m_balls[j].GetVel();
	EVec3f vel1x, vel1y, vel2x, vel2y;
	EVec3f p = m_balls[i].GetPos() - m_balls[j].GetPos();

	p.normalize();

	vel1x = vel1.dot(p) * p;
	vel1y = vel1 - vel1x;

	vel2x = vel2.dot(-p) * -p;
	vel2y = vel2 - vel2x;

	std::swap(vel1x, vel2x);

	vel1 = vel1x + vel1y;
	vel2 = vel2x + vel2y;

	m_balls[i].SetVel(vel1);
	m_balls[j].SetVel(vel2);

	pos1 += 0.01f * vel1;
	pos2 += 0.01f * vel2;

	m_balls[i].SetPos(pos1);
	m_balls[j].SetPos(pos2);
}

void EventManager::Step()
{
	for (int i = 0; i < m_balls.size(); i++)
	{
		if (m_balls[i].GetPos()[1] < radius) //床との反射
		{
			EVec3f pos = m_balls[i].GetPos();
			EVec3f vel = m_balls[i].GetVel();
			m_balls[i].SetPos(EVec3f(pos[0], radius, pos[2]));
			m_balls[i].SetVel(EVec3f(vel[0], -0.8 * vel[1], vel[2]));
		}

		for (int j = 0; j < m_balls.size(); j++) //ボール同士の衝突
		{
			if (i != j && (m_balls[i].GetPos() - m_balls[j].GetPos()).norm() < radius * 2)
			{
				Collision(i, j);
			}
		}

		m_balls[i].Step(0.01f); //ボールの移動
	}
}
