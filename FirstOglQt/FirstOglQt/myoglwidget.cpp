#include "myoglwidget.h"


MyOglWidget::MyOglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
  QSurfaceFormat format;
  format.setVersion(2, 0);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setRenderableType(QSurfaceFormat::OpenGL);
  setFormat(format);
  //this->makeCurrent(); //これでmake currentできる。ここでは不要。
}


MyOglWidget::~MyOglWidget()
{
}

void MyOglWidget::initializeGL()
{
  m_ogl.SetDefaultProperties();
}

void MyOglWidget::paintGL()
{
  m_ogl.OnDrawBegin(this->width(), this->height());

  glBegin(GL_LINES);
    glColor3d(1,0,0); glVertex3d(0,0,0); glVertex3d(1,0,0);
    glColor3d(0,1,0); glVertex3d(0,0,0); glVertex3d(0,1,0);
    glColor3d(0,0,1); glVertex3d(0,0,0); glVertex3d(0,0,1);
  glEnd();

  glFlush();
}

void MyOglWidget::resizeGL(int w, int h)
{
}

void MyOglWidget::button1Clicked()
{
  std::cout << "btn1!!\n" << std::flush;
}

void MyOglWidget::button2Clicked()
{
  std::cout << "btn2!!\n" << std::flush;
}

void MyOglWidget::mousePressEvent(QMouseEvent *e)
{
  int x = e->position().x(), y = e->position().y();
  std::cout << "press " << x <<" " << y << " " << e->buttons() << "\n" << std::flush;

  EVec2i p = EVec2i(x,y);
  if (e->buttons() == Qt::LeftButton) m_ogl.BtnDown_Rot(p);
  if (e->buttons() == Qt::RightButton) m_ogl.BtnDown_Trans(p);
  if (e->buttons() == Qt::MiddleButton) m_ogl.BtnDown_Zoom(p);
}

void MyOglWidget::mouseMoveEvent(QMouseEvent *e)
{
  int x = e->position().x(), y = e->position().y();
  std::cout << "move " << x <<" " << y << " " << e->buttons() << "\n" << std::flush;
  EVec2i p = EVec2i(x,y);
  m_ogl.MouseMove(p);
  this->repaint();
}

void MyOglWidget::mouseReleaseEvent(QMouseEvent *e)
{
  int x = e->position().x(), y = e->position().y();
  std::cout << "release " << x <<" " << y << " " << e->buttons() << "\n" << std::flush;
  m_ogl.BtnUp();
}


