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

    //登录部分
    void userLogin();

    //展示部分
    void userShowInf(QString name, QString password);

    //注册部分
    void userLogon();

private:
    Ui::Widget *ui;
    mySqlConnect* myDb;
    logon* mylogon;//注册
    login* mylogin;//登录窗口
    ShowInf* showUserInf;//显示用户信息窗口
    QPushButton* mybtn;

    //在这里存储一份账号密码作为副本
    QString todolistName;
    QString todolistPassword;
};
#endif // WIDGET_H
