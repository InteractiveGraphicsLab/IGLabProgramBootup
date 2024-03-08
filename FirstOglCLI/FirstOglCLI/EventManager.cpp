#include "pch.h"
#include "EventManager.h"

EventManager::EventManager()
{
  m_isL = m_isR = m_isM = false;
  m_balls.push_back(Ball(EVec3f(0, 2, 0), EVec3f(0, 2, 3)));
  m_balls.push_back(Ball(EVec3f(1, 1, 1), EVec3f(2, 0, 4)));
  m_balls.push_back(Ball(EVec3f(-1, 1, 0), EVec3f(0, 2, 0)));
  m_balls.push_back(Ball(EVec3f(0, 3, 0.5), EVec3f(5, 0, 0)));
  billiard_ = Billiard();
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

	billiard_.DrawTable();

	glDisable(GL_LIGHTING);//“d‹C‚ðÁ‚·
}

void EventManager::LBtnDown(int x, int y, OglForCLI* ogl)
{
  m_isL = true;
  ogl->BtnDown_Trans(EVec2i(x, y)); // OpenGL‚ÌŽ‹“_‚ð‰ñ“]‚³‚¹‚é€”õ
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
	EVec3f vel1 = m_balls[i].GetVel();
	EVec3f vel2 = m_balls[j].GetVel();
	EVec3f vel1x, vel1y, vel2x, vel2y;
	EVec3f p = m_balls[i].GetPos() - m_balls[j].GetPos();

	p.normalize();

	vel1x = p * vel1 * p;
	vel1y = vel1 - vel1x;

	vel2x = -p * vel2 * -p;
	vel2y = vel2 - vel2x;

	std::swap(vel1x, vel2x);

	m_balls[i].SetVel(vel1x + vel1y);
	m_balls[j].SetVel(vel2x + vel2y);
}

void EventManager::Step()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_balls[i].GetPos()[1] <= 0)
		{
			EVec3f pos = m_balls[i].GetPos();
			EVec3f vel = m_balls[i].GetVel();
			m_balls[i].SetPos(EVec3f(pos[0], 0.1f, pos[2]));
			m_balls[i].SetVel(EVec3f(vel[0], -vel[1], vel[2]));
		}
		for (int j = 0; j < 4; j++)
		{
			if (i != j && (m_balls[i].GetPos() - m_balls[j].GetPos()).norm() <= 0.2)
			{
				Collision(i, j);
			}
		}
		m_balls[i].Step(0.01f);
	}
}
