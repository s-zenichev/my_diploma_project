/********************************************************************************
** Form generated from reading UI file 'pid_tunerbQKbjH.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PID_TUNERBQKBJH_H
#define PID_TUNERBQKBJH_H

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
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *pidTopic;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_4;
    QPushButton *publishControl;
    QDoubleSpinBox *derivative;
    QLabel *label_8;
    QDoubleSpinBox *integral;
    QDoubleSpinBox *proportional;
    QLineEdit *controlTopic;
    QLabel *label_3;
    QCheckBox *autoSwitch;
    QLabel *label_2;
    QRadioButton *radioButton;
    QDoubleSpinBox *secondValue;
    QLabel *label;
    QCheckBox *autoPublish;
    QDoubleSpinBox *firstValue;
    QPushButton *publishPID;
    QDoubleSpinBox *filterConst;
    QLabel *label_7;
    QRadioButton *radioButton_2;
    QLabel *label_9;
    QLabel *label_10;
    QSpinBox *jointNumber;
    QSpinBox *switchTime;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(492, 322);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 471, 301));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pidTopic = new QLineEdit(layoutWidget);
        pidTopic->setObjectName(QString::fromUtf8("pidTopic"));

        gridLayout->addWidget(pidTopic, 0, 1, 1, 7);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 2);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        publishControl = new QPushButton(layoutWidget);
        publishControl->setObjectName(QString::fromUtf8("publishControl"));

        gridLayout->addWidget(publishControl, 5, 8, 1, 1);

        derivative = new QDoubleSpinBox(layoutWidget);
        derivative->setObjectName(QString::fromUtf8("derivative"));

        gridLayout->addWidget(derivative, 3, 1, 1, 2);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        integral = new QDoubleSpinBox(layoutWidget);
        integral->setObjectName(QString::fromUtf8("integral"));

        gridLayout->addWidget(integral, 2, 1, 1, 2);

        proportional = new QDoubleSpinBox(layoutWidget);
        proportional->setObjectName(QString::fromUtf8("proportional"));

        gridLayout->addWidget(proportional, 1, 1, 1, 2);

        controlTopic = new QLineEdit(layoutWidget);
        controlTopic->setObjectName(QString::fromUtf8("controlTopic"));

        gridLayout->addWidget(controlTopic, 5, 2, 1, 2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        autoSwitch = new QCheckBox(layoutWidget);
        autoSwitch->setObjectName(QString::fromUtf8("autoSwitch"));

        gridLayout->addWidget(autoSwitch, 6, 5, 1, 4);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        radioButton = new QRadioButton(layoutWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setEnabled(true);
        radioButton->setChecked(true);

        gridLayout->addWidget(radioButton, 6, 3, 1, 2);

        secondValue = new QDoubleSpinBox(layoutWidget);
        secondValue->setObjectName(QString::fromUtf8("secondValue"));

        gridLayout->addWidget(secondValue, 7, 2, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        autoPublish = new QCheckBox(layoutWidget);
        autoPublish->setObjectName(QString::fromUtf8("autoPublish"));

        gridLayout->addWidget(autoPublish, 5, 4, 1, 4);

        firstValue = new QDoubleSpinBox(layoutWidget);
        firstValue->setObjectName(QString::fromUtf8("firstValue"));

        gridLayout->addWidget(firstValue, 6, 2, 1, 1);

        publishPID = new QPushButton(layoutWidget);
        publishPID->setObjectName(QString::fromUtf8("publishPID"));

        gridLayout->addWidget(publishPID, 0, 8, 1, 1);

        filterConst = new QDoubleSpinBox(layoutWidget);
        filterConst->setObjectName(QString::fromUtf8("filterConst"));

        gridLayout->addWidget(filterConst, 4, 1, 1, 2);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        radioButton_2 = new QRadioButton(layoutWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        gridLayout->addWidget(radioButton_2, 7, 3, 1, 2);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 7, 7, 1, 2);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 4, 5, 1, 1);

        jointNumber = new QSpinBox(layoutWidget);
        jointNumber->setObjectName(QString::fromUtf8("jointNumber"));
        jointNumber->setMaximum(5);

        gridLayout->addWidget(jointNumber, 4, 8, 1, 1);

        switchTime = new QSpinBox(layoutWidget);
        switchTime->setObjectName(QString::fromUtf8("switchTime"));
        switchTime->setMaximum(10000);
        switchTime->setValue(1000);

        gridLayout->addWidget(switchTime, 7, 5, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PID_tuner", nullptr));
        pidTopic->setText(QCoreApplication::translate("MainWindow", "/joint0_pid", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Control topic", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Filter const", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        publishControl->setText(QCoreApplication::translate("MainWindow", "Publish", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "First val", nullptr));
        controlTopic->setText(QCoreApplication::translate("MainWindow", "/effort_controller/commands", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        autoSwitch->setText(QCoreApplication::translate("MainWindow", "Auto switch", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        radioButton->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Topic name", nullptr));
        autoPublish->setText(QCoreApplication::translate("MainWindow", "AutoPublish", nullptr));
        publishPID->setText(QCoreApplication::translate("MainWindow", "Publish", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Second val", nullptr));
        radioButton_2->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "milliseconds", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Joint #", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PID_TUNERBQKBJH_H
