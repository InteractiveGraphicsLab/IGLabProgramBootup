#ifndef OGLFORQT_H_
#define OGLFORQT_H_

#include "tmath.h"
#include <iostream>

//Windows固有の書き方をしてしまう（これでも動くが クロスプラットフォームではなくなるしQtの作法からは外れそう。。）
#include "windows.h"
#include "GL/gl.h"
#include "GL/glu.h"


class OglCameraParam
{
public:
  EVec3f m_pos; //camera position
  EVec3f m_cnt; //camera focus point
  EVec3f m_up ; //camera Up (y-axis) direction

  OglCameraParam()
  {
    m_pos = EVec3f(0, 0, 10);
    m_cnt = EVec3f(0, 0, 0 );
    m_up  = EVec3f(0, 1, 0 );
  }

  OglCameraParam( const OglCameraParam &src)
  {
    Copy(src);
  }

  OglCameraParam &operator=(const OglCameraParam &src)
  {
    Copy(src);
    return *this;
  }

  void Copy (const OglCameraParam &src)
  {
    m_pos = src.m_pos;
    m_cnt = src.m_cnt;
    m_up  = src.m_up ;
  }

  //camera rotation/zoom/translate by mouse operation
  // (mouse_dx, mouse_dy) : mouse offsets in 2D
  //
  void RotateCamera( int mouse_dx, int mouse_dy)
  {
    float theta = -mouse_dx / 200.0f;
    float phi   = -mouse_dy / 200.0f;

    EVec3f x_dir = ((m_cnt - m_pos).cross(m_up)).normalized();
    Eigen::AngleAxisf rotTheta(theta, m_up);
    Eigen::AngleAxisf rotPhi  (  phi, x_dir      );
    m_up  = rotPhi * rotTheta * m_up;
    m_pos = rotPhi * rotTheta * (m_pos - m_cnt) + m_cnt;
  }

  void ZoomCamera( int mouse_dy)
  {
    EVec3f newEyeP = m_pos + mouse_dy / 80.0f * (m_cnt - m_pos);
    if ((newEyeP - m_cnt).norm() > 0.02f) m_pos = newEyeP;
  }

  void TranslateCamera(int mouse_dx, int mouse_dy)
  {
    float c = (m_pos - m_cnt).norm() / 900.0f;
    EVec3f x_dir = ((m_pos - m_cnt).cross(m_up)).normalized();
    EVec3f t = c * mouse_dx * x_dir + c * mouse_dy * m_up;
    m_pos += t;
    m_cnt += t;
  }

  void ZoomCameraByOffset(float offset)
  {
    EVec3f rayD = (m_cnt - m_pos);
    float  len = rayD.norm();
    if (offset > len) return;
    rayD /= len;
    m_pos = m_pos + offset * rayD;
  }

  void Set(const EVec3f &pos, const EVec3f &cnt, const EVec3f up)
  {
    m_pos = pos;
    m_cnt = cnt;
    m_up  = up ;
  }

};



class OglForQt
{
private: 
  OglCameraParam m_camera; 
  EVec2i m_mouse_pos   ;
  EVec4f m_bkgrnd_color;

  enum {
    BTN_NON, BTN_TRANS, BTN_ZOOM, BTN_ROT
  } m_mousebtn_state;


public:

  ~OglForQt() {}

  OglForQt()
  {
    m_camera.Set(EVec3f(0, 0, 10), EVec3f(0, 0, 0), EVec3f(0, 1, 0));
    m_bkgrnd_color = EVec4f(0, 0, 0, 0.5);
    return;
  }


