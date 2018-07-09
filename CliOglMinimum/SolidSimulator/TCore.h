#pragma once

#include "OglForCLI.h"

class TCore
{
  //singleton
  //����������邽�߁C�m����single thread�ł���i�K��getInst����x�ǂ�ŏ��������s��

private:
  TCore();
public:
  static TCore* getInst(){
    static TCore p;
    return &p;
  }

private:
  bool m_bL, m_bR, m_bM; //mouse button flg

public:
  ~TCore();

  void LBtbnDown(EVec2i &p, OglForCLI *ogl);
  void RBtbnDown(EVec2i &p, OglForCLI *ogl);
  void MBtbnDown(EVec2i &p, OglForCLI *ogl);
  void LBtbnUp  (EVec2i &p, OglForCLI *ogl);
  void RBtbnUp  (EVec2i &p, OglForCLI *ogl);
  void MBtbnUp  (EVec2i &p, OglForCLI *ogl);
  void MouseMove(EVec2i &p, OglForCLI *ogl);
  void DrawScene();

};

