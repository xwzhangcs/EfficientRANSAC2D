/********************************************************************************
** Form generated from reading UI file 'SymmetryLineOptionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYMMETRYLINEOPTIONDIALOG_H
#define UI_SYMMETRYLINEOPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SymmetryLineOptionDialog
{
public:
    QPushButton *pushButtonCancel;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QLineEdit *lineEditMaxError;
    QLabel *label;

    void setupUi(QDialog *SymmetryLineOptionDialog)
    {
        if (SymmetryLineOptionDialog->objectName().isEmpty())
            SymmetryLineOptionDialog->setObjectName(QStringLiteral("SymmetryLineOptionDialog"));
        SymmetryLineOptionDialog->resize(243, 109);
        pushButtonCancel = new QPushButton(SymmetryLineOptionDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(140, 60, 91, 31));
        label_2 = new QLabel(SymmetryLineOptionDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 20, 131, 16));
        pushButtonOK = new QPushButton(SymmetryLineOptionDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(30, 60, 91, 31));
        lineEditMaxError = new QLineEdit(SymmetryLineOptionDialog);
        lineEditMaxError->setObjectName(QStringLiteral("lineEditMaxError"));
        lineEditMaxError->setGeometry(QRect(110, 20, 101, 20));
        label = new QLabel(SymmetryLineOptionDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 20, 47, 13));

        retranslateUi(SymmetryLineOptionDialog);

        QMetaObject::connectSlotsByName(SymmetryLineOptionDialog);
    } // setupUi

    void retranslateUi(QDialog *SymmetryLineOptionDialog)
    {
        SymmetryLineOptionDialog->setWindowTitle(QApplication::translate("SymmetryLineOptionDialog", "SymmetryLineOptionDialog", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("SymmetryLineOptionDialog", "Cancel", Q_NULLPTR));
        label_2->setText(QApplication::translate("SymmetryLineOptionDialog", "IOU threshold:", Q_NULLPTR));
        pushButtonOK->setText(QApplication::translate("SymmetryLineOptionDialog", "OK", Q_NULLPTR));
        label->setText(QApplication::translate("SymmetryLineOptionDialog", "[%]", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SymmetryLineOptionDialog: public Ui_SymmetryLineOptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYMMETRYLINEOPTIONDIALOG_H
