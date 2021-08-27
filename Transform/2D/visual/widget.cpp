#include "widget.h"
#include "ui_widget.h"
#include<QAction>
#include <QtGui/qevent.h>
#include <QSplashScreen>
#include <QtTest/QTest>
Widget::Widget(QWidget *parent) :
    QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->openGLWidget->setCursor(Qt::PointingHandCursor);
    ui->horizontalSlider->setCursor(Qt::PointingHandCursor);
    ui->horizontalSlider_2->setCursor(Qt::PointingHandCursor);
    ui->horizontalSlider_2->setMaximum(ui->openGLWidget->LENGTH/4);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_se1(const QString &)));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_se2(const QString &)));
    connect(ui->comboBox_3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_se3(const QString &)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),this, SLOT(setValue(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)),this, SLOT(setValueR(int)));
    connect(ui->radioButton, SIGNAL(clicked(bool)), this, SLOT(radioChecked(bool)));
    connect(ui->radioButton_2, SIGNAL(clicked(bool)), this, SLOT(radio2Checked(bool)));
    connect(ui->radioButton_3, SIGNAL(clicked(bool)), this, SLOT(radio3Checked(bool)));

    pauseAction=new QAction ("暂停",ui->openGLWidget);
    connect(pauseAction, SIGNAL(triggered(bool)), this, SLOT(ClickButton3()));
    ui->openGLWidget->addAction(pauseAction);
    fillAction=new QAction ("填充",ui->openGLWidget);
    connect(fillAction, SIGNAL(triggered(bool)), this, SLOT(ClickButton2()));
    ui->openGLWidget->addAction(fillAction);
    delAction=new QAction ("撤点",ui->openGLWidget);
    connect(delAction, SIGNAL(triggered(bool)), this, SLOT(ClickButton4()));
    ui->openGLWidget->addAction(delAction);
    addAction=new QAction ("添点",ui->openGLWidget);
    connect(addAction, SIGNAL(triggered(bool)), this, SLOT(ClickButton5()));
    ui->openGLWidget->addAction(addAction);
    addAction->setVisible(false);
    fillAction->setVisible(false);
    xySize=new QAction ("x缩放",ui->openGLWidget);
    ui->openGLWidget->addAction(xySize);
    xySize->setVisible(false);
    connect(xySize, SIGNAL(triggered(bool)), this, SLOT(ClickButton6()));
    ui->openGLWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::ClickButton2()
{
    ui->openGLWidget->isFILL=true;
    ui->openGLWidget->COUNT=1;
    ui->openGLWidget->TOTAL=0;
    ui->openGLWidget->PAUSE=false;
    pauseAction->setText("暂停");
}
void Widget::ClickButton3()
{
    if(ui->openGLWidget->PAUSE==false)
    {
        ui->openGLWidget->PAUSE=true;
        pauseAction->setText("开始");
    }
    else {
        ui->openGLWidget->PAUSE=false;
        pauseAction->setText("暂停");
    }
}
void Widget::ClickButton4()
{
    if(!ui->openGLWidget->TRANS2D){
    switch (ui->openGLWidget->MODEL) {
    case 0:
        if(ui->openGLWidget->PointNum>0)
            ui->openGLWidget->PointNum--;
        ui->openGLWidget->COUNT=1;
        ui->openGLWidget->TOTAL=0;
        //ui->openGLWidget->isFILL=false;
        break;
    case 1:
        if(ui->openGLWidget->PointNum>0)
            ui->openGLWidget->PointNum--;
        ui->openGLWidget->isFILL=false;
        ui->openGLWidget->TOTAL=0;
        break;
    }}
    else {
        if(ui->openGLWidget->mouseClickCount>0)
            ui->openGLWidget->mouseClickCount--;
        ui->openGLWidget->LISTEN=true;
        ui->openGLWidget->setCursor(Qt::PointingHandCursor);
    }

}
void Widget::ClickButton5()
{
    switch (ui->openGLWidget->MODEL) {
    case 0:
        ui->openGLWidget->COUNT=1;
        break;
    case 1:
        ui->openGLWidget->isFILL=false;
        ui->openGLWidget->TOTAL=0;
        break;
    }

}
void Widget::ClickButton6()
{
    if(ui->openGLWidget->xTrans)
    {
        ui->openGLWidget->xTrans=false;
        xySize->setText("x缩放");
        ui->openGLWidget->setCursor(Qt::SizeVerCursor);
    }
    else
    {
        ui->openGLWidget->xTrans=true;
        xySize->setText("y缩放");
        ui->openGLWidget->setCursor(Qt::SizeHorCursor);
    }

}
void Widget::on_se1(const QString &)
    {
        ui->openGLWidget->up=ui->comboBox->currentIndex();
        if(ui->openGLWidget->up>2)
            ui->openGLWidget->plotpre=false;
        else
            ui->openGLWidget->plotpre=true;
        ui->openGLWidget->COUNT=1;
        ui->openGLWidget->PointNum=0;
        ui->openGLWidget->TOTAL=0;
        ui->openGLWidget->PAUSE=false;
        pauseAction->setText("暂停");

    }
