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
  //std::cout << "timerが呼ばれた\n";   //コメントを表示して
  EventManager::GetInst()->Step();    //Step関数を読んで
  MainForm::GetInst()->RedrawPanel(); //Redrawする
}


MainForm::MainForm(void)
{
  m_ogl = 0;
  InitializeComponent();
  m_ogl = new OglForCLI(GetDC((HWND)m_panel->Handle.ToPointer()));
  m_ogl->SetBgColor(0.3f, 0.3f, 0.3f, 0.5f);
  m_ogl->SetCam(EVec3f(3.5f, -42.5f, 9.0f), EVec3f(-3.0f, 2.5f, -0.1f), EVec3f(0.1f, -0.6f, 0.6f));

  SetTimer((HWND)m_panel->Handle.ToPointer(), 1, 33, MyTimerProc); //追加
}

void MainForm::RedrawPanel()
{
  if (m_ogl == 0) return;
  m_ogl->OnDrawBegin(m_panel->Width, m_panel->Height, 45.0, 0.01f, 300.0f);
  EventManager::GetInst()->DrawScene();
  std::cout << m_ogl->GetCamPos() << "\n\n" << m_ogl->GetCamCnt() << "\n\n" << m_ogl->GetCamUp() << "\n\n\n\n";
  m_ogl->OnDrawEnd();
}

System::Void MainForm::m_panel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
  RedrawPanel();//再描画！!
}

System::Void MainForm::m_panel_Resize(System::Object^ sender, System::EventArgs^ e)
{
  RedrawPanel();//再描画！!
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
  std::cout << "マウスが動いた　" << e->X << " " << e->Y << "\n";
  EventManager::GetInst()->MouseMove(e->X, e->Y, m_ogl);
  RedrawPanel(); //再描画！!
}

System::Void MainForm::m_button1_Click(System::Object^ sender, System::EventArgs^ e)
{
  std::cout << "ボタン1が押された\n";
}

System::Void MainForm::m_button2_Click(System::Object^ sender, System::EventArgs^ e)
{
  std::cout << "ボタン2が押された\n";
}


