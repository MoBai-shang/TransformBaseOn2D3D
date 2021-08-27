#include "nehewidget.h"
#include "ui_nehewidget.h"
#include<QAction>
#include <math.h>
#include <qimage.h>
#include<QKeyEvent>
#include "nehewidget.h"
#include<QMessageBox>
#include<QColorDialog>
#include<QInputDialog>
#include <QMouseEvent>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QtGui/qevent.h>
NeHeWidget::NeHeWidget( QWidget* parent, const char* name, bool fs )
    : QGLWidget(parent)
{
  xRot = yRot = zRot = 0.0;
  hold = 0.0;
    m_Light = false;
    m_Deep = -12.0f;
  wiggle_count = 0;

  fullscreen = fs;
  setGeometry( x0, y0, width, height );
  if ( fullscreen )
    showFullScreen();

  startTimer( 5 );

}
void NeHeWidget::contextMenuEvent(QContextMenuEvent *){
    // 主菜单
    MainMenu = new QMenu(this);
    //主菜单的 子项
    QAction *option1 = new QAction(MainMenu);
    option1->setText("旗面");
    QAction *option2 = new QAction(MainMenu);
    option2->setText("控制");
    QAction *option3 = new QAction(MainMenu);
    option3->setText("灯光");
    QAction *option4 = new QAction(MainMenu);
    option4->setText("切屏");
    QAction *option5 = new QAction(MainMenu);
    option5->setText("光源");
    QList<QAction*> actionList;
    actionList<<option1<<option2<<option3<<option4;
    //添加子项到主菜单
    MainMenu->addActions(actionList);
    QMenu *menu1=new QMenu();
    QAction *floatAction=new QAction("飘动",menu1);
    connect(floatAction,SIGNAL(triggered(bool)), this, SLOT(Click1()));
    QAction *notfloatAction=new QAction("静止",menu1);
    connect(notfloatAction,SIGNAL(triggered(bool)), this, SLOT(Click2()));
    QList<QAction*> menu1List;

    menu1List<<floatAction<<notfloatAction;
    menu1->addActions(menu1List);
    option1->setMenu(menu1);

    QMenu *menu2=new QMenu();
    QAction *motionAction=new QAction("运动",menu2);
    connect(motionAction,SIGNAL(triggered(bool)), this, SLOT(Click3()));
    QAction *notmotionAction=new QAction("束缚",menu2);
     connect(notmotionAction,SIGNAL(triggered(bool)), this, SLOT(Click4()));
    QList<QAction*> menu2List;
    menu2List<<motionAction<<notmotionAction;
    menu2->addActions(menu2List);
    option2->setMenu(menu2);

    QMenu *menu3=new QMenu();
    QAction *lightAction=new QAction("开灯",menu3);
    connect(lightAction,SIGNAL(triggered(bool)), this, SLOT(Click5()));
    QAction *nolightAction=new QAction("关灯",menu3);
     connect(nolightAction,SIGNAL(triggered(bool)), this, SLOT(Click6()));
    QList<QAction*> menu3List;
    menu3List<<lightAction<<nolightAction;
    menu3->addActions(menu3List);
    option3->setMenu(menu3);

    QMenu *menu4=new QMenu();
    QAction *fullAction=new QAction("全屏",menu4);
    connect(fullAction,SIGNAL(triggered(bool)), this, SLOT(Click8()));
    QAction *halfAction=new QAction("半屏",menu4);
     connect(halfAction,SIGNAL(triggered(bool)), this, SLOT(Click9()));
    QList<QAction*> menu4List;
    menu4List<<fullAction<<halfAction;
    menu4->addActions(menu4List);
    option4->setMenu(menu4);

    QMenu *menu5=new QMenu();
    QAction *xAction=new QAction("x方向",menu5);
    connect(xAction,SIGNAL(triggered(bool)), this, SLOT(Click11()));
    QAction *yAction=new QAction("y方向",menu5);
     connect(yAction,SIGNAL(triggered(bool)), this, SLOT(Click12()));
     QAction *zAction=new QAction("z方向",menu5);
      connect(zAction,SIGNAL(triggered(bool)), this, SLOT(Click13()));
    QList<QAction*> menu5List;
    menu5List<<xAction<<yAction<<zAction;
    menu5->addActions(menu5List);
    option5->setMenu(menu5);
    //主菜单添加子菜单
    MainMenu->addMenu(menu1);
    MainMenu->addMenu(menu2);
    MainMenu->addMenu(menu3);
    MainMenu->addMenu(menu5);

    MainMenu->addMenu(menu4);

    QAction *lineAction=new QAction("线条",MainMenu);
    connect(lineAction,SIGNAL(triggered(bool)), this, SLOT(Click15()));
    MainMenu->addAction(lineAction);
    QAction *colorAction=new QAction("取色",MainMenu);
    connect(colorAction,SIGNAL(triggered(bool)), this, SLOT(Click14()));
    MainMenu->addAction(colorAction);
    QAction *helpAction=new QAction("帮助",MainMenu);
    connect(helpAction,SIGNAL(triggered(bool)), this, SLOT(Click7()));
    MainMenu->addAction(helpAction);
    QAction *closeAction=new QAction("退出",MainMenu);
    connect(closeAction,SIGNAL(triggered(bool)), this, SLOT(Click10()));
    MainMenu->addAction(closeAction);
      // 移动到当前鼠标所在未知
      MainMenu->exec(QCursor::pos());

}
void NeHeWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void NeHeWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x())/2.f ;// width();
    GLfloat dy = GLfloat(event->y() - lastPos.y())/2.f;// height();
    if(event->buttons() & Qt::LeftButton){
        xRot -=  dy;
        yRot -=  dx;
        updateGL();
    }
    lastPos = event->pos();
}

void NeHeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Click14();
}
NeHeWidget::~NeHeWidget()
{
}

void NeHeWidget::initializeGL()
{
  //loadGLTextures();

  glEnable( GL_TEXTURE_2D );
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0, 0.0, 0.0, 0.5 );
  glClearDepth( 1.0 );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
  glPolygonMode( GL_BACK, GL_FILL );
  glPolygonMode( GL_FRONT, GL_LINE );

  for ( int x = 0; x < 45; x++ )
  {
    for ( int y = 0; y < 45; y++ )
    {
      points3D[x][y][0] = float( ( x/5.0 ) - 4.5 );
      points3D[x][y][1] = float( ( y/5.0 ) - 4.5 );
      points3D[x][y][2] = float( sin( ( ( ( x/5.0 ) * 40.0 )/360.0 ) * 3.141592654 * 2.0 ) );
    }
  }
  GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};  //环境光参数
      GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  //漫散光参数
      GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; //光源位置
      glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //设置环境光
      glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //设置漫射光
      glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //设置光源位置
      glEnable(GL_LIGHT1);                                //启动一号光源
}

void NeHeWidget::paintGL()
{
  int x, y;
  float float_x, float_y, float_xb, float_yb;

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();

  glTranslatef( 0.0, 0.0, m_Deep );

  glRotatef( xRot, 1.0, 0.0, 0.0 );
  glRotatef( yRot, 0.0, 1.0, 0.0 );
  glRotatef( zRot, 0.0, 0.0, 1.0 );

  glBindTexture( GL_TEXTURE_2D, texture[0] );
    glColor3f(colorx,colory,colorz);
    glLineWidth(lineWidth);
  glBegin( GL_QUADS );

  switch (lightPosion) {
  case 1:
      glNormal3f(1.0f, 0.0f, 0.0f);
      break;
  case 2:
      glNormal3f(0.0f, 1.0f, 0.0f);
      break;
  case 3:
      glNormal3f(0.0f, 0.0f, 1.0f);
      break;
  }

    for ( x = 0; x < 44; x++ )
    {
      for ( y = 0; y < 44; y++ )
      {
          float rate=44;
        float_x = float(x)/rate;
        float_y = float(y)/rate;
        float_xb = float(x+1)/rate;
        float_yb = float(y+1)/rate;

        glTexCoord2f( float_x, float_y );

        glVertex3f( points3D[x][y][0], points3D[x][y][1], points3D[x][y][2] );

        glTexCoord2f( float_x, float_yb );
        glVertex3f( points3D[x][y+1][0], points3D[x][y+1][1], points3D[x][y+1][2] );

        glTexCoord2f( float_xb, float_yb );
        glVertex3f( points3D[x+1][y+1][0], points3D[x+1][y+1][1], points3D[x+1][y+1][2] );

        glTexCoord2f( float_xb, float_y );
        glVertex3f( points3D[x+1][y][0], points3D[x+1][y][1], points3D[x+1][y][2] );
      }
    }
  glEnd();
    if(isfloating)
    {
        if ( wiggle_count == 2 )
        {
          for ( y = 0; y < 45; y++ )
          {
            hold = points3D[0][y][2];
            for ( x = 0; x < 44; x++ )
            {
              points3D[x][y][2] = points3D[x+1][y][2];
            }
            points3D[44][y][2] = hold;
          }
          wiggle_count = 0;
        }
        wiggle_count++;
    }
  if(ismotion)
  {
      xRot += 0.3f;
      yRot += 0.2f;
      zRot += 0.4f;
  }

}

