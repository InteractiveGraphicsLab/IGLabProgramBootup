#include "glwidget.h"
#include <iostream>

#include "GL/gl.h"
#include "GL/glu.h"
#include "tmath.h""


GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
  QSurfaceFormat format;
  format.setVersion(2, 0);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setRenderableType(QSurfaceFormat::OpenGL);
  setFormat(format);
  //this->makeCurrent(); //これでmake currentできる。ここでは不要。
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
  initializeOpenGLFunctions(); // 所持するよりこっちのほうがいいかも。
}

void GLWidget::paintGL()
{
  glClearColor(0.2f,0.1f,0.2f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.2f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
  glEnd();

  glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
}


void GLWidget::button1Clicked()
{
  std::cout << "button1 clicked\n" << std::flush;
}

void GLWidget::button2Clicked()
{
  std::cout << "button2 clicked\n" << std::flush;
}


void GLWidget::mousePressEvent(QMouseEvent *e)
{
  std::cout << "press " << e->x() <<" " << e->y() << " " << e->buttons() << "\n" << std::flush;
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
  std::cout << "move " << e->x() <<" " << e->y() << " " << e->buttons() << "\n" << std::flush;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
  std::cout << "release " << e->x() <<" " << e->y() << " " << e->buttons() << "\n" << std::flush;
}




