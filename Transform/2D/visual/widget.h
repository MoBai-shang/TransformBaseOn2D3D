#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include<QAction>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void loadingPJ();
    QAction *pauseAction,*fillAction,*delAction,*addAction,*xySize;

    Ui::Widget *ui;
public slots:
    void ClickButton2();
    void ClickButton3();
    void ClickButton4();
    void ClickButton5();
    void ClickButton6();
    void on_se1(const QString &text);
    void on_se2(const QString &);
    void on_se3(const QString &text);
    void setValue(int);
    void setValueR(int);
    void radioChecked(bool);
    void radio2Checked(bool);
    void radio3Checked(bool);
    void radio4Checked(bool);
    /*
protected:
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *e);*/

};

#endif // WIDGET_H
