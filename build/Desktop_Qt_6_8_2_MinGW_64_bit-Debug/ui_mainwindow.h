/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtServerIP;
    QLineEdit *txtServerPort;
    QPushButton *btnConnect;
    QLineEdit *txtKey;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtFilePath;
    QPushButton *btnChooseFile;
    QPushButton *btnEncrypt;
    QGroupBox *horizontalGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnSendFile;
    QLabel *label;
    QTextEdit *txtLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        txtServerIP = new QLineEdit(centralwidget);
        txtServerIP->setObjectName("txtServerIP");

        horizontalLayout->addWidget(txtServerIP);

        txtServerPort = new QLineEdit(centralwidget);
        txtServerPort->setObjectName("txtServerPort");

        horizontalLayout->addWidget(txtServerPort);

        btnConnect = new QPushButton(centralwidget);
        btnConnect->setObjectName("btnConnect");

        horizontalLayout->addWidget(btnConnect);


        verticalLayout->addLayout(horizontalLayout);

        txtKey = new QLineEdit(centralwidget);
        txtKey->setObjectName("txtKey");
        txtKey->setReadOnly(true);

        verticalLayout->addWidget(txtKey);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        txtFilePath = new QLineEdit(centralwidget);
        txtFilePath->setObjectName("txtFilePath");
        txtFilePath->setReadOnly(true);

        horizontalLayout_2->addWidget(txtFilePath);

        btnChooseFile = new QPushButton(centralwidget);
        btnChooseFile->setObjectName("btnChooseFile");

        horizontalLayout_2->addWidget(btnChooseFile);

        btnEncrypt = new QPushButton(centralwidget);
        btnEncrypt->setObjectName("btnEncrypt");

        horizontalLayout_2->addWidget(btnEncrypt);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalGroupBox = new QGroupBox(centralwidget);
        horizontalGroupBox->setObjectName("horizontalGroupBox");
        horizontalLayout_4 = new QHBoxLayout(horizontalGroupBox);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        btnSendFile = new QPushButton(horizontalGroupBox);
        btnSendFile->setObjectName("btnSendFile");

        horizontalLayout_4->addWidget(btnSendFile);


        verticalLayout->addWidget(horizontalGroupBox);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        txtLog = new QTextEdit(centralwidget);
        txtLog->setObjectName("txtLog");
        txtLog->setReadOnly(true);

        verticalLayout->addWidget(txtLog);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Client Application", nullptr));
        txtServerIP->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter server IP", nullptr));
        txtServerPort->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter port", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        txtKey->setPlaceholderText(QCoreApplication::translate("MainWindow", "Secret key", nullptr));
        txtFilePath->setPlaceholderText(QCoreApplication::translate("MainWindow", "No file selected", nullptr));
        btnChooseFile->setText(QCoreApplication::translate("MainWindow", "Choose file", nullptr));
        btnEncrypt->setText(QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        btnSendFile->setText(QCoreApplication::translate("MainWindow", "Send file", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Client logs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
