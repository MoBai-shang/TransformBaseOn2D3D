#include "mygl.h"
#include<QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QtGui/qevent.h>
#include <exception>
#include<math.h>
MyGL::MyGL(QWidget *parent): QOpenGLWidget(parent) {
	timer = new QTimer();

    showFullScreen();
	//设置时间周期
	connect(timer,SIGNAL(timeout()),this,SLOT(update()));   //连接定时器的信号与槽
	timer->start(SPEED);
}
void MyGL::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(1.0,1.0,1.0,0.5);
	glClearDepth(1.0);
    glShadeModel( GL_SMOOTH );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

}
void MyGL::resizeGL(int width, int height) {
	Q_UNUSED(width);
	Q_UNUSED(height);
}
void MyGL::DrawCordinateLine(void) {
	int i = 0 ;
	//坐标线为黑色
    glColor3f(0.0f, 0.0f ,0.0f);
	glBegin(GL_LINES);
	//画x轴和y轴正半轴
	for (i=-WIDE-HalfWide; i>=-LENGTH; i=i-WIDE) {
		float temp=i*1.0f/LENGTH;
		glVertex2f(temp, -1);
		glVertex2f(temp, 1);
		glVertex2f(-1, temp);
		glVertex2f(1, temp);
	}
	//画x轴y轴负半轴
	for (i=WIDE+HalfWide; i<=LENGTH; i=i+WIDE) {
		float temp=i*1.0f/LENGTH;
		glVertex2f(temp, -1);
		glVertex2f(temp, 1);
		glVertex2f(-1, temp);
		glVertex2f(1, temp);
	}
	//画x=0，y=0
	glColor3f(0.0f, 0.0f ,1.0f);
	float temp=HalfWide*1.0/LENGTH;
	glVertex2f(-1, temp);
	glVertex2f(1, temp);
	glVertex2f(temp, -1);
	glVertex2f(temp,1);
	temp*=-1;
	glVertex2f(-1, temp);
	glVertex2f(1, temp);
	glVertex2f(temp, -1);
	glVertex2f(temp,1);
	glEnd();
}

