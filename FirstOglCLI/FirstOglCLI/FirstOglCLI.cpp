#include "pch.h"
#include <iostream>
#include "MainForm.h" //<-- �ǉ�

using namespace System;
using namespace FirstOglCLI; //<-- �ǉ�

int main(array<System::String ^> ^args)
{
  MainForm::GetInst()->ShowDialog();
  return 0;
}
