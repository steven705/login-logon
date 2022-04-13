#ifndef MYSQLCONNECT_H
#define MYSQLCONNECT_H

#include <QObject>
#include<QSqlQUery>
#include <QPixmap>
#include <QBuffer>
#include <QByteArray>
#include <QVariant>
#include <QVector>
#include "dbType.h" //这个存储的数据库的表
#include <QFile>

class mySqlConnect : public QObject
{
    Q_OBJECT
public:
    explicit mySqlConnect(QObject *parent = nullptr);
    //连接数据库
    bool connect();
    //登录
    bool login(tabel_userInf& myUser);
    //注册
    bool logon(tabel_userInf myUser);
    bool del(tabel_userInf myUser)
    {
		QString str = QString("update userInf set userName='%2' where userName='%1'").arg(myUser.userName).arg(myUser.userName + "f");
		bool isoK = query.exec(str);
        return isoK;
    }
    //修改用户信息
    bool changeUserInf(tabel_userInf myUser);
    //添加新的事项
    void addNewData(todolist_ui_inf& myuiInf);
    //查询当日事项
    QVector<tabel_infToDoList> searchNowDayData(QString nowUser,QString Nowday);
    //查询一项活动的所有信息
    todolist_ui_inf searchEventData(QString nowUser,QString event,QString nowDay,int EventType);
    //根据传入的信息将数据删除
    void deleteData(todolist_ui_inf& myuiInf);
    //根据传入的数据将信息进行修改
    void alterData(todolist_ui_inf& myuiInf);
    //关闭数据库连接
    void closeConnect();

private:
    //负责连接数据库
     QSqlDatabase db;
     //负责执行查询语句
     QSqlQuery query;

signals:


};

#endif // MYSQLCONNECT_H