void MyGL::paintGL() {

        DrawCordinateLine();//绘制坐标线

        switch (MODEL) {
            case 0:
                {
                    if(!(PointNum>1&&!plotpre))
                        for(int i=0; i<PointNum; i++)
                        putpixel2(polypoint[i].x,polypoint[i].y);

                    if(PointNum==2) { //当已经选择了两个端点时进行画线操作
                        if(COUNT==1&&TOTAL==0||TRANS2D&&(down==1||2)&&!LISTEN){
                            if(TRANS2D&&(down==1||2)&&!LISTEN) {TOTAL=0;COUNT=4*LENGTH;}

                        switch(up) {
                            case 0://进行DDA算法给线
                                DDACreateLine(polypoint[0].x,polypoint[0].y,polypoint[1].x,polypoint[1].y,COUNT);
                                break;
                            case 1://进行中点算法给线
                                BresenhamLine(polypoint[0].x,polypoint[0].y,polypoint[1].x,polypoint[1].y,COUNT);
                                break;
                            case 2://进行Bresenham算法给线
                                Bresenham2Line(polypoint[0].x,polypoint[0].y,polypoint[1].x,polypoint[1].y,COUNT);
                                break;
                            case 3://Bresenham算法绘圆
                                //根据两点计算出半径
                                if(COUNT==1||TRANS2D&&down==2)
                                R=int(sqrt(pow(polypoint[0].x-polypoint[1].x,2)+pow(polypoint[0].y-polypoint[1].y,2)));
                                BresenhamCircle(polypoint[0].x,polypoint[0].y,R,COUNT);
                                break;
                            case 4://中点四分法绘圆
                                //根据两点计算出半径
                            //printf("%d****\n",COUNT);
                            if(COUNT==1||TRANS2D&&down==2)
                            R=int(sqrt(pow(polypoint[0].x-polypoint[1].x,2)+pow(polypoint[0].y-polypoint[1].y,2)));

                                MidpointCircle(polypoint[0].x,polypoint[0].y,R,COUNT);
                                break;
                            case 5://中点四分法绘制椭圆
                                //根据两点计算出椭圆长半轴和短半轴
                            if(COUNT==1||TRANS2D&&down==2){
                                A=abs(polypoint[0].x-polypoint[1].x);
                                B=abs(polypoint[0].y-polypoint[1].y);
                                if(A==0) A=B;
                                if(B==0) B=A;}
                                MidpointElipse(polypoint[0].x,polypoint[0].y,A,B,COUNT);
                                break;
                        }
                        }
                        //Draw();
                    }

                    break;
                }
            case 1:
                {
                    //绘制在多边形填充模式下鼠标点选的点
                    for(int i=0; i<PointNum; i++)
                        putpixel2(polypoint[i].x,polypoint[i].y);
                    if(PointNum>1)
                    {
                        if(!TRANS2D)
                        for(int i=0;i<PointNum-1;i++)
                            DDADrawLine(polypoint[i].x,polypoint[i].y,polypoint[i+1].x,polypoint[i+1].y,4*LENGTH);
                        else if(down<2)
                        {
                            for(int i=0;i<PointNum-1;i++)
                                DDADrawLine(polypoint[i].x,polypoint[i].y,polypoint[i+1].x,polypoint[i+1].y,4*LENGTH);
                        }
                        else
                        {
                            if(down>2&&TRANSFLAG1)
                            {
                                int i=0;
                                for(i=0;i<PointNum/2-1;i++)
                                    DDADrawLine(polypoint[i].x,polypoint[i].y,polypoint[i+1].x,polypoint[i+1].y,4*LENGTH);
                                i++;
                                for(;i<PointNum-1;i++)
                                    DDADrawLine(polypoint[i].x,polypoint[i].y,polypoint[i+1].x,polypoint[i+1].y,4*LENGTH);
                            }
                            else {
                                for(int i=0;i<PointNum-1;i++)
                                    DDADrawLine(polypoint[i].x,polypoint[i].y,polypoint[i+1].x,polypoint[i+1].y,4*LENGTH);
                            }
                        }
                    }

                    if(isFILL) { //当选择了填充模式
                        switch(mid) {
                            case 0://多边形扫描线填充
                                if(COUNT==1&&TOTAL==0||TRANS2D&&(down==1||2)&&!LISTEN)
                                {
                                    if(TRANS2D&&(down==1||2)&&!LISTEN) {TOTAL=0;COUNT=4*LENGTH;}
                                    fill();
                                }
                                //Draw();
                                break;
                        }
                    }
                    break;
                }
            }

        if(TOTAL>0)
            Draw();
        if(TRANS2D)
        {
            for(int h=0;h<mouseClickCount;h++)
                putpixel2(ttx[h],tty[h]);
            if(mouseClickCount==2)
                DDADrawLine(ttx[0],tty[0],ttx[1],tty[1],4*LENGTH);
        }

}
int MyGL::Trans(int x) { //将屏幕坐标转为绘图坐标
	int res;
	if(x>LENGTH)
		res=(x+HalfWide-LENGTH)/WIDE;
	else {
		res=(x-HalfWide-LENGTH)/WIDE;
	}
	return res;
}
//绘制一个点，这里用一个正方形表示一个点。
void MyGL::putpixel(int x, int y) {
	glBegin( GL_QUADS );
	glColor3f(1.0,0.0,0.0);
	float xx=x*Rate-Rate/2.0f;
	float yy=y*Rate-Rate/2.0f;
	glVertex3f( xx,  yy+Rate,  0.0 );
	glVertex3f(  xx+Rate,  yy+Rate,  0.0 );
	glVertex3f(  xx+Rate, yy,  0.0 );
	glVertex3f( xx, yy,  0.0 );
	glEnd();
}
void MyGL::putpixel2(int x, int y) {
	glBegin( GL_QUADS );
	glColor3f(0.0,1.0,1.0);
    double xx=x*Rate-Rate/2.0;
    double yy=y*Rate-Rate/2.0;
	glVertex3f( xx,  yy+Rate,  0.0 );
	glVertex3f(  xx+Rate,  yy+Rate,  0.0 );
	glVertex3f(  xx+Rate, yy,  0.0 );
	glVertex3f( xx, yy,  0.0 );
	glEnd();
}
//根据屏幕坐标点绘制画布坐标点
void MyGL::Putpixel(int x, int y) {
	int xx,yy;
	if(x<LENGTH) {
		xx=x-LENGTH-HalfWide;
		xx=xx-xx%WIDE-HalfWide;
	} else {
		xx=x-LENGTH-HalfWide;
		if(xx<0) xx=-HalfWide;
		else
			xx=xx-xx%WIDE+HalfWide;
	}
	if(y<LENGTH) {
		yy=y-LENGTH-HalfWide;
		yy=yy-yy%WIDE-HalfWide;
	} else {
		yy=y-LENGTH-HalfWide;
		if(yy<0) yy=-HalfWide;
		else yy=yy-yy%WIDE+HalfWide;
	}
	float t1=1.0f*xx/LENGTH,t2=1.0f*yy/LENGTH;
	glBegin( GL_QUADS );
	glColor3f(0.0,1.0,1.0);
	glVertex3f( t1,  t2+Rate,  0.0 );
	glVertex3f(  t1+Rate,  t2+Rate,  0.0 );
	glVertex3f(  t1+Rate, t2,  0.0 );
	glVertex3f( t1, t2,  0.0 );
	glEnd();
}
void MyGL::mousePressEvent(QMouseEvent *ev) { //鼠标响应事件
    if(ev->button() == Qt::LeftButton)
    {
        if(!TRANS2D)
            switch (MODEL) {
            case 0:
                { //当前为绘线模式
                    COUNT=1;//使画布上能打点数量初始化为1
                    PointNum=PointNum%2;//使用户通过鼠标输入的点数保持在1和2两者之一，弃掉多余的点
                    TOTAL=0;
                    polypoint[PointNum].x=Trans(ev->x());//将点坐标由绝对坐标转为逻辑相对坐标
                    polypoint[PointNum].y=Trans(2*LENGTH-ev->y());//将点坐标由绝对坐标转为逻辑相对坐标
                    PointNum++;//用户输入的点数加1
                    break;
                }
            case 1:
                { //处于填充模式
                    if(isFILL) { //已经处于填充模式下则转为待填充模式
                        PointNum=0;//多边形点数初始化为0
                        isFILL=false;//未填充
                        TOTAL=0;//待填充点数队列初始化为0
                    }
                    polypoint[PointNum].x=Trans(ev->x());//将点坐标由绝对坐标转为逻辑相对坐标
                    polypoint[PointNum].y=Trans(2*LENGTH-ev->y());//将点坐标由绝对坐标转为逻辑相对坐标
                    PointNum++;//用户输入的多边形点数加1
                    break;
                }
            }
        else {
            switch (down) {
            case 0:
                CLICKPOINT2D[0].x=Trans(ev->x());
                CLICKPOINT2D[0].y=Trans(2*LENGTH-ev->y());
                break;
            case 1:
            {
                if(LISTEN){
                    ttx[0]=Trans(ev->x());
                    tty[0]=Trans(2*LENGTH-ev->y());
                    RTrans=ev->y();
                    CLICKPOINT2D[0].x=ttx[0];
                    CLICKPOINT2D[0].y=tty[0];
                    //mouseposx=ev->x();
                    //mouseposy=ev->y();
                    mouseClickCount=1;
                    setCursor(Qt::ClosedHandCursor);
                    LISTEN=false;
                }
                else
                {
                    CLICKPOINT2D[0].x=Trans(ev->x());
                    CLICKPOINT2D[0].y=Trans(2*LENGTH-ev->y());
                    mouseposx=ev->x();
                    mouseposy=ev->y();

                }
                break;
            }
            case 2://
            {   if(LISTEN){
                ttx[0]=Trans(ev->x());
                tty[0]=Trans(2*LENGTH-ev->y());


                mouseClickCount=1;
                if(xTrans)
                setCursor(Qt::SizeHorCursor);
                else  setCursor(Qt::SizeVerCursor);
                LISTEN=false;}
                break;
            }
            case 3://点对称
            {
                ttx[0]=Trans(ev->x());
                tty[0]=Trans(2*LENGTH-ev->y());
                if(mouseClickCount>0)
                {
                    PointNum/=2;
                    TOTAL/=2;
                    TRANSFLAG1=false;
                    TRANSFLAG2=false;
                }
                for(int i=0; i<PointNum; i++)
                {
                    polypoint[i+PointNum].x=ttx[0]*2-polypoint[i].x;
                    polypoint[i+PointNum].y=tty[0]*2-polypoint[i].y;
                }
                PointNum*=2;
                TRANSFLAG1=true;
                if(TOTAL>0)
                {
                    for(int i=0; i<TOTAL; i++) {
                        POINTS[i+TOTAL].x=ttx[0]*2-POINTS[i].x;
                        POINTS[i+TOTAL].y=tty[0]*2-POINTS[i].y;
                    }
                    TOTAL*=2;
                    TRANSFLAG2=true;
                }

                mouseClickCount=1;
                break;
            }
            case 4:
            {
                if(mouseClickCount>1)
                {
                    mouseClickCount=0;
                    PointNum/=2;
                    TOTAL/=2;
                    TRANSFLAG1=false;
                    TRANSFLAG2=false;
                }
                ttx[mouseClickCount]=Trans(ev->x());
                tty[mouseClickCount]=Trans(2*LENGTH-ev->y());
                 mouseClickCount++;

                if(mouseClickCount==2)
                {
                    for(int i=0; i<PointNum; i++)
                    {
                        symmetric(ttx[0],tty[0],ttx[1],tty[1],polypoint[i],polypoint[i+PointNum]);

                    }
                    PointNum*=2;
                    TRANSFLAG1=true;

                    if(TOTAL>0)
                    {
                        for(int i=0; i<TOTAL; i++) {
                            symmetric(ttx[0],tty[0],ttx[1],tty[1],POINTS[i],POINTS[i+TOTAL]);
                        }
                        TOTAL*=2;
                        TRANSFLAG2=true;
                    }
                }
                break;
            }
            }

        }
     }

}
void MyGL::rateChange(int xr,int yr,double Sx,double Sy,double x,double y,double &xo,int &yo)
{
    xo=getInt( Sx*x - xr*(Sx - 1));
    yo=getInt(Sy*y - yr*(Sy - 1));
}
void MyGL::symmetric(int x1,int y1,int x2,int y2,point p0,point &p)
{
        double a=y2-y1;
        double b=x1-x2;
        double c=x2*y1-y2*x1;

        double t;
        double tems,temc;
        double x=p0.x,y=p0.y;

        if(x1==x2)
        {
            if(a>0) t=-3.1415926/2;
            else if(a<0) t=3.1415926/2;
            else return;
            tems=0,temc=-1;
        }
        else if(y1==y2)
        {
            p.x=x;
            p.y=getInt(2*y1-y);
            return;
        }
        else {
            t=atan(-a/b);
            tems=sin(2*t),temc=cos(2*t);
        }

        p.x=getInt(x*temc+y*tems+(c*(temc-1))/a);
        p.y=getInt(x*tems-y*temc+(c*tems)/a);

}
void MyGL::mouseMoveEvent(QMouseEvent *ev) {

    if(TRANS2D)
    {
        mouseMovePoint.x=Trans(ev->x());
        mouseMovePoint.y=Trans(2*LENGTH-ev->y());
        switch (down) {
        case 0:
        {
            int dx=int(mouseMovePoint.x-CLICKPOINT2D[0].x);
            int dy=int(mouseMovePoint.y-CLICKPOINT2D[0].y);
            for(int i=0; i<PointNum; i++)
            {
                polypoint[i].x+=dx;
                polypoint[i].y+=dy;
            }
            if(TOTAL>0)
            {
                for(int i=0; i<TOTAL; i++) {
                    POINTS[i].x+=dx;
                    POINTS[i].y+=dy;
                }
            }
           break;
        }
        case 1:
        {
            if(!LISTEN)
            {
                float angle=getAngle(CLICKPOINT2D[0].x,CLICKPOINT2D[0].y,ttx[0],tty[0],mouseMovePoint.x,mouseMovePoint.y);
                if((ev->x()-mouseposx)*(mouseposy-RTrans)<0) angle*=-1;
                mouseposx=ev->x();
                mouseposy=ev->y();
                for(int i=0; i<PointNum; i++)
                {
                    rotate(angle,ttx[0],tty[0],recx[i],recy[i],polypoint[i].x,polypoint[i].y);

                }
            }

           break;
        }


        }
    CLICKPOINT2D[0].x=mouseMovePoint.x;
    CLICKPOINT2D[0].y=mouseMovePoint.y;
    }
}

