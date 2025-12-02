/********************************************************************************
** Form generated from reading UI file 'robot_controllerkksIPB.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ROBOT_CONTROLLERKKSIPB_H
#define ROBOT_CONTROLLERKKSIPB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label_23;
    QLabel *label_4;
    QSlider *spC5;
    QLabel *label_17;
    QDoubleSpinBox *pos2;
    QLabel *label_28;
    QCheckBox *fb5;
    QSlider *posC4;
    QLabel *label_3;
    QRadioButton *waveSpeed;
    QLabel *label_25;
    QSlider *posC3;
    QSpinBox *waveJointNumber;
    QSlider *posC1;
    QCheckBox *fb2;
    QDoubleSpinBox *firstValue;
    QCheckBox *fb4;
    QDoubleSpinBox *derivative;
    QSlider *spC0;
    QCheckBox *fb3;
    QLabel *sp2;
    QSlider *spC3;
    QLabel *label_31;
    QLabel *label_12;
    QLabel *label_24;
    QLabel *label_8;
    QRadioButton *publishFirst;
    QCheckBox *autoPublish;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *integrator_max;
    QLabel *label_5;
    QSlider *spC1;
    QLabel *label_18;
    QDoubleSpinBox *secondValue;
    QDoubleSpinBox *pos5;
    QLabel *sp3;
    QLabel *label_20;
    QLabel *label_13;
    QDoubleSpinBox *pos1;
    QLabel *sp0;
    QRadioButton *wavePosition;
    QSlider *posC0;
    QLabel *label_19;
    QDoubleSpinBox *proportional;
    QLabel *label_11;
    QSpinBox *switchTime;
    QCheckBox *fb0;
    QLabel *label_14;
    QPushButton *resetButton;
    QSlider *posC2;
    QCheckBox *fb1;
    QLabel *sp5;
    QLabel *sp1;
    QLabel *label_21;
    QDoubleSpinBox *filterConst;
    QLabel *label_30;
    QDoubleSpinBox *pos4;
    QLabel *label_22;
    QLabel *label_2;
    QSpinBox *pidJointNumber;
    QLabel *label_26;
    QDoubleSpinBox *integrator_min;
    QSlider *spC2;
    QSlider *posC5;
    QLabel *label_7;
    QLabel *label_10;
    QDoubleSpinBox *pos0;
    QSpacerItem *verticalSpacer;
    QLabel *sp4;
    QLabel *label_15;
    QPushButton *publishPID;
    QSlider *spC4;
    QLabel *label;
    QLabel *label_9;
    QRadioButton *publishSecond;
    QLabel *label_27;
    QDoubleSpinBox *pos3;
    QLabel *label_29;
    QLabel *label_16;
    QDoubleSpinBox *integral;
    QRadioButton *pidSpeed;
    QRadioButton *pidPosition;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(990, 465);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 0, 975, 461));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(widget);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_2->addWidget(label_23, 4, 6, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 5, 0, 1, 1);

        spC5 = new QSlider(widget);
        spC5->setObjectName(QString::fromUtf8("spC5"));
        spC5->setMinimum(-180);
        spC5->setMaximum(180);
        spC5->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(spC5, 16, 8, 1, 3);

        label_17 = new QLabel(widget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_17->setFont(font);

        gridLayout_2->addWidget(label_17, 10, 8, 1, 2);

        pos2 = new QDoubleSpinBox(widget);
        pos2->setObjectName(QString::fromUtf8("pos2"));
        pos2->setDecimals(1);
        pos2->setMinimum(-180.000000000000000);
        pos2->setMaximum(180.000000000000000);

        gridLayout_2->addWidget(pos2, 3, 11, 1, 1);

        label_28 = new QLabel(widget);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_2->addWidget(label_28, 16, 6, 1, 1);

        fb5 = new QCheckBox(widget);
        fb5->setObjectName(QString::fromUtf8("fb5"));
        fb5->setChecked(true);

        gridLayout_2->addWidget(fb5, 6, 7, 1, 1);

        posC4 = new QSlider(widget);
        posC4->setObjectName(QString::fromUtf8("posC4"));
        posC4->setMinimum(-180);
        posC4->setMaximum(180);
        posC4->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(posC4, 5, 8, 1, 3);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 4, 0, 1, 1);

        waveSpeed = new QRadioButton(widget);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(waveSpeed);
        waveSpeed->setObjectName(QString::fromUtf8("waveSpeed"));
        waveSpeed->setChecked(true);

        gridLayout_2->addWidget(waveSpeed, 12, 4, 1, 1);

        label_25 = new QLabel(widget);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_2->addWidget(label_25, 6, 6, 1, 1);

        posC3 = new QSlider(widget);
        posC3->setObjectName(QString::fromUtf8("posC3"));
        posC3->setMinimum(-180);
        posC3->setMaximum(180);
        posC3->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(posC3, 4, 8, 1, 3);

        waveJointNumber = new QSpinBox(widget);
        waveJointNumber->setObjectName(QString::fromUtf8("waveJointNumber"));
        waveJointNumber->setMaximum(5);

        gridLayout_2->addWidget(waveJointNumber, 12, 1, 1, 1);

        posC1 = new QSlider(widget);
        posC1->setObjectName(QString::fromUtf8("posC1"));
        posC1->setMinimum(-180);
        posC1->setMaximum(180);
        posC1->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(posC1, 2, 8, 1, 3);

        fb2 = new QCheckBox(widget);
        fb2->setObjectName(QString::fromUtf8("fb2"));
        fb2->setChecked(true);

        gridLayout_2->addWidget(fb2, 3, 7, 1, 1);

        firstValue = new QDoubleSpinBox(widget);
        firstValue->setObjectName(QString::fromUtf8("firstValue"));
        firstValue->setMinimum(-999.000000000000000);
        firstValue->setMaximum(999.000000000000000);

        gridLayout_2->addWidget(firstValue, 15, 1, 1, 1);

        fb4 = new QCheckBox(widget);
        fb4->setObjectName(QString::fromUtf8("fb4"));
        fb4->setChecked(true);

        gridLayout_2->addWidget(fb4, 5, 7, 1, 1);

        derivative = new QDoubleSpinBox(widget);
        derivative->setObjectName(QString::fromUtf8("derivative"));
        derivative->setDecimals(5);
        derivative->setMaximum(9999.000000000000000);

        gridLayout_2->addWidget(derivative, 5, 1, 1, 1);

        spC0 = new QSlider(widget);
        spC0->setObjectName(QString::fromUtf8("spC0"));
        spC0->setMinimum(-180);
        spC0->setMaximum(180);
        spC0->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(spC0, 11, 8, 1, 3);

        fb3 = new QCheckBox(widget);
        fb3->setObjectName(QString::fromUtf8("fb3"));
        fb3->setChecked(true);

        gridLayout_2->addWidget(fb3, 4, 7, 1, 1);

        sp2 = new QLabel(widget);
        sp2->setObjectName(QString::fromUtf8("sp2"));

        gridLayout_2->addWidget(sp2, 13, 11, 1, 1);

        spC3 = new QSlider(widget);
        spC3->setObjectName(QString::fromUtf8("spC3"));
        spC3->setMinimum(-180);
        spC3->setMaximum(180);
        spC3->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(spC3, 14, 8, 1, 3);

        label_31 = new QLabel(widget);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_2->addWidget(label_31, 14, 6, 1, 1);

        label_12 = new QLabel(widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 4, 3, 1, 1);

        label_24 = new QLabel(widget);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_2->addWidget(label_24, 5, 6, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 15, 0, 1, 1);

        publishFirst = new QRadioButton(widget);
        buttonGroup_3 = new QButtonGroup(MainWindow);
        buttonGroup_3->setObjectName(QString::fromUtf8("buttonGroup_3"));
        buttonGroup_3->addButton(publishFirst);
        publishFirst->setObjectName(QString::fromUtf8("publishFirst"));
        publishFirst->setEnabled(true);
        publishFirst->setChecked(true);

        gridLayout_2->addWidget(publishFirst, 15, 2, 1, 1);

        autoPublish = new QCheckBox(widget);
        autoPublish->setObjectName(QString::fromUtf8("autoPublish"));

        gridLayout_2->addWidget(autoPublish, 10, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 5, 1, 1);

        integrator_max = new QDoubleSpinBox(widget);
        integrator_max->setObjectName(QString::fromUtf8("integrator_max"));
        integrator_max->setDecimals(4);
        integrator_max->setMaximum(999.000000000000000);

        gridLayout_2->addWidget(integrator_max, 3, 4, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 5, 3, 1, 1);

        spC1 = new QSlider(widget);
        spC1->setObjectName(QString::fromUtf8("spC1"));
        spC1->setMinimum(-180);
        spC1->setMaximum(180);
        spC1->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(spC1, 12, 8, 1, 3);

        label_18 = new QLabel(widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_2->addWidget(label_18, 0, 7, 1, 1);

        secondValue = new QDoubleSpinBox(widget);
        secondValue->setObjectName(QString::fromUtf8("secondValue"));
        secondValue->setMinimum(-999.000000000000000);
        secondValue->setMaximum(999.000000000000000);

        gridLayout_2->addWidget(secondValue, 16, 1, 1, 1);

        pos5 = new QDoubleSpinBox(widget);
        pos5->setObjectName(QString::fromUtf8("pos5"));
        pos5->setDecimals(1);
        pos5->setMinimum(-180.000000000000000);
        pos5->setMaximum(180.000000000000000);

        gridLayout_2->addWidget(pos5, 6, 11, 1, 1);

        sp3 = new QLabel(widget);
        sp3->setObjectName(QString::fromUtf8("sp3"));

        gridLayout_2->addWidget(sp3, 14, 11, 1, 1);

        label_20 = new QLabel(widget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_2->addWidget(label_20, 1, 6, 1, 1);

        label_13 = new QLabel(widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);

        gridLayout_2->addWidget(label_13, 10, 1, 1, 3);

        pos1 = new QDoubleSpinBox(widget);
        pos1->setObjectName(QString::fromUtf8("pos1"));
        pos1->setDecimals(1);
        pos1->setMinimum(-180.000000000000000);
        pos1->setMaximum(180.000000000000000);

        gridLayout_2->addWidget(pos1, 2, 11, 1, 1);

        sp0 = new QLabel(widget);
        sp0->setObjectName(QString::fromUtf8("sp0"));

        gridLayout_2->addWidget(sp0, 11, 11, 1, 1);

        wavePosition = new QRadioButton(widget);
        buttonGroup_2->addButton(wavePosition);
        wavePosition->setObjectName(QString::fromUtf8("wavePosition"));

        gridLayout_2->addWidget(wavePosition, 13, 4, 1, 1);

        posC0 = new QSlider(widget);
        posC0->setObjectName(QString::fromUtf8("posC0"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(posC0->sizePolicy().hasHeightForWidth());
        posC0->setSizePolicy(sizePolicy);
        posC0->setMinimumSize(QSize(300, 0));
        posC0->setMinimum(-180);
        posC0->setMaximum(180);
        posC0->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(posC0, 1, 8, 1, 3);

        label_19 = new QLabel(widget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_2->addWidget(label_19, 0, 11, 1, 1);

        proportional = new QDoubleSpinBox(widget);
        proportional->setObjectName(QString::fromUtf8("proportional"));
        proportional->setDecimals(5);
        proportional->setMaximum(9999.000000000000000);

        gridLayout_2->addWidget(proportional, 3, 1, 1, 1);

        label_11 = new QLabel(widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 3, 3, 1, 1);

        switchTime = new QSpinBox(widget);
        switchTime->setObjectName(QString::fromUtf8("switchTime"));
        switchTime->setMaximum(10000);
        switchTime->setValue(1000);

        gridLayout_2->addWidget(switchTime, 13, 1, 1, 1);

        fb0 = new QCheckBox(widget);
        fb0->setObjectName(QString::fromUtf8("fb0"));
        fb0->setChecked(true);

        gridLayout_2->addWidget(fb0, 1, 7, 1, 1);

        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 12, 0, 1, 1);

        resetButton = new QPushButton(widget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        gridLayout_2->addWidget(resetButton, 16, 4, 1, 1);

        posC2 = new QSlider(widget);
        posC2->setObjectName(QString::fromUtf8("posC2"));
        posC2->setMinimum(-180);
        posC2->setMaximum(180);
        posC2->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(posC2, 3, 8, 1, 3);

        fb1 = new QCheckBox(widget);
        fb1->setObjectName(QString::fromUtf8("fb1"));
        fb1->setChecked(true);

        gridLayout_2->addWidget(fb1, 2, 7, 1, 1);

        sp5 = new QLabel(widget);
        sp5->setObjectName(QString::fromUtf8("sp5"));

        gridLayout_2->addWidget(sp5, 16, 11, 1, 1);

        sp1 = new QLabel(widget);
        sp1->setObjectName(QString::fromUtf8("sp1"));

        gridLayout_2->addWidget(sp1, 12, 11, 1, 1);

        label_21 = new QLabel(widget);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 2, 6, 1, 1);

        filterConst = new QDoubleSpinBox(widget);
        filterConst->setObjectName(QString::fromUtf8("filterConst"));
        filterConst->setDecimals(5);
        filterConst->setMaximum(999.000000000000000);
        filterConst->setValue(1.000000000000000);

        gridLayout_2->addWidget(filterConst, 5, 4, 1, 1);

        label_30 = new QLabel(widget);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_2->addWidget(label_30, 15, 6, 1, 1);

        pos4 = new QDoubleSpinBox(widget);
        pos4->setObjectName(QString::fromUtf8("pos4"));
        pos4->setDecimals(1);
        pos4->setMinimum(-180.000000000000000);
        pos4->setMaximum(180.000000000000000);

        gridLayout_2->addWidget(pos4, 5, 11, 1, 1);

        label_22 = new QLabel(widget);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_2->addWidget(label_22, 3, 6, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        pidJointNumber = new QSpinBox(widget);
        pidJointNumber->setObjectName(QString::fromUtf8("pidJointNumber"));
        pidJointNumber->setMaximum(5);

        gridLayout_2->addWidget(pidJointNumber, 1, 1, 1, 1);

        label_26 = new QLabel(widget);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_2->addWidget(label_26, 12, 6, 1, 1);

        integrator_min = new QDoubleSpinBox(widget);
        integrator_min->setObjectName(QString::fromUtf8("integrator_min"));
        integrator_min->setDecimals(4);
        integrator_min->setMinimum(-999.000000000000000);
        integrator_min->setMaximum(0.000000000000000);

        gridLayout_2->addWidget(integrator_min, 4, 4, 1, 1);

        spC2 = new QSlider(widget);
        spC2->setObjectName(QString::fromUtf8("spC2"));
        spC2->setMinimum(-180);
        spC2->setMaximum(180);
        spC2->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(spC2, 13, 8, 1, 3);

        posC5 = new QSlider(widget);
        posC5->setObjectName(QString::fromUtf8("posC5"));
        posC5->setMinimum(-180);
        posC5->setMaximum(180);
        posC5->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(posC5, 6, 8, 1, 3);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 16, 0, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        pos0 = new QDoubleSpinBox(widget);
        pos0->setObjectName(QString::fromUtf8("pos0"));
        pos0->setDecimals(1);
        pos0->setMinimum(-180.000000000000000);
        pos0->setMaximum(180.000000000000000);

        gridLayout_2->addWidget(pos0, 1, 11, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 7, 5, 1, 1);

        sp4 = new QLabel(widget);
        sp4->setObjectName(QString::fromUtf8("sp4"));

        gridLayout_2->addWidget(sp4, 15, 11, 1, 1);

        label_15 = new QLabel(widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 13, 0, 1, 1);

        publishPID = new QPushButton(widget);
        publishPID->setObjectName(QString::fromUtf8("publishPID"));

        gridLayout_2->addWidget(publishPID, 1, 4, 1, 1);

        spC4 = new QSlider(widget);
        spC4->setObjectName(QString::fromUtf8("spC4"));
        spC4->setMinimum(-180);
        spC4->setMaximum(180);
        spC4->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(spC4, 15, 8, 1, 3);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout_2->addWidget(label, 0, 1, 1, 2);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 13, 2, 1, 1);

        publishSecond = new QRadioButton(widget);
        buttonGroup_3->addButton(publishSecond);
        publishSecond->setObjectName(QString::fromUtf8("publishSecond"));

        gridLayout_2->addWidget(publishSecond, 16, 2, 1, 1);

        label_27 = new QLabel(widget);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_2->addWidget(label_27, 11, 6, 1, 1);

        pos3 = new QDoubleSpinBox(widget);
        pos3->setObjectName(QString::fromUtf8("pos3"));
        pos3->setDecimals(1);
        pos3->setMinimum(-180.000000000000000);
        pos3->setMaximum(180.000000000000000);

        gridLayout_2->addWidget(pos3, 4, 11, 1, 1);

        label_29 = new QLabel(widget);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_2->addWidget(label_29, 13, 6, 1, 1);

        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font);

        gridLayout_2->addWidget(label_16, 0, 8, 1, 2);

        integral = new QDoubleSpinBox(widget);
        integral->setObjectName(QString::fromUtf8("integral"));
        integral->setDecimals(5);
        integral->setMaximum(9999.000000000000000);

        gridLayout_2->addWidget(integral, 4, 1, 1, 1);

        pidSpeed = new QRadioButton(widget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(pidSpeed);
        pidSpeed->setObjectName(QString::fromUtf8("pidSpeed"));
        pidSpeed->setEnabled(true);
        pidSpeed->setChecked(true);

        gridLayout_2->addWidget(pidSpeed, 1, 2, 1, 1);

        pidPosition = new QRadioButton(widget);
        buttonGroup->addButton(pidPosition);
        pidPosition->setObjectName(QString::fromUtf8("pidPosition"));

        gridLayout_2->addWidget(pidPosition, 1, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "robot_controller", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Speed control", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        fb5->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        waveSpeed->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        fb2->setText(QString());
        fb4->setText(QString());
        fb3->setText(QString());
        sp2->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Int. min", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "First val", nullptr));
        publishFirst->setText(QString());
        autoPublish->setText(QCoreApplication::translate("MainWindow", "Activate", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Filter const", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Pos. FB", nullptr));
        sp3->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Wave generator", nullptr));
        sp0->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        wavePosition->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Set Pos", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Int. max", nullptr));
        fb0->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "Joint #", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset robot", nullptr));
        fb1->setText(QString());
        sp5->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        sp1->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Second val", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Joint #", nullptr));
        sp4->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Switch time", nullptr));
        publishPID->setText(QCoreApplication::translate("MainWindow", "Publish", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "PID setter", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "milliseconds", nullptr));
        publishSecond->setText(QString());
        label_27->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Position control", nullptr));
        pidSpeed->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        pidPosition->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ROBOT_CONTROLLERKKSIPB_H
