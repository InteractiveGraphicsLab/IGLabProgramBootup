#include "pch.h"
#include <iostream>
#include "MainForm.h" //<-- �ǉ�

using namespace System;
using namespace FirstOglCLI; //<-- �ǉ�

int main(array<System::String ^> ^args)
{
  std::cout << "hello, world. printf �f�o�b�O�͂���Ȋ����ōs���I\n";
  MainForm::GetInst()->ShowDialog();
  return 0;
}