void Widget::on_se2(const QString &)
{
    ui->openGLWidget->mid=ui->comboBox_2->currentIndex();
    ui->openGLWidget->COUNT=1;
    ui->openGLWidget->TOTAL=0;
    ui->openGLWidget->PointNum=0;
    ui->openGLWidget->PAUSE=false;
    pauseAction->setText("暂停");
}
void Widget::on_se3(const QString &)
{
    ui->openGLWidget->down=ui->comboBox_3->currentIndex();
    ui->openGLWidget->PAUSE=false;
    pauseAction->setText("暂停");
    ui->openGLWidget->mouseClickCount=0;
    if(ui->openGLWidget->TRANSFLAG1) {ui->openGLWidget->PointNum/=2;ui->openGLWidget->TRANSFLAG1=false;}
    if(ui->openGLWidget->TRANSFLAG2) {ui->openGLWidget->TOTAL/=2;ui->openGLWidget->TRANSFLAG2=false;}
    if(ui->openGLWidget->down>0)
        ui->openGLWidget->setCursor(Qt::PointingHandCursor);
    else {
        ui->openGLWidget->setCursor(Qt::ClosedHandCursor);
    }
    ui->openGLWidget->LISTEN=true;
    ui->openGLWidget->Sx=1;
    ui->openGLWidget->Sy=1;
    if(ui->openGLWidget->down!=2)
    {xySize->setVisible(false);ui->label_mse->setText("温馨提示：鼠标左右键可用！");}
    else{ xySize->setVisible(true);ui->label_mse->setText("温馨提示：鼠标右键及滚轮可用！");}
    if(ui->openGLWidget->down==1||ui->openGLWidget->down==2) delAction->setVisible(true);
    else delAction->setVisible(false);
}
void Widget::setValue(int)
{
    int value=ui->horizontalSlider->value();
    ui->openGLWidget->SPEED=400-4*value;
    ui->openGLWidget->timer->start(ui->openGLWidget->SPEED);
}
void Widget::setValueR(int)
{
    int value=ui->horizontalSlider_2->value();
    ui->openGLWidget->HalfWide=int(ui->openGLWidget->LENGTH*1.0/value);
    ui->openGLWidget->WIDE=ui->openGLWidget->HalfWide*2;
    ui->openGLWidget->Rate=1.0*ui->openGLWidget->WIDE/ui->openGLWidget->LENGTH;
}
void Widget::radioChecked(bool)
{
    if(ui->openGLWidget->TRANS3D) ui->openGLWidget->changeBaseColor=true;
        ui->comboBox_2->setEnabled(false);
        ui->comboBox->setEnabled(true);
        ui->comboBox_3->setEnabled(false);
        ui->openGLWidget->MODEL=0;
        ui->openGLWidget->COUNT=1;
        ui->openGLWidget->TOTAL=0;
        ui->openGLWidget->PointNum=0;
        ui->openGLWidget->PAUSE=false;
        pauseAction->setText("暂停");
        ui->openGLWidget->setCursor(Qt::PointingHandCursor);
        addAction->setVisible(false);
        fillAction->setVisible(false);
        pauseAction->setVisible(true);
        delAction->setVisible(true);
        xySize->setVisible(false);
        ui->label_mse->setText("温馨提示：鼠标左右键可用！");
        ui->openGLWidget->TRANS2D=false;
        ui->openGLWidget->TRANS3D=false;

}
void Widget::radio2Checked(bool)
{
    if(ui->openGLWidget->TRANS3D) ui->openGLWidget->changeBaseColor=true;
    ui->comboBox_2->setEnabled(true);
    ui->comboBox->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
    ui->openGLWidget->MODEL=1;
    ui->openGLWidget->COUNT=1;
    ui->openGLWidget->PointNum=0;
    ui->openGLWidget->isFILL=false;
    ui->openGLWidget->TOTAL=0;
    ui->openGLWidget->PAUSE=false;
    pauseAction->setText("暂停");
    ui->openGLWidget->setCursor(Qt::PointingHandCursor);
    addAction->setVisible(true);
    fillAction->setVisible(true);
    pauseAction->setVisible(true);
    delAction->setVisible(true);
    xySize->setVisible(false);
    ui->label_mse->setText("温馨提示：鼠标左右键可用！");
    ui->openGLWidget->TRANS3D=false;
    ui->openGLWidget->TRANS2D=false;

}
void Widget::radio3Checked(bool)
{
    if(ui->openGLWidget->TRANS3D) ui->openGLWidget->changeBaseColor=true;
    if(ui->openGLWidget->down==0)
        ui->openGLWidget->setCursor(Qt::ClosedHandCursor);
    else ui->openGLWidget->setCursor(Qt::PointingHandCursor);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->comboBox_3->setEnabled(true);
    ui->openGLWidget->TRANS2D=true;
    ui->openGLWidget->PAUSE=false;
    pauseAction->setText("暂停");
    addAction->setVisible(false);
    fillAction->setVisible(false);
    pauseAction->setVisible(false);
    if(ui->openGLWidget->down==1||ui->openGLWidget->down==2) delAction->setVisible(true);
    else delAction->setVisible(false);
    if(ui->openGLWidget->down!=2)
    {xySize->setVisible(false);ui->label_mse->setText("温馨提示：鼠标左右键可用！");}
    else{ xySize->setVisible(true);ui->label_mse->setText("温馨提示：鼠标右键及滚轮可用！");}
    ui->openGLWidget->mouseClickCount=0;
    ui->openGLWidget->TRANSFLAG1=false;
    ui->openGLWidget->TRANSFLAG2=false;
    ui->openGLWidget->LISTEN=true;
    ui->openGLWidget->Sx=1;
    ui->openGLWidget->Sy=1;
    ui->openGLWidget->TRANS3D=false;

    for(int i=0;i<ui->openGLWidget->PointNum;i++)
    {
        ui->openGLWidget->recx[i]=ui->openGLWidget->polypoint[i].x;
        ui->openGLWidget->recy[i]=ui->openGLWidget->polypoint[i].y;
    }
}
void Widget::radio4Checked(bool)
{
    ui->openGLWidget->changeBaseColor=true;
    ui->comboBox_2->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
    ui->openGLWidget->TRANS2D=false;
    ui->openGLWidget->TRANS3D=true;
    pauseAction->setText("暂停");
    addAction->setVisible(false);
    fillAction->setVisible(false);
    pauseAction->setVisible(false);
    delAction->setVisible(false);
    xySize->setVisible(false);
    ui->openGLWidget->mouseClickCount=0;
    ui->openGLWidget->LISTEN=true;
    ui->label_mse->setText("温馨提示：鼠标左右键可用！");
}
void Widget::loadingPJ()
{
    QPixmap lodingPix(":/init.jpg");
    QSplashScreen splash(lodingPix);
    splash.show();
    splash.showMessage("MoBaiGeneral\t", Qt::AlignTop|Qt::AlignRight, Qt::red);
    QCoreApplication::processEvents();
    QTest::qSleep(1000);   //qSleep参数为毫秒
    this->show();
    splash.finish(this);
}

/*
void Widget::mouseMoveEvent(QMouseEvent *e)
{
    ui->pushButton_2->setText("("+QString::number(e->x())+", "+QString :: number(e->y())+")");
}
void Widget::mouseReleaseEvent(QMouseEvent *e)
{

    ui->pushButton_3->setText("("+QString::number(e->x())+", "+QString :: number(e->y())+")");
}*/
