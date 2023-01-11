#pragma once

#pragma unmanaged
#include "OglForCLI.h"
#include "ttexmesh.h"
#include "OglImage.h"


class EventManager
{
private:
  TTexMesh m_mesh;
  OGLImage2D4 m_img;
  bool m_isL, m_isR, m_isM; //マウスボタンの状態
  EventManager();

public:
  //シングルトンクラス（see デザインパターン, シングルトン）
  static EventManager* GetInst() {
    static EventManager p;
    return &p;
  }
  void DrawScene();
  void LBtnDown(int x, int y, OglForCLI* ogl);
  void MBtnDown(int x, int y, OglForCLI* ogl);
  void RBtnDown(int x, int y, OglForCLI* ogl);
  void LBtnUp(int x, int y, OglForCLI* ogl);
  void MBtnUp(int x, int y, OglForCLI* ogl);
  void RBtnUp(int x, int y, OglForCLI* ogl);
  void MouseMove(int x, int y, OglForCLI* ogl);

  void Step();

  void LoadObj(std::string obj_name, std::string texture_name) {
    m_mesh.initialize(obj_name.c_str());
    m_img.Allocate(texture_name.c_str());
    m_img.FlipInY();
  }



  void LoadMatrxTxt(std::string fname, OglForCLI* ogl);
};
#pragma managed
