/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include <mygl.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSlider *horizontalSlider;
    QLabel *label_4;
    QSlider *horizontalSlider_2;
    QLabel *label;
    MyGL *openGLWidget;
    QFrame *line_2;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_3;
    QFrame *line;
    QFrame *line_6;
    QLabel *label_mse;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1400, 900);
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        Widget->setFont(font);
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 20, 471, 121));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(8);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(10, 20, 10, 20);
        horizontalSlider = new QSlider(gridLayoutWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(10);
        horizontalSlider->setMaximum(99);
        horizontalSlider->setPageStep(5);
        horizontalSlider->setValue(50);
        horizontalSlider->setSliderPosition(50);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 1, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        horizontalSlider_2 = new QSlider(gridLayoutWidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setMinimum(10);
        horizontalSlider_2->setMaximum(50);
        horizontalSlider_2->setPageStep(5);
        horizontalSlider_2->setSliderPosition(28);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_2, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setPointSize(15);
        label->setFont(font2);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        openGLWidget = new MyGL(Widget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(520, 20, 860, 860));
        openGLWidget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(9, 41, 4, 255), stop:0.085 rgba(2, 79, 0, 255), stop:0.19 rgba(50, 147, 22, 255), stop:0.275 rgba(236, 191, 49, 255), stop:0.39 rgba(243, 61, 34, 255), stop:0.555 rgba(135, 81, 60, 255), stop:0.667 rgba(121, 75, 255, 255), stop:0.825 rgba(164, 255, 244, 255), stop:0.885 rgba(104, 222, 71, 255), stop:1 rgba(93, 128, 0, 255));"));
        line_2 = new QFrame(Widget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(10, 150, 501, 20));
        line_2->setLineWidth(1);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        comboBox = new QComboBox(Widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(230, 240, 251, 51));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        comboBox->setFont(font3);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 205, 181, 251));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(30, 40, 181, 41));
        radioButton->setFont(font2);
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(30, 105, 181, 41));
        radioButton_2->setFont(font2);
        radioButton_2->setChecked(false);
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(30, 170, 181, 41));
        radioButton_3->setFont(font2);
        comboBox_2 = new QComboBox(Widget);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setEnabled(false);
        comboBox_2->setGeometry(QRect(230, 305, 251, 51));
        comboBox_2->setFont(font3);
        comboBox_3 = new QComboBox(Widget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setEnabled(false);
        comboBox_3->setGeometry(QRect(230, 370, 251, 51));
        comboBox_3->setFont(font3);
        line_4 = new QFrame(Widget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(0, 10, 21, 881));
        line_4->setLineWidth(2);
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(Widget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(10, 0, 1381, 20));
        line_5->setLineWidth(2);
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(Widget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(10, 880, 1381, 20));
        line_3->setLineWidth(2);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line = new QFrame(Widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(500, 10, 20, 881));
        line->setLineWidth(2);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(Widget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(1380, 10, 16, 881));
        line_6->setLineWidth(2);
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        label_mse = new QLabel(Widget);
        label_mse->setObjectName(QString::fromUtf8("label_mse"));
        label_mse->setGeometry(QRect(110, 540, 361, 101));
        label_mse->setFont(font3);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", " \350\247\206\351\207\216\345\215\212\345\276\204\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("Widget", " \346\274\224\347\244\272\351\200\237\345\272\246\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "DDA\347\256\227\346\263\225", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "\344\270\255\347\202\271\347\224\273\347\272\277\347\256\227\346\263\225", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Widget", "Bresenham\347\224\273\347\272\277\347\256\227\346\263\225", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Widget", "Bresenham\347\224\273\345\234\206\347\256\227\346\263\225", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Widget", "\345\233\233\345\210\206\344\270\255\347\202\271\347\224\273\345\234\206\347\256\227\346\263\225", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("Widget", "\345\233\233\345\210\206\344\270\255\347\202\271\347\224\273\346\244\255\345\234\206\347\256\227\346\263\225", nullptr));

        groupBox->setTitle(QString());
        radioButton->setText(QCoreApplication::translate("Widget", "\347\273\230\347\272\277\346\250\241\345\274\217", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Widget", "\345\241\253\345\205\205\346\250\241\345\274\217", nullptr));
        radioButton_3->setText(QCoreApplication::translate("Widget", "\344\272\214\347\273\264\345\217\230\346\215\242", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("Widget", "\345\244\232\350\276\271\345\275\242\346\211\253\346\217\217\347\272\277\345\241\253\345\205\205\347\256\227\346\263\225", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("Widget", "\345\271\263\347\247\273", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("Widget", "\346\227\213\350\275\254", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("Widget", "\347\274\251\346\224\276", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("Widget", "\347\202\271\345\257\271\347\247\260", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("Widget", "\347\272\277\345\257\271\347\247\260", nullptr));

        label_mse->setText(QCoreApplication::translate("Widget", "\346\270\251\351\246\250\346\217\220\347\244\272\357\274\232\351\274\240\346\240\207\345\267\246\345\217\263\351\224\256\345\217\257\347\224\250\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
