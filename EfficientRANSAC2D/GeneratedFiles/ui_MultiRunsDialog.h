/********************************************************************************
** Form generated from reading UI file 'MultiRunsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIRUNSDIALOG_H
#define UI_MULTIRUNSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MultiRunsDialog
{
public:
    QGroupBox *groupBox_4;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *lineEditInput;
    QLineEdit *lineEditOutput;
    QPushButton *pushButtonInput;
    QPushButton *pushButtonOutput;
    QLineEdit *lineEditInputConfig;
    QPushButton *pushButtonInputConfig;
    QLabel *label_23;
    QPushButton *pushButtonInputDetect;
    QLineEdit *lineEditInputDetect;
    QLabel *label_24;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *MultiRunsDialog)
    {
        if (MultiRunsDialog->objectName().isEmpty())
            MultiRunsDialog->setObjectName(QStringLiteral("MultiRunsDialog"));
        MultiRunsDialog->resize(321, 210);
        groupBox_4 = new QGroupBox(MultiRunsDialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(13, 10, 291, 141));
        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 20, 47, 13));
        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 106, 47, 13));
        lineEditInput = new QLineEdit(groupBox_4);
        lineEditInput->setObjectName(QStringLiteral("lineEditInput"));
        lineEditInput->setGeometry(QRect(57, 20, 161, 20));
        lineEditOutput = new QLineEdit(groupBox_4);
        lineEditOutput->setObjectName(QStringLiteral("lineEditOutput"));
        lineEditOutput->setGeometry(QRect(57, 106, 161, 20));
        pushButtonInput = new QPushButton(groupBox_4);
        pushButtonInput->setObjectName(QStringLiteral("pushButtonInput"));
        pushButtonInput->setGeometry(QRect(227, 20, 51, 23));
        pushButtonOutput = new QPushButton(groupBox_4);
        pushButtonOutput->setObjectName(QStringLiteral("pushButtonOutput"));
        pushButtonOutput->setGeometry(QRect(227, 106, 51, 23));
        lineEditInputConfig = new QLineEdit(groupBox_4);
        lineEditInputConfig->setObjectName(QStringLiteral("lineEditInputConfig"));
        lineEditInputConfig->setGeometry(QRect(57, 75, 161, 20));
        pushButtonInputConfig = new QPushButton(groupBox_4);
        pushButtonInputConfig->setObjectName(QStringLiteral("pushButtonInputConfig"));
        pushButtonInputConfig->setGeometry(QRect(227, 75, 51, 23));
        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 75, 47, 13));
        pushButtonInputDetect = new QPushButton(groupBox_4);
        pushButtonInputDetect->setObjectName(QStringLiteral("pushButtonInputDetect"));
        pushButtonInputDetect->setGeometry(QRect(227, 48, 51, 23));
        lineEditInputDetect = new QLineEdit(groupBox_4);
        lineEditInputDetect->setObjectName(QStringLiteral("lineEditInputDetect"));
        lineEditInputDetect->setGeometry(QRect(57, 48, 161, 20));
        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(10, 48, 47, 13));
        pushButtonCancel = new QPushButton(MultiRunsDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(205, 161, 91, 31));
        pushButtonOK = new QPushButton(MultiRunsDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(75, 161, 91, 31));

        retranslateUi(MultiRunsDialog);

        QMetaObject::connectSlotsByName(MultiRunsDialog);
    } // setupUi

    void retranslateUi(QDialog *MultiRunsDialog)
    {
        MultiRunsDialog->setWindowTitle(QApplication::translate("MultiRunsDialog", "MultiRunsDialog", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MultiRunsDialog", "Data", Q_NULLPTR));
        label_21->setText(QApplication::translate("MultiRunsDialog", "Input:", Q_NULLPTR));
        label_22->setText(QApplication::translate("MultiRunsDialog", "Output:", Q_NULLPTR));
        pushButtonInput->setText(QApplication::translate("MultiRunsDialog", "...", Q_NULLPTR));
        pushButtonOutput->setText(QApplication::translate("MultiRunsDialog", "...", Q_NULLPTR));
        pushButtonInputConfig->setText(QApplication::translate("MultiRunsDialog", "...", Q_NULLPTR));
        label_23->setText(QApplication::translate("MultiRunsDialog", "Opt:", Q_NULLPTR));
        pushButtonInputDetect->setText(QApplication::translate("MultiRunsDialog", "...", Q_NULLPTR));
        label_24->setText(QApplication::translate("MultiRunsDialog", "Detect:", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("MultiRunsDialog", "Cancel", Q_NULLPTR));
        pushButtonOK->setText(QApplication::translate("MultiRunsDialog", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MultiRunsDialog: public Ui_MultiRunsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIRUNSDIALOG_H