float MyGL::getDistance(float x1,float y1,float x2,float y2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
float MyGL::getAngle(int x2,int y2,int x1,int y1,int x3,int y3)
{
    float c=getDistance(x1,y1,x2,y2);
    float a=getDistance(x2,y2,x3,y3);
    float b=getDistance(x1,y1,x3,y3);
    float angle=acos((b*b+c*c-a*a)/(2*b*c));
    if(x1==x2)
    {
        if (x1==x3) return 0;
        else if(x1<x3) return -angle;
        else return angle;
    }
    return angle;
}
void MyGL::rotate(float t,int xr,int yr,double &x,double &y,double &xo,int &yo)
{
    double tx=x*cos(t) - xr*(cos(t) - 1) - y*sin(t) + yr*sin(t);
    double ty=y*cos(t) - yr*(cos(t) - 1) + x*sin(t) - xr*sin(t);
    x=tx;y=ty;
    xo=getInt(tx);
    yo=getInt(ty);

}
void MyGL::mouseReleaseEvent(QMouseEvent *ev) {

}
void MyGL::mouseDoubleClickEvent(QMouseEvent *event) // 鼠标双击事件
{
    if(event->button() == Qt::LeftButton){             // 如果是鼠标左键按下
        if(MODEL==1)
        {
            isFILL=true;
            COUNT=1;
            TOTAL=0;
        }
    }
}
void MyGL::wheelEvent(QWheelEvent *event)    // 滚轮事件，滚轮默认滚动一下是15度，此时date（）函数会返回15*8=120的整数，当滚轮远离返回正值，反之负值。
{
    if(TRANS2D&&down==2&&!LISTEN){
    if(event->delta() > 0){                    // 当滚轮远离使用者时
       if(xTrans)
           Sx+=0.05;
       else Sy+=0.05;// 进行放大

    }else{                                     // 当滚轮向使用者方向旋转时
        if(xTrans)
        {Sx-=0.05;if(Sx<0.3) Sx=0.3;}
        else {Sy-=0.05; if(Sy<0.3) Sy=0.3;}       // 进行缩小

    }
    for(int i=0; i<PointNum; i++)
    {
        rateChange(ttx[0],tty[0],Sx,Sy,recx[i],recy[i],polypoint[i].x,polypoint[i].y);
    }
}
}
int MyGL::getInt(double x) { //将浮点数据转为整数
    if(x<0)
        return (int(x-0.5));
    else
        return (int(x+0.5));
}
//图元填充，多边形线性扫描
void MyGL::fill() {
    int MaxY=-LENGTH;
    int MinY = LENGTH;
    int i;
    for(i = 0; i < PointNum; i++ ) {
        if( polypoint[i].y > MaxY ) {
            MaxY = polypoint[i].y;
        }
        if( polypoint[i].y < MinY ) {
            MinY = polypoint[i].y;
        }
    }
    //初始化AET表，即初始化活跃边表-------------------------------------
    AET *pAET = new AET;
    pAET->next = NULL;
    //初始化NET表，即初始化边表------------------------------------
    NET *pNET[2*LENGTH+1];
    for( i = MinY; i <= MaxY; i++ ) {
        pNET[i+LENGTH] = new NET;
        pNET[i+LENGTH]->next = NULL;
    }
    //扫描并建立NET表，即建立边表------------------------------
    for( i = MinY; i <= MaxY; i++ ) {
        for( int j = 0; j < PointNum; j++ ) {
            if( polypoint[j].y == i) {
                if( polypoint[ (j-1+PointNum) % PointNum ].y > polypoint[j].y ) {
                    NET *p=new NET;
                    p->x = polypoint[j].x;
                    p->ymax = polypoint[ (j-1+PointNum) % PointNum ].y;
                    p->dx = ( polypoint[ (j-1+PointNum)%PointNum ].x-polypoint[j].x ) *1.0/ ( polypoint[ (j-1+PointNum) % PointNum ].y - polypoint[j].y );
                    p->next = pNET[i+LENGTH]->next;
                    pNET[i+LENGTH]->next = p;
                }
                if( polypoint[ (j+1+PointNum ) % PointNum].y > polypoint[j].y ) {
                    NET *p = new NET;
                    p->x = polypoint[j].x;
                    p->ymax = polypoint[ (j+1+PointNum) % PointNum ].y;
                    p->dx = ( polypoint[ (j+1+PointNum) % PointNum ].x-polypoint[j].x )*1.0 / ( polypoint[ (j+1+PointNum) % PointNum ].y- polypoint[j].y );
                    p->next = pNET[i+LENGTH]->next;
                    pNET[i+LENGTH]->next = p;
                }
            }
        }
    }

    //建立并更新活性边表AET--------------------------------------
    for( i = MinY; i <= MaxY; i++ ) {
        //计算新的交点x,更新AET
        NET *p = pAET->next;
        while( p != NULL ) {
            p->x = p->x + p->dx;
            p = p->next;
        }

        //更新后新AET先排序---------------------------------------
        //断表排序,不再开辟空间
        AET *tq = pAET;
        p = pAET->next;
        tq->next = NULL;
        while( p != NULL ) {
            while( tq->next != NULL && p->x >= tq->next->x ) {
                tq = tq->next;
            }
            NET *s = p->next;
            p->next = tq->next;
            tq->next = p;
            p = s;
            tq = pAET;
        }
        if(i==MaxY) {
            //*配对填充颜色-----------------
            p = pAET->next;
            while( p != NULL && p->next != NULL ) {
                for(int j = getInt(p->x); j <= getInt(p->next->x); j++) {
                    POINTS[TOTAL].x=static_cast<int>(j);
                    POINTS[TOTAL].y=i;
                    TOTAL++;
                }
                p = p->next->next;//考虑端点情况
            }
        }

        //先从AET表中删除ymax==i的结点---------------------------
        AET *q = pAET;
        p = q->next;
        while( p != NULL ) {
            if( p->ymax == i) {
                q->next = p->next;
                delete p;
                p = q->next;
            } else {
                q = q->next;
                p = q->next;
            }
        }

        //将NET中的新点加入AET,并用插入法按X值递增排序-----------------------------
        p = pNET[i+LENGTH]->next;
        q = pAET;
        while( p != NULL ) {
            while( q->next != NULL && p->x >= q->next->x) {
                q = q->next;
            }
            NET *s = p->next;
            p->next = q->next;
            q->next = p;
            p = s;
            q = pAET;
        }

        //配对填充颜色-------------------------
        p = pAET->next;
        while( p != NULL && p->next != NULL ) {
            for(int j = getInt(p->x); j <= getInt(p->next->x); j++) {
                POINTS[TOTAL].x=static_cast<int>(j);
                POINTS[TOTAL].y=i;
                TOTAL++;
            }
            p = p->next->next;//考虑端点情况
        }
    }
    NET *phead = NULL;
    NET *pnext = NULL;

    //释放活跃边表---------------------
    phead = pAET;
    while( phead != NULL ) {
        pnext = phead->next;
        delete phead;
        phead = pnext;
    }
}

//实现在循环填充时仅调用一次图元填充函数计算，减少时间运行成本
void MyGL::Draw() {
    if(COUNT<1) return;
    int top=COUNT;
    if(MODEL==0&&up>2) top*=4;
    if(!PAUSE) COUNT++;//下次画布上需要打现出的点数加一
	for(int i=0; i<TOTAL; i++) {

        if(i==top) return;
		putpixel(POINTS[i].x,POINTS[i].y);
	}

}
//DDA画线算法
void MyGL::DDACreateLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num) {
	//画线算法的实现
    int dx,dy,epsl;
    double x,y,xIncre,yIncre;
	dx = x1-x0;
	dy = y1-y0;
	x = x0;
	y = y0;
	int px,py;
	if(abs(dx) > abs(dy)) epsl = abs(dx);
	else epsl = abs(dy);
    xIncre = dx*1.0 / epsl ;
    yIncre = dy*1.0 / epsl ;
    for(int k = 0; k<=epsl; k++) {
        px=getInt(x);
        py=getInt(y);
        POINTS[TOTAL].x=px;
        POINTS[TOTAL].y=py;
        TOTAL++;
		x += xIncre;
		y += yIncre;
    }
}
void MyGL::DDADrawLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num) {
    //设置颜色
    glColor3f(0.0f,1.0f,1.0f);
    //对画线动画进行控制
    if(num==0)
        return;
    //画线算法的实现
    int dx,dy,epsl;
    double x,y,xIncre,yIncre;
    dx = x1-x0;
    dy = y1-y0;
    x = x0;
    y = y0;
    int px,py;
    if(abs(dx) > abs(dy)) epsl = abs(dx);
    else epsl = abs(dy);
    xIncre = dx*1.0 / epsl ;
    yIncre = dy*1.0 / epsl ;
    for(int k = 0; k<=epsl; k++) {
        px=getInt(x);
        py=getInt(y);
        putpixel2(px,py);
        if (k>=num-1) return;
        x += xIncre;
        y += yIncre;
    }
}
//两数字交换
void MyGL::swap(GLsizei &x,GLsizei &y) {
	GLsizei temp;
	temp=x;
	x=y;
	y=temp;
}
//中点画线算法
void MyGL::BresenhamLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num) {
    int flag1=0,flag2=0;
    GLsizei dx,dy,d,upIncre,downIncre,x,y;
	dx=x1-x0;
	dy=y1-y0;
	if(abs(dy)>abs(dx)) {
		swap(x0,y0);
		swap(x1,y1);
		flag1=1;
	}
	if(dy*dx<0) {
		y0*=-1;
		y1*=-1;
		flag2=1;
	}
	if(x0>x1) {
		swap(x0,x1);
		swap(y0,y1);
	}
	dx=x1-x0;
	dy=y1-y0;
	x=x0;
	y=y0;
	d=dx-2*dy;
	upIncre=2*dx-2*dy;
	downIncre=-2*dy;
	GLsizei drawx,drawy;
	while(x<=x1) {
		drawx=x;
		drawy=y;
		if(flag2)
			drawy*=-1;
		if(flag1)
			swap(drawx,drawy);
        POINTS[TOTAL].x=drawx;
        POINTS[TOTAL].y=drawy;
        TOTAL++;
		x++;
		if(d<0) {
			y++;
			d+=upIncre;
		} else d+=downIncre;
    }
}
void MyGL::Bresenham2Line(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num) {
    int flag1=0,flag2=0;
    GLsizei x,y,dx,dy,e;
	dx=x1-x0;
	dy=y1-y0;
	if(abs(dy)>abs(dx)) {
		swap(x0,y0);
		swap(x1,y1);
		flag1=1;
	}
	if(dy*dx<0) {
		y0*=-1;
		y1*=-1;
		flag2=1;
	}
	if(x0>x1) {
		swap(x0,x1);
		swap(y0,y1);
	}
	dx=x1-x0;
	dy=y1-y0;
	e=-dx;
	x=x0;
	y=y0;
	GLsizei drawx,drawy;
	while(x<=x1) {
		drawx=x;
		drawy=y;
		if(flag2)
			drawy*=-1;
		if(flag1)
            swap(drawx,drawy);
        POINTS[TOTAL].x=drawx;
        POINTS[TOTAL].y=drawy;
        TOTAL++;
		x++;
		e=e+2*dy;
		if(e>0) {
			y++;
			e=e-2*dx;
		}
    }
}
void MyGL::BresenhamCircle(GLsizei x, GLsizei y, GLsizei R, GLsizei num) {
    int d,xa,ya;
	xa=0;
	ya=R;
	d=1-R;
    while(xa<=ya) {
        POINTS[TOTAL]={double(xa+x),ya+y};TOTAL++;
        POINTS[TOTAL]={double(ya+x),xa+y};TOTAL++;
        POINTS[TOTAL]={double(-ya+x),xa+y};TOTAL++;
        POINTS[TOTAL]={double(-xa+x),ya+y};TOTAL++;
        POINTS[TOTAL]={double(-xa+x),-ya+y};TOTAL++;
        POINTS[TOTAL]={double(-ya+x),-xa+y};TOTAL++;
        POINTS[TOTAL]={double(ya+x),-xa+y};TOTAL++;
        POINTS[TOTAL]={double(xa+x),-ya+y};TOTAL++;
		if(d<0) d+=2*xa+3;
		else {
			d+=2*(xa-ya)+5;
			ya--;
		}
		xa++;
    }
}
void MyGL::MidpointCircle(int x0,int y0,int R,int num) {
    int x,y,deltax,deltay,d;
	x=0;
	y=R;
	d=1-R;
	deltax=3;
	deltay=2-R-R;
	while(x<=y) {
        POINTS[TOTAL]={double(x+x0),y+y0};TOTAL++;
        POINTS[TOTAL]={double(y+x0),x+y0};TOTAL++;
        POINTS[TOTAL]={double(-y+x0),x+y0};TOTAL++;
        POINTS[TOTAL]={double(-x+x0),y+y0};TOTAL++;
        POINTS[TOTAL]={double(-x+x0),-y+y0};TOTAL++;
        POINTS[TOTAL]={double(-y+x0),-x+y0};TOTAL++;
        POINTS[TOTAL]={double(y+x0),-x+y0};TOTAL++;
        POINTS[TOTAL]={double(x+x0),-y+y0};TOTAL++;
		if(d<0) {
			d+=deltax;
			deltax+=2;
			x++;
		} else {
			d+=deltax+deltay;
			deltax+=2;
			deltay+=2;
			x++;
			y--;
        }
    }
}
void MyGL::MidpointElipse(int x0,int y0,int a,int b,int num) {
    int x=0,y=b;
	double d1,d2;
	d1=b*b+a*a*(0.25-b);
	while(b*b*(x+1)<=a*a*(y-0.5)) {
        POINTS[TOTAL]={double(x+x0),y+y0};TOTAL++;
        POINTS[TOTAL]={double(-x+x0),y+y0};TOTAL++;
        POINTS[TOTAL]={double(-x+x0),-y+y0};TOTAL++;
        POINTS[TOTAL]={double(x+x0),-y+y0};TOTAL++;
		if(d1<0) {
			d1+=b*b*(2*x+3);
			x++;
		} else {
			d1+=(b*b*(2*x+3)+a*a*(2-2*y));
			x++;
			y--;
        }
	}
    POINTS[TOTAL]={double(x+x0),y+y0};TOTAL++;
    POINTS[TOTAL]={double(-x+x0),y+y0};TOTAL++;
    POINTS[TOTAL]={double(-x+x0),-y+y0};TOTAL++;
    POINTS[TOTAL]={double(x+x0),-y+y0};TOTAL++;
	d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
    while(y>0) {
		if(d2<0) {
			d2+=b*b*(2*x+2)+a*a*(3-2*y);
			x++;
			y--;
		} else {
			d2+=a*a*(3-2*y);
			y--;
        }
        POINTS[TOTAL]={double(x+x0),y+y0};TOTAL++;
        POINTS[TOTAL]={double(-x+x0),y+y0};TOTAL++;
        POINTS[TOTAL]={double(-x+x0),-y+y0};TOTAL++;
        POINTS[TOTAL]={double(x+x0),-y+y0};TOTAL++;
    }
}
