// SolidSimulator.cpp : ���C�� �v���W�F�N�g �t�@�C���ł��B

#include "stdafx.h"
#include "stdio.h"
#include "MainForm.h"

using namespace System;
using namespace SolidSimulator;

[STAThreadAttribute]
int main()
{
  printf("show dialog here!!");
  MainForm::getInst()->ShowDialog();
  return 0;
}

