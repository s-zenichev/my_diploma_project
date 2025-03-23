/********************************************************************************
** Form generated from reading UI file 'pid_tunerOcPELL.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PID_TUNEROCPELL_H
#define PID_TUNEROCPELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *pidTopic;
    QPushButton *publishPID;
    QLabel *label_2;
    QDoubleSpinBox *proportional;
    QLabel *label_3;
    QDoubleSpinBox *integral;
    QLabel *label_4;
    QDoubleSpinBox *derivative;
    QLabel *label_5;
    QDoubleSpinBox *filterConst;
    QLabel *label_10;
    QSpinBox *jointNumber;
    QLabel *label_6;
    QLineEdit *controlTopic;
    QPushButton *publishControl;
    QCheckBox *autoSwitch;
    QSpinBox *switchTime;
    QLabel *label_9;
    QCheckBox *autoPublish;
    QLabel *label_8;
    QDoubleSpinBox *firstValue;
    QRadioButton *radioButton;
    QLabel *label_7;
    QDoubleSpinBox *secondValue;
    QRadioButton *radioButton_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(501, 379);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(11, 16, 481, 351));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pidTopic = new QLineEdit(widget);
        pidTopic->setObjectName(QString::fromUtf8("pidTopic"));

        gridLayout->addWidget(pidTopic, 0, 1, 1, 6);

        publishPID = new QPushButton(widget);
        publishPID->setObjectName(QString::fromUtf8("publishPID"));

        gridLayout->addWidget(publishPID, 0, 7, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        proportional = new QDoubleSpinBox(widget);
        proportional->setObjectName(QString::fromUtf8("proportional"));
        proportional->setMaximum(9999.000000000000000);

        gridLayout->addWidget(proportional, 1, 1, 1, 3);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        integral = new QDoubleSpinBox(widget);
        integral->setObjectName(QString::fromUtf8("integral"));
        integral->setMaximum(9999.000000000000000);

        gridLayout->addWidget(integral, 2, 1, 1, 3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        derivative = new QDoubleSpinBox(widget);
        derivative->setObjectName(QString::fromUtf8("derivative"));
        derivative->setMaximum(9999.000000000000000);

        gridLayout->addWidget(derivative, 3, 1, 1, 3);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        filterConst = new QDoubleSpinBox(widget);
        filterConst->setObjectName(QString::fromUtf8("filterConst"));
        filterConst->setMaximum(999.000000000000000);
        filterConst->setValue(100.000000000000000);

        gridLayout->addWidget(filterConst, 4, 1, 1, 3);

        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 4, 5, 1, 1);

        jointNumber = new QSpinBox(widget);
        jointNumber->setObjectName(QString::fromUtf8("jointNumber"));
        jointNumber->setMaximum(5);

        gridLayout->addWidget(jointNumber, 4, 7, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 2);

        controlTopic = new QLineEdit(widget);
        controlTopic->setObjectName(QString::fromUtf8("controlTopic"));

        gridLayout->addWidget(controlTopic, 5, 2, 1, 5);

        publishControl = new QPushButton(widget);
        publishControl->setObjectName(QString::fromUtf8("publishControl"));

        gridLayout->addWidget(publishControl, 5, 7, 1, 1);

        autoSwitch = new QCheckBox(widget);
        autoSwitch->setObjectName(QString::fromUtf8("autoSwitch"));

        gridLayout->addWidget(autoSwitch, 6, 0, 1, 3);

        switchTime = new QSpinBox(widget);
        switchTime->setObjectName(QString::fromUtf8("switchTime"));
        switchTime->setMaximum(10000);
        switchTime->setValue(1000);

        gridLayout->addWidget(switchTime, 6, 3, 1, 2);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 6, 5, 1, 1);

        autoPublish = new QCheckBox(widget);
        autoPublish->setObjectName(QString::fromUtf8("autoPublish"));

        gridLayout->addWidget(autoPublish, 6, 6, 1, 2);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        firstValue = new QDoubleSpinBox(widget);
        firstValue->setObjectName(QString::fromUtf8("firstValue"));
        firstValue->setMinimum(-999.000000000000000);
        firstValue->setMaximum(999.000000000000000);

        gridLayout->addWidget(firstValue, 7, 3, 1, 1);

        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setEnabled(true);
        radioButton->setChecked(true);

        gridLayout->addWidget(radioButton, 7, 4, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 8, 0, 1, 1);

        secondValue = new QDoubleSpinBox(widget);
        secondValue->setObjectName(QString::fromUtf8("secondValue"));
        secondValue->setMinimum(-999.000000000000000);
        secondValue->setMaximum(999.000000000000000);

        gridLayout->addWidget(secondValue, 8, 3, 1, 1);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        gridLayout->addWidget(radioButton_2, 8, 4, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PID_tuner", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Topic name", nullptr));
        pidTopic->setText(QCoreApplication::translate("MainWindow", "/pid_values", nullptr));
        publishPID->setText(QCoreApplication::translate("MainWindow", "Publish", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Filter const", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Joint #", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Control topic", nullptr));
        controlTopic->setText(QCoreApplication::translate("MainWindow", "/desired/joint_speeds", nullptr));
        publishControl->setText(QCoreApplication::translate("MainWindow", "Publish", nullptr));
        autoSwitch->setText(QCoreApplication::translate("MainWindow", "Auto switch", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "milliseconds", nullptr));
        autoPublish->setText(QCoreApplication::translate("MainWindow", "AutoPublish", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "First val", nullptr));
        radioButton->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Second val", nullptr));
        radioButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PID_TUNEROCPELL_H