void NeHeWidget::resizeGL( int width, int height )
{
  if ( height == 0 )
  {
    height = 1;
  }
  glViewport( 0, 0, (GLint)width, (GLint)height );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  GLfloat zNear = 0.1;
  GLfloat zFar = 100.0;
  GLfloat aspect = (GLfloat)width/(GLfloat)height;
  GLfloat fH = tan(GLfloat(90.0/360.0*3.14159))*zNear;
  GLfloat fW = fH * aspect;
  glFrustum(-fW, fW, -fH, fH, zNear, zFar);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

void NeHeWidget::timerEvent(QTimerEvent*)
{
  updateGL();
}

void NeHeWidget::keyPressEvent( QKeyEvent *e )
{
  switch ( e->key() )
  {
  case Qt::Key_F2:
    fullscreen = !fullscreen;
    if ( fullscreen )
    {
      showFullScreen();
    }
    else
    {
      showNormal();
      setGeometry( x0, y0, width, height );
    }
    update();
    break;
   case Qt::Key_Up:
      xRot-=3;
      break;
  case Qt::Key_Down:
     xRot+=3;
     break;
  case Qt::Key_Left:
     yRot-=3;
     break;
  case Qt::Key_Right:
     yRot+=3;
     break;
  case Qt::Key_L:                                     //L为开启关闭光源的切换键
      m_Light = !m_Light;
      if (m_Light)
      {
          glEnable(GL_LIGHTING);                      //开启光源
      }
      else
      {
          glDisable(GL_LIGHTING);                     //关闭光源
      }
      break;
  case Qt::Key_Plus:                                //PageUp按下使木箱移向屏幕内部
      m_Deep += 0.3f;
      break;
  case Qt::Key_Minus:                              //PageDown按下使木箱移向观察者
      m_Deep -= 0.3f;
      break;
  case Qt::Key_Escape:
    close();
  }
}
void NeHeWidget::wheelEvent(QWheelEvent *event)    // 滚轮事件，滚轮默认滚动一下是15度，此时date（）函数会返回15*8=120的整数，当滚轮远离返回正值，反之负值。
{

    if(event->delta() > 0){                    // 当滚轮远离使用者时
       zRot+=3;
    }
    else{                                     // 当滚轮向使用者方向旋转时
        zRot-=3;
    }

}
void NeHeWidget::loadGLTextures()
{

}
void NeHeWidget::Click1()
{
        isfloating=true;
}
void NeHeWidget::Click2()
{
        isfloating=false;
}
void NeHeWidget::Click4()
{
        ismotion=false;
}

void NeHeWidget::Click3()
{
        ismotion=true;
}
void NeHeWidget::Click5()
{
    m_Light=true;
    glEnable(GL_LIGHTING);                      //开启光源
}

void NeHeWidget::Click6()
{
    glDisable(GL_LIGHTING);                     //关闭光源
    m_Light=false;
}
void NeHeWidget::Click7()
{
    QString content="鼠标：\n     双击：取色\n     滚轮：z轴旋转\n     左键拖动：旋转控制\n键盘:\n     左右方向键：y轴旋转\n     上下方向键：x轴旋转\n     L键：灯光\n     加减键：缩放\n     F2键：切屏\n     Esc键：退出";
    QMessageBox::information(this, "帮助", content);

}
void NeHeWidget::Click8()
{
    fullscreen=true;
    showFullScreen();
    update();
}
void NeHeWidget::Click9()
{
    fullscreen=false;
    showNormal();
    setGeometry( x0, y0, width, height );
    update();
}
void NeHeWidget::Click10()
{
    close();
}
void NeHeWidget::Click11()
{
    lightPosion=1;
}
void NeHeWidget::Click12()
{
    lightPosion=2;
}
void NeHeWidget::Click13()
{
    lightPosion=3;
}
void NeHeWidget::Click14()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if(color.red()+color.green()+color.blue()>0)
    {
        colorx=float(color.red()/255.f);
        colory=float(color.green()/255.f);
        colorz=float(color.blue()/255.f);
    }
}
void NeHeWidget::Click15()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "提示",
                                                       "输入线宽度（0-10）",
                                                       QLineEdit::Normal,
                                                       "1",
                                                       &isOK);
    if(isOK&&text.toFloat()>0) {
        lineWidth=text.toFloat();
        if(lineWidth>10) lineWidth=10.;
    }
}
