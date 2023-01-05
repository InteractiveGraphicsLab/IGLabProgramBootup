#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>


class GLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
  Q_OBJECT
public:
  GLWidget(QWidget *parent = nullptr);
  virtual ~GLWidget();
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  void button1Clicked();
  void button2Clicked();

  void	mouseMoveEvent(QMouseEvent *e);
  void	mousePressEvent(QMouseEvent *e);
  void	mouseReleaseEvent(QMouseEvent *e);
};

#endif // GLWIDGET_H