  void OnDrawBegin(
    int    screem_width,
    int    screen_height,
    double fovY      = 45.0,
    double view_near = 0.02,
    double view_far  = 700.0)
  {
    static bool isFirst = true;
    if(isFirst)
    {
      SetDefaultProperties();
    }


    glViewport(0, 0, screem_width, screen_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovY, screem_width / (double)screen_height, view_near, view_far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(m_camera.m_pos[0], m_camera.m_pos[1], m_camera.m_pos[2],
              m_camera.m_cnt[0], m_camera.m_cnt[1], m_camera.m_cnt[2],
              m_camera.m_up[0], m_camera.m_up[1], m_camera.m_up[2]);
    glClearColor( m_bkgrnd_color[0],
                  m_bkgrnd_color[1],
                  m_bkgrnd_color[2],
                  m_bkgrnd_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
  }


  void OnDrawEnd()
  {
    glFinish();
  }


  inline EVec3f GetCamPos() const { return m_camera.m_pos; }
  inline EVec3f GetCamCnt() const { return m_camera.m_cnt; }
  inline EVec3f GetCamUp()  const { return m_camera.m_up;  }
  inline void   SetCam(const EVec3f& pos, const EVec3f& cnt, const EVec3f& up)
  {
    m_camera.Set(pos, cnt, up);
  }
 
  inline void SetBgColor(const EVec4f &bg) 
  { 
    m_bkgrnd_color = bg; 
  }

  inline void SetBgColor(float r, float g, float b, float a) 
  { 
    m_bkgrnd_color << r, g, b, a; 
  }

  //Mouse Listener for Camera manipuration
  void BtnDown_Trans(const EVec2i &p)
  {
    m_mouse_pos = p;
    m_mousebtn_state = BTN_TRANS;
  }
  void BtnDown_Zoom(const EVec2i &p)
  {
    m_mouse_pos = p;
    m_mousebtn_state = BTN_ZOOM;
  }
  void BtnDown_Rot(const EVec2i &p)
  {
    m_mouse_pos = p;
    m_mousebtn_state = BTN_ROT;
  }
  void BtnUp()
  {
    m_mousebtn_state = BTN_NON;
  }

  void MouseMove(const EVec2i &p)
  {
    if (m_mousebtn_state == BTN_NON) return;
    int dX = p[0] - m_mouse_pos[0];
    int dY = p[1] - m_mouse_pos[1];
    if (m_mousebtn_state == BTN_ROT) m_camera.RotateCamera(dX, dY);
    if (m_mousebtn_state == BTN_ZOOM) m_camera.ZoomCamera(dY);
    if (m_mousebtn_state == BTN_TRANS) m_camera.TranslateCamera(dX, dY);
    m_mouse_pos = p;
  }

  void ZoomCamera(float offset)
  {
    m_camera.ZoomCameraByOffset(offset);
  }

  void unProject_correctY(
    const double cx, 
    const double cy, 
    const double depth, 
    double &x, 
    double &y, 
    double &z)
  {
    double modelMat[16], projMat[16];
    int vp[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMat);
    glGetDoublev(GL_PROJECTION_MATRIX, projMat);
    glGetIntegerv(GL_VIEWPORT, vp);

    gluUnProject(cx, vp[3] - cy, depth, modelMat, projMat, vp, &x, &y, &z);
  }

  void Project(
    const double inX, 
    const double inY, 
    const double inZ,
    double &outX, 
    double &outY,
    double &outZ)
  {
    double model[16], proj[16];
    int vp[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, vp);

    gluProject(inX, inY, inZ, model, proj, vp, &outX, &outY, &outZ);
  }


  inline void GetCursorRay(
    int cx, 
    int cy, 
    EVec3f &ray_pos, 
    EVec3f &ray_dir)
  {
    double x1, y1, z1, x2, y2, z2;
    unProject_correctY(cx, cy, 0.01, x1, y1, z1);
    unProject_correctY(cx, cy, 0.2, x2, y2, z2);

    ray_pos << (float)x1, (float)y1, (float)z1;
    ray_dir << (float)(x2 - x1), (float)(y2 - y1), (float)(z2 - z1);
    ray_dir.normalize();
  }

  inline void GetCursorRay(
      const EVec2i &pt, 
      EVec3f &rayPos, 
      EVec3f &rayDir)
  {
    GetCursorRay(pt[0], pt[1], rayPos, rayDir);
  }

  std::tuple<EVec3f, EVec3f> GetCursorRay1(const EVec2i &pt)
  {
    EVec3f ray_pos, ray_dir;
    GetCursorRay(pt[0], pt[1], ray_pos, ray_dir);
    return std::forward_as_tuple( ray_pos, ray_dir ) ;
  }



  void SetDefaultProperties()
  {
    glClearDepth(1.0f);

    //Material 
    float   shin[1] = { 64 };
    EVec4f  spec(1, 1, 1, 0.5);
    EVec4f  diff(0.5f, 0.5f, 0.5f, 0.5f);
    EVec4f  ambi(0.5f, 0.5f, 0.5f, 0.5f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , spec.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , diff.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , ambi.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

    ////lights
    //glEnable(GL_LIGHTING);
    //EVec4f lPosi[3] = { EVec4f(1000,1000,-1000,1), EVec4f(-1000,1000,-1000,1), EVec4f(1000,-1000,-1000,1) };
    //EVec4f lambi[3] = { EVec4f(1.0f,1.0f,1.0f,1), EVec4f(0,0,0,0)            , EVec4f(0,0,0,0) };
    //EVec4f ldiff[3] = { EVec4f(1.0f,1.0f,1.0f,1), EVec4f(0.5f,0.5f,0.5f,1)   , EVec4f(0.5f,0.5f,0.5f,1) };
    //EVec4f lspec[3] = { EVec4f(0.3f,0.3f,0.3f,1), EVec4f(0.3f,0.3f,0.3f,1)   , EVec4f(0.3f,0.3f,0.3f,1) };

    //for (int i = 0; i < 3; ++i)
    //{
    //  GLenum light = (i == 0) ? GL_LIGHT0 : 
    //                 (i == 1) ? GL_LIGHT1 : GL_LIGHT2;
    //  glLightfv(light, GL_POSITION, lPosi[i].data());
    //  glLightfv(light, GL_AMBIENT , lambi[i].data());
    //  glLightfv(light, GL_DIFFUSE , ldiff[i].data());
    //  glLightfv(light, GL_SPECULAR, lspec[i].data());
    //  glEnable(light);
    //}

    // other general states
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glShadeModel(GL_SMOOTH);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glPolygonMode(GL_FRONT, GL_FILL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
  }

};



/*

inline void t_DrawPolyLine(
  const EVec3f color,
  const float  width,
  const std::vector<EVec3f>& points,
  const bool b_closed = false
)
{
  int N = (int)points.size();
  if (b_closed) N += 1;

  int* idx = new int[N];
  for (int i = 0; i < N; ++i) idx[i] = i;
  if (b_closed) idx[N - 1] = 0;

  glColor3d(color[0], color[1], color[2]);
  glLineWidth(width);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, points.data());
  glDrawElements(GL_LINE_STRIP, N, GL_UNSIGNED_INT, idx);
  glDisableClientState(GL_VERTEX_ARRAY);

  delete[] idx;
}

inline void t_DrawPolyLine(
  const EVec3f  color,
  const float   width,
  const int     num_points,
  const EVec3f* points,
  const bool b_closed = false
)
{
  int N = num_points;
  if (b_closed) N += 1;

  int* idx = new int[N];
  for (int i = 0; i < N; ++i) idx[i] = i;
  if (b_closed) idx[N - 1] = 0;

  glColor3d(color[0], color[1], color[2]);
  glLineWidth(width);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, points);
  glDrawElements(GL_LINE_STRIP, N, GL_UNSIGNED_INT, idx);
  glDisableClientState(GL_VERTEX_ARRAY);

  delete[] idx;
}
*/


#endif
