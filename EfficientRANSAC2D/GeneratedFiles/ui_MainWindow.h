/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionDetectContours;
    QAction *actionDetectCurves;
    QAction *actionDetectLines;
    QAction *actionDetectCurvesLines;
    QAction *actionSave;
    QAction *actionGenerateContours;
    QAction *actionRightAngle;
    QAction *actionDetectCurvesLinesWithRA;
    QAction *actionBatchFiles;
    QAction *actionReflection;
    QAction *actionDetectSymmetryLine;
    QAction *actionLayers;
    QAction *actionCombineImages;
    QAction *actionMulti_Runs;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTool;
    QMenu *menuTest;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(805, 720);
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionDetectContours = new QAction(MainWindowClass);
        actionDetectContours->setObjectName(QStringLiteral("actionDetectContours"));
        actionDetectCurves = new QAction(MainWindowClass);
        actionDetectCurves->setObjectName(QStringLiteral("actionDetectCurves"));
        actionDetectLines = new QAction(MainWindowClass);
        actionDetectLines->setObjectName(QStringLiteral("actionDetectLines"));
        actionDetectCurvesLines = new QAction(MainWindowClass);
        actionDetectCurvesLines->setObjectName(QStringLiteral("actionDetectCurvesLines"));
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Resources/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionGenerateContours = new QAction(MainWindowClass);
        actionGenerateContours->setObjectName(QStringLiteral("actionGenerateContours"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Resources/contour.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGenerateContours->setIcon(icon2);
        actionRightAngle = new QAction(MainWindowClass);
        actionRightAngle->setObjectName(QStringLiteral("actionRightAngle"));
        actionDetectCurvesLinesWithRA = new QAction(MainWindowClass);
        actionDetectCurvesLinesWithRA->setObjectName(QStringLiteral("actionDetectCurvesLinesWithRA"));
        actionBatchFiles = new QAction(MainWindowClass);
        actionBatchFiles->setObjectName(QStringLiteral("actionBatchFiles"));
        actionReflection = new QAction(MainWindowClass);
        actionReflection->setObjectName(QStringLiteral("actionReflection"));
        actionDetectSymmetryLine = new QAction(MainWindowClass);
        actionDetectSymmetryLine->setObjectName(QStringLiteral("actionDetectSymmetryLine"));
        actionLayers = new QAction(MainWindowClass);
        actionLayers->setObjectName(QStringLiteral("actionLayers"));
        actionCombineImages = new QAction(MainWindowClass);
        actionCombineImages->setObjectName(QStringLiteral("actionCombineImages"));
        actionMulti_Runs = new QAction(MainWindowClass);
        actionMulti_Runs->setObjectName(QStringLiteral("actionMulti_Runs"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 805, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QStringLiteral("menuTool"));
        menuTest = new QMenu(menuBar);
        menuTest->setObjectName(QStringLiteral("menuTest"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuBar->addAction(menuTest->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTool->addAction(actionDetectCurves);
        menuTool->addAction(actionDetectLines);
        menuTool->addAction(actionRightAngle);
        menuTool->addAction(actionDetectSymmetryLine);
        menuTool->addSeparator();
        menuTool->addAction(actionDetectCurvesLines);
        menuTool->addSeparator();
        menuTool->addAction(actionGenerateContours);
        menuTest->addAction(actionBatchFiles);
        menuTest->addAction(actionReflection);
        menuTest->addAction(actionLayers);
        menuTest->addAction(actionCombineImages);
        menuTest->addAction(actionMulti_Runs);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Efficient RANSAC 2D", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDetectContours->setText(QApplication::translate("MainWindowClass", "Detect Contours", Q_NULLPTR));
        actionDetectCurves->setText(QApplication::translate("MainWindowClass", "Detect Curves", Q_NULLPTR));
        actionDetectLines->setText(QApplication::translate("MainWindowClass", "Detect Lines", Q_NULLPTR));
        actionDetectCurvesLines->setText(QApplication::translate("MainWindowClass", "Detect Curves/Lines", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindowClass", "Save", Q_NULLPTR));
        actionGenerateContours->setText(QApplication::translate("MainWindowClass", "Generate Contours", Q_NULLPTR));
        actionRightAngle->setText(QApplication::translate("MainWindowClass", "Right Angle", Q_NULLPTR));
        actionDetectCurvesLinesWithRA->setText(QApplication::translate("MainWindowClass", "Detect Curves/Lines with RA", Q_NULLPTR));
        actionBatchFiles->setText(QApplication::translate("MainWindowClass", "Batch Files", Q_NULLPTR));
        actionReflection->setText(QApplication::translate("MainWindowClass", "Reflection", Q_NULLPTR));
        actionDetectSymmetryLine->setText(QApplication::translate("MainWindowClass", "Detect Symmetry Line", Q_NULLPTR));
        actionLayers->setText(QApplication::translate("MainWindowClass", "Use Layers", Q_NULLPTR));
        actionCombineImages->setText(QApplication::translate("MainWindowClass", "Combine images", Q_NULLPTR));
        actionMulti_Runs->setText(QApplication::translate("MainWindowClass", "Multiple Runs", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", Q_NULLPTR));
        menuTool->setTitle(QApplication::translate("MainWindowClass", "Tool", Q_NULLPTR));
        menuTest->setTitle(QApplication::translate("MainWindowClass", "Test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
