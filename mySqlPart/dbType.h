#ifndef DBTYPE_H
#define DBTYPE_H
#include<QString>
#include<QPixmap>
#include <QByteArray>
using namespace std;



//这个是从ui获得的信息
//就是用户输入的信息 用户输入了开始日期和结束日期 我们就要对其拆分 一天一天存储
struct todolist_ui_inf
{
    QString userName;
    QString BeginDT;
    QString EndDT;
    QString BeginT;
    QString EndT;
    int EventType;
    QString EventTitle;
    QString Note;

};

//这一部分保存的是数据库的表的数据类型
//数据表的命名为 infToDoList
struct tabel_infToDoList
{
    QString userName;
    QString DT;//主要区别就是把开始时间和结束时间合在了一起 然后插入多条信息
    QString BeginT;
    QString EndT;
    int EventType;
    QString EventTitle;
    QString Note;

};


//这个是用户信息表
//数据库表的命名为 userInf
struct tabel_userInf
{
    QString userName;
    QString password;
    QString userPetName;//昵称
    QString birthday;
    QString sex;
    QString note;
    QString path;//头像路径
    QString suffix;//头像图片的后缀
    QPixmap pixmap;//这个存储的是用户头像
    QByteArray byteArray;//用于将图片传出来

};

#endif // DBTYPE_H
