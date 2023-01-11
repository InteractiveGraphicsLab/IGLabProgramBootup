#include "pch.h"
#include <iostream>
#include "MainForm.h" //<-- 追加

using namespace System;
using namespace FirstOglCLI; //<-- 追加

int main(array<System::String ^> ^args)
{
  std::cout << "hello, world. printf デバッグはこんな感じで行う！\n";
  MainForm::GetInst()->ShowDialog();
  return 0;
}
