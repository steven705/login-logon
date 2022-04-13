/********************************************************************************
** Form generated from reading UI file 'showinf.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWINF_H
#define UI_SHOWINF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowInf
{
public:

    void setupUi(QWidget *ShowInf)
    {
        if (ShowInf->objectName().isEmpty())
            ShowInf->setObjectName(QString::fromUtf8("ShowInf"));
        ShowInf->resize(536, 830);

        retranslateUi(ShowInf);

        QMetaObject::connectSlotsByName(ShowInf);
    } // setupUi

    void retranslateUi(QWidget *ShowInf)
    {
        ShowInf->setWindowTitle(QCoreApplication::translate("ShowInf", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowInf: public Ui_ShowInf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWINF_H
