#ifndef MYOGLWIDGET_H
#define MYOGLWIDGET_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include "tmath.h"
#include "OglForQt.h"


class MyOglWidget : public QOpenGLWidget
{ 
  Q_OBJECT

private:
  OglForQt m_ogl;

public:
  MyOglWidget(QWidget *parent = nullptr);
  ~MyOglWidget();

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  void button1Clicked();
  void button2Clicked();

  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYOGLWIDGET_H
