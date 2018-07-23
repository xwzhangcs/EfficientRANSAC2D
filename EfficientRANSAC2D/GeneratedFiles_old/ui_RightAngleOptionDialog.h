/********************************************************************************
** Form generated from reading UI file 'RightAngleOptionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RIGHTANGLEOPTIONDIALOG_H
#define UI_RIGHTANGLEOPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RightAngleOptionDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxResolution;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;
    QCheckBox *checkBoxOptimization;

    void setupUi(QDialog *RightAngleOptionDialog)
    {
        if (RightAngleOptionDialog->objectName().isEmpty())
            RightAngleOptionDialog->setObjectName(QStringLiteral("RightAngleOptionDialog"));
        RightAngleOptionDialog->resize(246, 111);
        RightAngleOptionDialog->setMinimumSize(QSize(246, 100));
        RightAngleOptionDialog->setMaximumSize(QSize(346, 300));
        label = new QLabel(RightAngleOptionDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 61, 21));
        spinBoxResolution = new QSpinBox(RightAngleOptionDialog);
        spinBoxResolution->setObjectName(QStringLiteral("spinBoxResolution"));
        spinBoxResolution->setGeometry(QRect(160, 10, 61, 22));
        pushButtonCancel = new QPushButton(RightAngleOptionDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(130, 70, 81, 31));
        pushButtonOK = new QPushButton(RightAngleOptionDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(30, 70, 81, 31));
        checkBoxOptimization = new QCheckBox(RightAngleOptionDialog);
        checkBoxOptimization->setObjectName(QStringLiteral("checkBoxOptimization"));
        checkBoxOptimization->setGeometry(QRect(20, 40, 141, 17));

        retranslateUi(RightAngleOptionDialog);

        QMetaObject::connectSlotsByName(RightAngleOptionDialog);
    } // setupUi

    void retranslateUi(QDialog *RightAngleOptionDialog)
    {
        RightAngleOptionDialog->setWindowTitle(QApplication::translate("RightAngleOptionDialog", "Option Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("RightAngleOptionDialog", "Resolution:", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("RightAngleOptionDialog", "Cancel", Q_NULLPTR));
        pushButtonOK->setText(QApplication::translate("RightAngleOptionDialog", "OK", Q_NULLPTR));
        checkBoxOptimization->setText(QApplication::translate("RightAngleOptionDialog", "Optimization", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RightAngleOptionDialog: public Ui_RightAngleOptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RIGHTANGLEOPTIONDIALOG_H
