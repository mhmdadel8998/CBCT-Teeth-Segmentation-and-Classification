/********************************************************************************
** Form generated from reading UI file 'MainWindowmPSKkQ.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWMPSKKQ_H
#define MAINWINDOWMPSKKQ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qvtkopenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionrotate;
    QAction *actionmove;
    QAction *actionZoomIN;
    QAction *actionZoomout;
    QAction *actionMIP;
    QAction *actionSkin;
    QAction *actionMuscle;
    QAction *actionBone;
    QWidget *centralwidget;
    QVTKOpenGLWidget *openGLWidget;
    QVTKOpenGLWidget *openGLWidget_2;
    QVTKOpenGLWidget *openGLWidget_3;
    QVTKOpenGLWidget *openGLWidget_4;
    QVTKOpenGLWidget *openGLWidget_5;
    QVTKOpenGLWidget *openGLWidget_6;
    QVTKOpenGLWidget *openGLWidget_7;
    QVTKOpenGLWidget *openGLWidget_8;
    QVTKOpenGLWidget *openGLWidget_9;
    QVTKOpenGLWidget *openGLWidget_10;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuVolume;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1824, 959);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("C:/Users/Mo/Downloads/26-268656_open-file-folder-icon-folder-files-icon-png.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionrotate = new QAction(MainWindow);
        actionrotate->setObjectName(QString::fromUtf8("actionrotate"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("C:/Users/Mo/Downloads/437-4374497_rotating-arrow-symbol-icon-rotate-arrow-png-transparent.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrotate->setIcon(icon1);
        actionmove = new QAction(MainWindow);
        actionmove->setObjectName(QString::fromUtf8("actionmove"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("C:/Users/Mo/Downloads/file-svg-move-icon-11563347037wxavun0mrl.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionmove->setIcon(icon2);
        actionZoomIN = new QAction(MainWindow);
        actionZoomIN->setObjectName(QString::fromUtf8("actionZoomIN"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("C:/Users/Mo/Downloads/images.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomIN->setIcon(icon3);
        actionZoomout = new QAction(MainWindow);
        actionZoomout->setObjectName(QString::fromUtf8("actionZoomout"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("C:/Users/Mo/Downloads/download (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomout->setIcon(icon4);
        actionMIP = new QAction(MainWindow);
        actionMIP->setObjectName(QString::fromUtf8("actionMIP"));
        actionSkin = new QAction(MainWindow);
        actionSkin->setObjectName(QString::fromUtf8("actionSkin"));
        actionMuscle = new QAction(MainWindow);
        actionMuscle->setObjectName(QString::fromUtf8("actionMuscle"));
        actionBone = new QAction(MainWindow);
        actionBone->setObjectName(QString::fromUtf8("actionBone"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new QVTKOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 10, 391, 281));
        openGLWidget_2 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_2->setObjectName(QString::fromUtf8("openGLWidget_2"));
        openGLWidget_2->setGeometry(QRect(10, 300, 391, 281));
        openGLWidget_3 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_3->setObjectName(QString::fromUtf8("openGLWidget_3"));
        openGLWidget_3->setGeometry(QRect(10, 590, 391, 281));
        openGLWidget_4 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_4->setObjectName(QString::fromUtf8("openGLWidget_4"));
        openGLWidget_4->setGeometry(QRect(420, 10, 391, 281));
        openGLWidget_5 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_5->setObjectName(QString::fromUtf8("openGLWidget_5"));
        openGLWidget_5->setGeometry(QRect(420, 300, 391, 281));
        openGLWidget_6 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_6->setObjectName(QString::fromUtf8("openGLWidget_6"));
        openGLWidget_6->setGeometry(QRect(420, 590, 391, 281));
        openGLWidget_7 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_7->setObjectName(QString::fromUtf8("openGLWidget_7"));
        openGLWidget_7->setGeometry(QRect(830, 10, 391, 281));
        openGLWidget_8 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_8->setObjectName(QString::fromUtf8("openGLWidget_8"));
        openGLWidget_8->setGeometry(QRect(830, 300, 391, 281));
        openGLWidget_9 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_9->setObjectName(QString::fromUtf8("openGLWidget_9"));
        openGLWidget_9->setGeometry(QRect(830, 590, 391, 281));
        openGLWidget_10 = new QVTKOpenGLWidget(centralwidget);
        openGLWidget_10->setObjectName(QString::fromUtf8("openGLWidget_10"));
        openGLWidget_10->setGeometry(QRect(1240, 10, 581, 861));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1824, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuVolume = new QMenu(menuEdit);
        menuVolume->setObjectName(QString::fromUtf8("menuVolume"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionOpen);
        menuEdit->addAction(menuVolume->menuAction());
        menuVolume->addAction(actionMIP);
        menuVolume->addAction(actionSkin);
        menuVolume->addAction(actionMuscle);
        menuVolume->addAction(actionBone);
        toolBar->addAction(actionrotate);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionrotate->setText(QCoreApplication::translate("MainWindow", "rotate", nullptr));
        actionmove->setText(QCoreApplication::translate("MainWindow", "move", nullptr));
        actionZoomIN->setText(QCoreApplication::translate("MainWindow", "ZoomIN", nullptr));
        actionZoomout->setText(QCoreApplication::translate("MainWindow", "Zoomout", nullptr));
        actionMIP->setText(QCoreApplication::translate("MainWindow", "MIP", nullptr));
        actionSkin->setText(QCoreApplication::translate("MainWindow", "Skin", nullptr));
        actionMuscle->setText(QCoreApplication::translate("MainWindow", "Muscle", nullptr));
        actionBone->setText(QCoreApplication::translate("MainWindow", "Bone", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuVolume->setTitle(QCoreApplication::translate("MainWindow", "Volume", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWMPSKKQ_H
