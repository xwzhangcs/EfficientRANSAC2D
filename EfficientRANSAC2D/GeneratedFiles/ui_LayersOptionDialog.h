/********************************************************************************
** Form generated from reading UI file 'LayersOptionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYERSOPTIONDIALOG_H
#define UI_LAYERSOPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LayersOptionDialog
{
public:
    QPushButton *pushButtonCancel;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lineEditCurveMinAngle;
    QLineEdit *lineEditCurveNumIterations;
    QLabel *label_5;
    QLineEdit *lineEditCurveMaxRadius;
    QLineEdit *lineEditCurveMinRadius;
    QLineEdit *lineEditCurveMaxErrorRatioToRadius;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_7;
    QLineEdit *lineEditCurveMinPoints;
    QLineEdit *lineEditCurveClusterEpsilon;
    QLabel *label_14;
    QGroupBox *groupBox_2;
    QLineEdit *lineEditLineMinLength;
    QLineEdit *lineEditLineClusterEpsilon;
    QLineEdit *lineEditLineMinPoints;
    QLineEdit *lineEditLineMaxError;
    QLineEdit *lineEditLineNumIterations;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *lineEditLineAngleThreshold;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_19;
    QLineEdit *lineEditRAMaxError;
    QLineEdit *lineEditRAClusterEpsilon;
    QCheckBox *checkBoxUseRA;
    QCheckBox *checkBoxRAOptimization;
    QLabel *label_20;
    QPushButton *pushButtonOK;
    QGroupBox *groupBox_4;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *lineEditInput;
    QLineEdit *lineEditOutput;
    QPushButton *pushButtonInput;
    QPushButton *pushButtonOutput;
    QGroupBox *groupBox_3;
    QLabel *label_16;
    QLineEdit *lineEditContourMaxError;
    QLineEdit *lineEditContourAngleThreshold;
    QLabel *label_17;
    QLabel *label_18;
    QLineEdit *lineEditIOUThreshold;
    QLabel *label_23;
    QLabel *label_24;
    QCheckBox *checkBoxSymmetryLine;
    QCheckBox *checkBoxParallel;
    QLabel *label_25;
    QLabel *label_26;
    QLineEdit *lineEditParallelThreshold;
    QCheckBox *checkBoxRA;
    QLabel *label_27;
    QLineEdit *lineEditRAthreshold;
    QLabel *label_28;
    QLabel *label_29;
    QLineEdit *lineEditSymmetryWeight;
    QLineEdit *lineEditRaWeight;
    QLabel *label_30;
    QLineEdit *lineEditParallelWeight;
    QLabel *label_31;
    QLabel *label_32;
    QLineEdit *lineEditAccuracyWeight;
    QCheckBox *checkBoxAccuracy;

    void setupUi(QDialog *LayersOptionDialog)
    {
        if (LayersOptionDialog->objectName().isEmpty())
            LayersOptionDialog->setObjectName(QStringLiteral("LayersOptionDialog"));
        LayersOptionDialog->resize(305, 861);
        pushButtonCancel = new QPushButton(LayersOptionDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(171, 821, 91, 31));
        groupBox = new QGroupBox(LayersOptionDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(11, 91, 281, 171));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 81, 16));
        lineEditCurveMinAngle = new QLineEdit(groupBox);
        lineEditCurveMinAngle->setObjectName(QStringLiteral("lineEditCurveMinAngle"));
        lineEditCurveMinAngle->setGeometry(QRect(140, 100, 101, 20));
        lineEditCurveNumIterations = new QLineEdit(groupBox);
        lineEditCurveNumIterations->setObjectName(QStringLiteral("lineEditCurveNumIterations"));
        lineEditCurveNumIterations->setGeometry(QRect(140, 20, 101, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 120, 131, 16));
        lineEditCurveMaxRadius = new QLineEdit(groupBox);
        lineEditCurveMaxRadius->setObjectName(QStringLiteral("lineEditCurveMaxRadius"));
        lineEditCurveMaxRadius->setGeometry(QRect(140, 140, 101, 20));
        lineEditCurveMinRadius = new QLineEdit(groupBox);
        lineEditCurveMinRadius->setObjectName(QStringLiteral("lineEditCurveMinRadius"));
        lineEditCurveMinRadius->setGeometry(QRect(140, 120, 101, 20));
        lineEditCurveMaxErrorRatioToRadius = new QLineEdit(groupBox);
        lineEditCurveMaxErrorRatioToRadius->setObjectName(QStringLiteral("lineEditCurveMaxErrorRatioToRadius"));
        lineEditCurveMaxErrorRatioToRadius->setGeometry(QRect(140, 60, 101, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 131, 16));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 140, 131, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 80, 131, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 100, 131, 16));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 20, 81, 16));
        lineEditCurveMinPoints = new QLineEdit(groupBox);
        lineEditCurveMinPoints->setObjectName(QStringLiteral("lineEditCurveMinPoints"));
        lineEditCurveMinPoints->setGeometry(QRect(140, 40, 101, 20));
        lineEditCurveClusterEpsilon = new QLineEdit(groupBox);
        lineEditCurveClusterEpsilon->setObjectName(QStringLiteral("lineEditCurveClusterEpsilon"));
        lineEditCurveClusterEpsilon->setGeometry(QRect(140, 80, 101, 20));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(250, 100, 31, 16));
        groupBox_2 = new QGroupBox(LayersOptionDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(11, 271, 281, 241));
        lineEditLineMinLength = new QLineEdit(groupBox_2);
        lineEditLineMinLength->setObjectName(QStringLiteral("lineEditLineMinLength"));
        lineEditLineMinLength->setGeometry(QRect(140, 100, 101, 20));
        lineEditLineClusterEpsilon = new QLineEdit(groupBox_2);
        lineEditLineClusterEpsilon->setObjectName(QStringLiteral("lineEditLineClusterEpsilon"));
        lineEditLineClusterEpsilon->setGeometry(QRect(140, 80, 101, 20));
        lineEditLineMinPoints = new QLineEdit(groupBox_2);
        lineEditLineMinPoints->setObjectName(QStringLiteral("lineEditLineMinPoints"));
        lineEditLineMinPoints->setGeometry(QRect(140, 40, 101, 20));
        lineEditLineMaxError = new QLineEdit(groupBox_2);
        lineEditLineMaxError->setObjectName(QStringLiteral("lineEditLineMaxError"));
        lineEditLineMaxError->setGeometry(QRect(140, 60, 101, 20));
        lineEditLineNumIterations = new QLineEdit(groupBox_2);
        lineEditLineNumIterations->setObjectName(QStringLiteral("lineEditLineNumIterations"));
        lineEditLineNumIterations->setGeometry(QRect(140, 20, 101, 20));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 80, 131, 16));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 20, 81, 16));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 40, 81, 16));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 100, 131, 16));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 60, 131, 16));
        lineEditLineAngleThreshold = new QLineEdit(groupBox_2);
        lineEditLineAngleThreshold->setObjectName(QStringLiteral("lineEditLineAngleThreshold"));
        lineEditLineAngleThreshold->setGeometry(QRect(140, 120, 101, 20));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 120, 131, 16));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(250, 120, 31, 16));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 170, 131, 16));
        lineEditRAMaxError = new QLineEdit(groupBox_2);
        lineEditRAMaxError->setObjectName(QStringLiteral("lineEditRAMaxError"));
        lineEditRAMaxError->setGeometry(QRect(140, 170, 101, 20));
        lineEditRAClusterEpsilon = new QLineEdit(groupBox_2);
        lineEditRAClusterEpsilon->setObjectName(QStringLiteral("lineEditRAClusterEpsilon"));
        lineEditRAClusterEpsilon->setGeometry(QRect(140, 190, 101, 20));
        checkBoxUseRA = new QCheckBox(groupBox_2);
        checkBoxUseRA->setObjectName(QStringLiteral("checkBoxUseRA"));
        checkBoxUseRA->setGeometry(QRect(10, 150, 141, 17));
        checkBoxRAOptimization = new QCheckBox(groupBox_2);
        checkBoxRAOptimization->setObjectName(QStringLiteral("checkBoxRAOptimization"));
        checkBoxRAOptimization->setGeometry(QRect(10, 210, 101, 17));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 190, 131, 16));
        pushButtonOK = new QPushButton(LayersOptionDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(41, 821, 91, 31));
        groupBox_4 = new QGroupBox(LayersOptionDialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(11, 5, 281, 81));
        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 20, 47, 13));
        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 50, 47, 13));
        lineEditInput = new QLineEdit(groupBox_4);
        lineEditInput->setObjectName(QStringLiteral("lineEditInput"));
        lineEditInput->setGeometry(QRect(50, 20, 161, 20));
        lineEditOutput = new QLineEdit(groupBox_4);
        lineEditOutput->setObjectName(QStringLiteral("lineEditOutput"));
        lineEditOutput->setGeometry(QRect(50, 50, 161, 20));
        pushButtonInput = new QPushButton(groupBox_4);
        pushButtonInput->setObjectName(QStringLiteral("pushButtonInput"));
        pushButtonInput->setGeometry(QRect(220, 20, 51, 23));
        pushButtonOutput = new QPushButton(groupBox_4);
        pushButtonOutput->setObjectName(QStringLiteral("pushButtonOutput"));
        pushButtonOutput->setGeometry(QRect(220, 50, 51, 23));
        groupBox_3 = new QGroupBox(LayersOptionDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(11, 521, 281, 291));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 20, 91, 16));
        lineEditContourMaxError = new QLineEdit(groupBox_3);
        lineEditContourMaxError->setObjectName(QStringLiteral("lineEditContourMaxError"));
        lineEditContourMaxError->setGeometry(QRect(140, 20, 101, 20));
        lineEditContourAngleThreshold = new QLineEdit(groupBox_3);
        lineEditContourAngleThreshold->setObjectName(QStringLiteral("lineEditContourAngleThreshold"));
        lineEditContourAngleThreshold->setGeometry(QRect(140, 40, 101, 20));
        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 40, 91, 16));
        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(250, 40, 31, 16));
        lineEditIOUThreshold = new QLineEdit(groupBox_3);
        lineEditIOUThreshold->setObjectName(QStringLiteral("lineEditIOUThreshold"));
        lineEditIOUThreshold->setGeometry(QRect(140, 80, 101, 20));
        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 80, 131, 16));
        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(250, 80, 47, 13));
        checkBoxSymmetryLine = new QCheckBox(groupBox_3);
        checkBoxSymmetryLine->setObjectName(QStringLiteral("checkBoxSymmetryLine"));
        checkBoxSymmetryLine->setGeometry(QRect(10, 60, 131, 17));
        checkBoxParallel = new QCheckBox(groupBox_3);
        checkBoxParallel->setObjectName(QStringLiteral("checkBoxParallel"));
        checkBoxParallel->setGeometry(QRect(10, 180, 121, 20));
        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 140, 121, 16));
        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(250, 200, 31, 21));
        lineEditParallelThreshold = new QLineEdit(groupBox_3);
        lineEditParallelThreshold->setObjectName(QStringLiteral("lineEditParallelThreshold"));
        lineEditParallelThreshold->setGeometry(QRect(140, 200, 101, 22));
        checkBoxRA = new QCheckBox(groupBox_3);
        checkBoxRA->setObjectName(QStringLiteral("checkBoxRA"));
        checkBoxRA->setGeometry(QRect(10, 120, 81, 20));
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(250, 140, 31, 16));
        lineEditRAthreshold = new QLineEdit(groupBox_3);
        lineEditRAthreshold->setObjectName(QStringLiteral("lineEditRAthreshold"));
        lineEditRAthreshold->setGeometry(QRect(140, 140, 101, 22));
        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(10, 200, 94, 16));
        label_29 = new QLabel(groupBox_3);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(10, 100, 47, 13));
        lineEditSymmetryWeight = new QLineEdit(groupBox_3);
        lineEditSymmetryWeight->setObjectName(QStringLiteral("lineEditSymmetryWeight"));
        lineEditSymmetryWeight->setGeometry(QRect(140, 100, 101, 20));
        lineEditRaWeight = new QLineEdit(groupBox_3);
        lineEditRaWeight->setObjectName(QStringLiteral("lineEditRaWeight"));
        lineEditRaWeight->setGeometry(QRect(140, 160, 101, 20));
        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(10, 160, 47, 13));
        lineEditParallelWeight = new QLineEdit(groupBox_3);
        lineEditParallelWeight->setObjectName(QStringLiteral("lineEditParallelWeight"));
        lineEditParallelWeight->setGeometry(QRect(140, 220, 101, 20));
        label_31 = new QLabel(groupBox_3);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(10, 220, 47, 13));
        label_32 = new QLabel(groupBox_3);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(10, 260, 47, 13));
        lineEditAccuracyWeight = new QLineEdit(groupBox_3);
        lineEditAccuracyWeight->setObjectName(QStringLiteral("lineEditAccuracyWeight"));
        lineEditAccuracyWeight->setGeometry(QRect(140, 260, 101, 20));
        checkBoxAccuracy = new QCheckBox(groupBox_3);
        checkBoxAccuracy->setObjectName(QStringLiteral("checkBoxAccuracy"));
        checkBoxAccuracy->setGeometry(QRect(10, 240, 131, 17));

        retranslateUi(LayersOptionDialog);

        QMetaObject::connectSlotsByName(LayersOptionDialog);
    } // setupUi

    void retranslateUi(QDialog *LayersOptionDialog)
    {
        LayersOptionDialog->setWindowTitle(QApplication::translate("LayersOptionDialog", "LayersOptionDialog", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("LayersOptionDialog", "Cancel", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("LayersOptionDialog", "Curve", Q_NULLPTR));
        label->setText(QApplication::translate("LayersOptionDialog", "Min points:", Q_NULLPTR));
        label_5->setText(QApplication::translate("LayersOptionDialog", "Min radius:", Q_NULLPTR));
        label_2->setText(QApplication::translate("LayersOptionDialog", "Max error ratio to radius:", Q_NULLPTR));
        label_6->setText(QApplication::translate("LayersOptionDialog", "Max radius:", Q_NULLPTR));
        label_3->setText(QApplication::translate("LayersOptionDialog", "Cluster epsilon:", Q_NULLPTR));
        label_4->setText(QApplication::translate("LayersOptionDialog", "Min angle:", Q_NULLPTR));
        label_7->setText(QApplication::translate("LayersOptionDialog", "# iterations:", Q_NULLPTR));
        label_14->setText(QApplication::translate("LayersOptionDialog", "[deg]", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("LayersOptionDialog", "Line", Q_NULLPTR));
        label_8->setText(QApplication::translate("LayersOptionDialog", "Cluster epsilon:", Q_NULLPTR));
        label_9->setText(QApplication::translate("LayersOptionDialog", "# iterations:", Q_NULLPTR));
        label_10->setText(QApplication::translate("LayersOptionDialog", "Min points:", Q_NULLPTR));
        label_11->setText(QApplication::translate("LayersOptionDialog", "Min length:", Q_NULLPTR));
        label_12->setText(QApplication::translate("LayersOptionDialog", "Max error:", Q_NULLPTR));
        label_13->setText(QApplication::translate("LayersOptionDialog", "Angle threshold:", Q_NULLPTR));
        label_15->setText(QApplication::translate("LayersOptionDialog", "[deg]", Q_NULLPTR));
        label_19->setText(QApplication::translate("LayersOptionDialog", "Max error:", Q_NULLPTR));
        checkBoxUseRA->setText(QApplication::translate("LayersOptionDialog", "Use right angle method", Q_NULLPTR));
        checkBoxRAOptimization->setText(QApplication::translate("LayersOptionDialog", "Optimization", Q_NULLPTR));
        label_20->setText(QApplication::translate("LayersOptionDialog", "Cluster epsilon:", Q_NULLPTR));
        pushButtonOK->setText(QApplication::translate("LayersOptionDialog", "OK", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("LayersOptionDialog", "Data", Q_NULLPTR));
        label_21->setText(QApplication::translate("LayersOptionDialog", "Input", Q_NULLPTR));
        label_22->setText(QApplication::translate("LayersOptionDialog", "Output", Q_NULLPTR));
        pushButtonInput->setText(QApplication::translate("LayersOptionDialog", "...", Q_NULLPTR));
        pushButtonOutput->setText(QApplication::translate("LayersOptionDialog", "...", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("LayersOptionDialog", "Contour", Q_NULLPTR));
        label_16->setText(QApplication::translate("LayersOptionDialog", "Max error:", Q_NULLPTR));
        label_17->setText(QApplication::translate("LayersOptionDialog", "Angle threshold:", Q_NULLPTR));
        label_18->setText(QApplication::translate("LayersOptionDialog", "[deg]", Q_NULLPTR));
        label_23->setText(QApplication::translate("LayersOptionDialog", "IOU threshold:", Q_NULLPTR));
        label_24->setText(QApplication::translate("LayersOptionDialog", "[%]", Q_NULLPTR));
        checkBoxSymmetryLine->setText(QApplication::translate("LayersOptionDialog", "Use symmetry line", Q_NULLPTR));
        checkBoxParallel->setText(QApplication::translate("LayersOptionDialog", "Use parallelism:", Q_NULLPTR));
        label_25->setText(QApplication::translate("LayersOptionDialog", "RA angle threshold:", Q_NULLPTR));
        label_26->setText(QApplication::translate("LayersOptionDialog", "[deg]", Q_NULLPTR));
        checkBoxRA->setText(QApplication::translate("LayersOptionDialog", "Use RA", Q_NULLPTR));
        label_27->setText(QApplication::translate("LayersOptionDialog", "[deg]", Q_NULLPTR));
        label_28->setText(QApplication::translate("LayersOptionDialog", "Angle threshold:", Q_NULLPTR));
        label_29->setText(QApplication::translate("LayersOptionDialog", "Weight:", Q_NULLPTR));
        label_30->setText(QApplication::translate("LayersOptionDialog", "Weight:", Q_NULLPTR));
        label_31->setText(QApplication::translate("LayersOptionDialog", "Weight:", Q_NULLPTR));
        label_32->setText(QApplication::translate("LayersOptionDialog", "Weight:", Q_NULLPTR));
        checkBoxAccuracy->setText(QApplication::translate("LayersOptionDialog", "Use accuracy", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LayersOptionDialog: public Ui_LayersOptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYERSOPTIONDIALOG_H
