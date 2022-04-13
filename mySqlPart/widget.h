#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"mysqlconnect.h"
#include"login.h"
#include<QPushButton>
#include"showinf.h"
#include"logon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //��¼����
    void userLogin();

    //չʾ����
    void userShowInf(QString name, QString password);

    //ע�Ჿ��
    void userLogon();

private:
    Ui::Widget *ui;
    mySqlConnect* myDb;
    logon* mylogon;//ע��
    login* mylogin;//��¼����
    ShowInf* showUserInf;//��ʾ�û���Ϣ����
    QPushButton* mybtn;

    //������洢һ���˺�������Ϊ����
    QString todolistName;
    QString todolistPassword;
};
#endif // WIDGET_H
