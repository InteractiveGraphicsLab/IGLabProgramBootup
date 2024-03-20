#include "pch.h"
#include "MainForm.h"
#include <iostream>
#pragma unmanaged
#include "EventManager.h"
#pragma managed

using namespace FirstOglCLI;

#pragma comment( lib, "opengl32.lib" )


#pragma comment( lib, "glu32.lib"    )
#pragma comment( lib, "gdi32.lib"    )
#pragma comment( lib, "User32.lib"   )


static void CALLBACK MyTimerProc(
  HWND hWnd,           // handle of CWnd that called SetTimer
  UINT nMsg,           // WM_TIMER
  UINT_PTR nIDEvent,   // timer identification
  DWORD dwTime         // system time
)
{
  //std::cout << "timer���Ă΂ꂽ\n";   //�R�����g��\������
  EventManager::GetInst()->Step();    //Step�֐���ǂ��
  MainForm::GetInst()->RedrawPanel(); //Redraw����
}


MainForm::MainForm(void)
{
  m_ogl = 0; //opengl�{��
  InitializeComponent();
  m_ogl = new OglForCLI(GetDC((HWND)m_panel->Handle.ToPointer()));
  m_ogl->SetBgColor(0.3f, 0.3f, 0.3f, 0.5f);
  m_ogl->SetCam(EVec3f(0, 20, 0), EVec3f(0, 0, 0), EVec3f(1, 0, -1)); //�J�����ʒu�ύX

  SetTimer((HWND)m_panel->Handle.ToPointer(), 1, 10, MyTimerProc); //�ǉ� 33��10
}

void MainForm::RedrawPanel()
{
  if (m_ogl == 0) return;
  m_ogl->OnDrawBegin(m_panel->Width, m_panel->Height, 45.0, 0.01f, 300.0f);
  EventManager::GetInst()->DrawScene();
  m_ogl->OnDrawEnd();
}

System::Void MainForm::m_panel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
  RedrawPanel();//�ĕ`��I!
}

System::Void MainForm::m_panel_Resize(System::Object^ sender, System::EventArgs^ e)
{
  RedrawPanel();//�ĕ`��I!
}

System::Void MainForm::m_panel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
  if (e->Button == System::Windows::Forms::MouseButtons::Left) EventManager::GetInst()->LBtnDown(e->X, e->Y, m_ogl);
  if (e->Button == System::Windows::Forms::MouseButtons::Middle) EventManager::GetInst()->MBtnDown(e->X, e->Y, m_ogl);
  if (e->Button == System::Windows::Forms::MouseButtons::Right) EventManager::GetInst()->RBtnDown(e->X, e->Y, m_ogl);
}

System::Void MainForm::m_panel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
  if (e->Button == System::Windows::Forms::MouseButtons::Left) EventManager::GetInst()->LBtnUp(e->X, e->Y, m_ogl);
  if (e->Button == System::Windows::Forms::MouseButtons::Middle) EventManager::GetInst()->MBtnUp(e->X, e->Y, m_ogl);
  if (e->Button == System::Windows::Forms::MouseButtons::Right) EventManager::GetInst()->RBtnUp(e->X, e->Y, m_ogl);
}

System::Void MainForm::m_panel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
  //std::cout << "�}�E�X���������@" << e->X << " " << e->Y << "\n";
  EventManager::GetInst()->MouseMove(e->X, e->Y, m_ogl);
  //RedrawPanel(); //�ĕ`��I!
}

System::Void MainForm::m_button1_Click(System::Object^ sender, System::EventArgs^ e)
{
  //std::cout << "�{�^��1�������ꂽ\n";
}

System::Void MainForm::m_button2_Click(System::Object^ sender, System::EventArgs^ e)
{
  //std::cout << "�{�^��2�������ꂽ\n";
}


