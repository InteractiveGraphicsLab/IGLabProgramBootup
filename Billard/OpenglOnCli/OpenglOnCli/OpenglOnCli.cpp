#include "stdafx.h"
#include "MainForm.h"
#include "EventManager.h"

#include <iostream>

using namespace System;
using namespace OpenglOnCli;


[STAThreadAttribute]
int main()
{
  MainForm::GetInst()->ShowDialog();  
  return 0;
}
