/********************************************************************************
** Form generated from reading UI file 'logon.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGON_H
#define UI_LOGON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_logon
{
public:

    void setupUi(QWidget *logon)
    {
        if (logon->objectName().isEmpty())
            logon->setObjectName(QString::fromUtf8("logon"));
        logon->resize(400, 300);

        retranslateUi(logon);

        QMetaObject::connectSlotsByName(logon);
    } // setupUi

    void retranslateUi(QWidget *logon)
    {
        logon->setWindowTitle(QCoreApplication::translate("logon", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class logon: public Ui_logon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGON_H
