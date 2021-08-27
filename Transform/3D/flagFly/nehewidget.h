#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QMainWindow>
#include<QtOpenGL/qgl.h>
#include <qtimer.h>
#include<QAction>

class NeHeWidget : public QGLWidget
{
    Q_OBJECT

public:

  NeHeWidget( QWidget* parent = 0, const char* name = 0, bool fs = false );
  ~NeHeWidget();
  bool m_Light;                                   //光源的开/关
  float m_Deep;
public slots:
    void Click1();
    void Click2();
    void Click3();
    void Click4();
    void Click6();
    void Click5();
    void Click7();
    void Click8();
    void Click9();
    void Click10();
    void Click11();
    void Click12();
    void Click13();
    void Click14();
    void Click15();
protected:
void ShowTextEditMenu(QPoint);
virtual void contextMenuEvent(QContextMenuEvent *event);
  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void keyPressEvent( QKeyEvent *e );
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);//滚轮事件
  void loadGLTextures();
  void timerEvent( QTimerEvent * );
  QMenu *MainMenu;
    QPoint lastPos;
protected:

  bool fullscreen;
  int lightPosion=2;

  GLfloat xRot, yRot, zRot;
  float colorx=0.7,colory=0.7,colorz=0.7;
  GLfloat hold;
  float lineWidth=2.0;
  GLuint texture[1];
  int isfloating=false,ismotion=false;
  float points3D[45][45][3];
  int wiggle_count;
  int x0=640,y0=300,width=640,height=480;
};

#endif // NEHEWIDGET_H
