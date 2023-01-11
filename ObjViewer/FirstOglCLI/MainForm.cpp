#include "pch.h"
#include "MainForm.h"
#include <iostream>
#pragma unmanaged
#include "EventManager.h"
#pragma managed

using namespace FirstOglCLI;
using namespace System::Runtime::InteropServices;

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib"    )
#pragma comment( lib, "gdi32.lib"    )
#pragma comment( lib, "User32.lib"   )

/*
static void CALLBACK MyTimerProc(
  HWND hWnd,           // handle of CWnd that called SetTimer
  UINT nMsg,           // WM_TIMER
  UINT_PTR nIDEvent,   // timer identification
  DWORD dwTime         // system time
)
{
  std::cout << "timerが呼ばれた\n";   //コメントを表示して
  EventManager::GetInst()->Step();    //Step関数を読んで
  MainForm::GetInst()->RedrawPanel(); //Redrawする
}
*/

static bool t_showOpenFileDlg
(
  const char* filter,
  std::string& fname
)
{
  OpenFileDialog^ dlg = gcnew OpenFileDialog();
  dlg->Filter = gcnew System::String(filter);
  dlg->Multiselect = false;
  dlg->ShowHelp = true;

  auto a = dlg->ShowDialog();
  if ( a == System::Windows::Forms::DialogResult::Cancel) {
    return false;
  }

  IntPtr mptr = Marshal::StringToHGlobalAnsi(dlg->FileName);
  fname = static_cast<const char*>(mptr.ToPointer());

  return true;
}




MainForm::MainForm(void)
{
  m_ogl = 0;
  InitializeComponent();
  
  m_ogl = new OglForCLI(GetDC((HWND)m_panel->Handle.ToPointer()));
  m_ogl->SetBgColor(0.3f, 0.3f, 0.3f, 0.5f);

  //SetTimer((HWND)m_panel->Handle.ToPointer(), 1, 33, MyTimerProc); //追加
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
  RedrawPanel();
}

System::Void MainForm::m_panel_Resize(System::Object^ sender, System::EventArgs^ e)
{
  RedrawPanel();
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
  EventManager::GetInst()->MouseMove(e->X, e->Y, m_ogl);
  RedrawPanel(); //再描画！!
}

System::Void MainForm::m_button1_Click(System::Object^ sender, System::EventArgs^ e)
{
  std::string fname1, fname2;
  if (!t_showOpenFileDlg("mesh   (*.obj)|*.obj", fname1)) return;
  if (!t_showOpenFileDlg("texture(*.png)|*.png", fname2)) return;

  EventManager::GetInst()->LoadObj(fname1, fname2);
  RedrawPanel(); //再描画！!
}

System::Void MainForm::m_button2_Click(System::Object^ sender, System::EventArgs^ e)
{
  std::cout << "ボタン2が押された\n";
  std::string fname1;
  if (!t_showOpenFileDlg("matrix info text (*.txt)|*.txt", fname1)) return;
  EventManager::GetInst()->LoadMatrxTxt(fname1, m_ogl);





}


