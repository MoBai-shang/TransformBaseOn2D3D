#ifndef MYGL_H
#define MYGL_H
#include<QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class MyGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

    public:
        explicit MyGL(QWidget *parent = 0);

        /******定义结构体用于活性边表AET和新边表NET***********************************/
        typedef struct XET
        {
            int ymax;
            double dx,x;
            struct XET* next;
        }AET,NET;
        /******定义点结构体point******************************************************/
        struct point
        {
            double x;
            int y;
        }polypoint[400];

        int PointNum=0; 	//填充动画时绘制点的数目
        int WIDE = 30,LENGTH=430,HalfWide=WIDE/2,PAUSE=false;
        double Rate=1.0*WIDE/LENGTH;
        int MODEL=0,TRANS2D=false,up=0,mid=0,down=0,COUNT=1,SPEED=2000-20*90,plotpre=true,isFILL=false,TOTAL=0;
        int mouseMovePointx=0,mouseMovePointy=0;
        double recx[400],recy[400];
        double Sx=1,Sy=1;
        int xTrans=false;
        point *POINTS=new point[LENGTH*LENGTH*4];
        point CLICKPOINT2D[3];
        int mouseClickCount=0;
        int ttx[2],tty[2];
        int RTrans=0;
        int TRANS3D=false;
        int R,A,B,mouseposx,mouseposy;
        point mouseMovePoint;
        int getInt(double x);
        int TRANSFLAG1=false,TRANSFLAG2=false,LISTEN=true;
        void DrawCordinateLine(void);
        void putpixel(GLsizei x, GLsizei y);
        void putpixel2(int x, int y);
        void Putpixel(GLsizei x, GLsizei y);
        void swap(GLsizei &x,GLsizei &y);
        void fill();
        void Draw();
        void vertex3f(float* p1,float* p2,float* p3,float* p4);
        void show3D();
        int changeBaseColor=false;
        void rateChange(int xr,int yr,double Sx,double Sy,double x,double y,double &xo,int &yo);
        void symmetric(int x1,int y1,int x2,int y2,point p0,point &p);
        float getDistance(float x1,float y1,float x2,float y2);
        float getAngle(int x1,int y1,int x2,int y2,int x3,int y3);
        void rotate(float t,int xr,int yr,double &x,double &y,double &xo,int &yo);
        void DDACreateLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num);
        void DDADrawLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num);
        void BresenhamLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num);
        void Bresenham2Line(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num);
        void BresenhamCircle(GLsizei x, GLsizei y, GLsizei R, GLsizei num);
        void MidpointCircle(int x0,int y0,int R,int num);
        void MidpointElipse(int x0,int y0,int a,int b,int num);
        void Initial(void);
        void ChangeSize(GLsizei w, GLsizei h);
        void ReDraw(void);
        int Trans(int x);
        void pointTrans(MyGL::point& p,int length);


    protected:
        GLfloat xRot, yRot, zRot;

        virtual void initializeGL();
        virtual void paintGL();
        virtual void resizeGL(int width, int height);
        void mousePressEvent(QMouseEvent *event);//鼠标点击事件
        void mouseReleaseEvent(QMouseEvent *event);//鼠标释放事件
        void mouseDoubleClickEvent(QMouseEvent *event);//鼠标双击事件
        void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件
        void wheelEvent(QWheelEvent *event);//滚轮事件
    public:
        QTimer *timer;                //定义新的定时器

};


#endif // MYGL_H
