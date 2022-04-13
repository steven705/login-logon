#include "mysqlconnect.h"
#include <QMessageBox>

mySqlConnect::mySqlConnect(QObject *parent) : QObject(parent)
{

}
//连接数据库
bool mySqlConnect::connect()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("47.98.181.12");
    db.setPort(3306);
    db.setDatabaseName("todolist");
    db.setUserName("user_todolist");
    db.setPassword("15377619612Lzx@");
    if (db.open())
    {
        query=QSqlQuery(db);
        return true;
    }
    else
    {
        return false;
    }
}
 //用户验证
bool mySqlConnect::login(tabel_userInf& myUser)
{
	QString str = QString("select * from userInf where userName='%1' and userPassword= '%2'")
		.arg(myUser.userName).arg(myUser.password);
	query.exec(str);
	//只要有结果就查询成功了
	//同时将信息复制过来
	while (query.next())
	{
		//将信息复制过来
		myUser.userPetName= query.value(2).toString();
		myUser.birthday = query.value(3).toString();
		myUser.sex = query.value(4).toString();
		myUser.note = query.value(5).toString();
		myUser.suffix= query.value(6).toString();
		myUser.byteArray = query.value(7).toByteArray();
		return true;
	}
	return false;
}
//用户注册
bool mySqlConnect::logon(tabel_userInf myUser)
{
    //先看一下这个用户名是不是存在的
	//存在的话
	QString str = QString("select * from userInf where userName='%1'").arg(myUser.userName);
	query.exec(str);
	//只要有结果说明用户名被用了
	while (query.next())
	{
        return false;
	}

	//将照片以二进制流的方式存到数据库
	QByteArray data;
	QString path =myUser.path;
	QFile* file = new QFile(path); //fileName为二进制数据文件名  
	file->open(QIODevice::ReadOnly);
	data = file->readAll();
	file->close();
	QVariant var(data);
	

	QString strQSL = QString("insert into  userInf values('%1','%2','%3','%4','%5','%6','%7',?)")
        .arg(myUser.userName).arg(myUser.password).arg(myUser.userPetName).
		arg(myUser.birthday).arg(myUser.sex).arg(myUser.note).arg(myUser.suffix);
	query.prepare(strQSL);
	query.addBindValue(var);
	return query.exec();
}
//修改用户信息
bool mySqlConnect::changeUserInf(tabel_userInf myUser)
{

	//将照片以二进制流的方式存到数据库
	QByteArray data;
	QString path = myUser.path;
	QFile* file = new QFile(path); //fileName为二进制数据文件名  
	file->open(QIODevice::ReadOnly);
	data = file->readAll();
	file->close();
	QVariant var(data);


	QString strQSL = QString("insert into userInf values('%1','%2','%3','%4','%5','%6','%7',?)")
		.arg(myUser.userName).arg(myUser.password).arg(myUser.userPetName).
		arg(myUser.birthday).arg(myUser.sex).arg(myUser.note).arg(myUser.suffix);
	query.prepare(strQSL);
	query.addBindValue(var);
	return query.exec();
	
}


//1
//这里需要注意 原来的内张表已经被删除了
//新的表的名称叫做 infToDoList 数据结构看dbType.h或者数据库
//新的表的只有一个日期 没有了开始日期和结束日期 将其合并在了一起
//这里的意思就是比如说从2022年3月21日2022年到4月20日 
//那么需要分别插入 3.21 3.22  3.23 3.24 3.25 ..... 4.20
//这里实现可以利用QDate （可以实现日期加减比较)
//todolist_ui_inf& myuiInf 是ui界面传入的(显示详细信息的部分) 数据类型参照dbType.h 里面有解释
void mySqlConnect::addNewData(todolist_ui_inf& myuiInf)
{
    
}

//2
//查询一项活动的所有信息 数据的返回值是 todolist_ui_inf 
//这里和上一个函数对应 就是说查询到了 这个在3.22，3.23,3.24,3.25有这一项活动
//那么开始日期就是 2022-3-22 结束日期就是2022年3.25
//传入的信息分别： 当前用户名 事件名称 当前日期 事件类型1 2 3之类的
//todolist_ui_inf 这个数据结构是界面使用的包括开始日期和结束日期
todolist_ui_inf mySqlConnect::searchEventData(QString nowUser, QString event, QString nowDay, int EventType)
{
	todolist_ui_inf ret;
	return ret;
}
//3
//根据传入的信息将数据从数据库删除  infToDoList 
//todolist_ui_inf& myuiInf 是ui界面传入的(显示详细信息的部分)
void mySqlConnect::deleteData(todolist_ui_inf& myuiInf)
{
	return;
}
//4
//根据传入的信息将数据从数据库修改  infToDoList 
//todolist_ui_inf& myuiInf 是ui界面传入的(显示详细信息的部分)
void mySqlConnect::alterData(todolist_ui_inf& myuiInf)
{
	return;
}

//查询当日事项的所有信息返回
QVector<tabel_infToDoList> mySqlConnect::searchNowDayData(QString nowUser,QString Nowday)
{
	QString str = QString("select * from infToDoList where userName='%1' and DT= '%2'").arg(nowUser).arg(Nowday);
	query.exec(str);
	//tabel_infToDoList是数据库的表
	QVector<tabel_infToDoList> ret;
	while (query.next())
	{
		tabel_infToDoList tmp;
		tmp.userName = query.value(0).toString();
		tmp.DT = query.value(1).toInt();
		tmp.BeginT = query.value(2).toString();
		tmp.EndT = query.value(3).toString();
		tmp.EventTitle = query.value(4).toString();
		tmp.EventType = query.value(5).toInt();
		tmp.Note = query.value(6).toString();
		ret.push_back(tmp);
	}
	return ret;
}


//关闭数据库连接
void mySqlConnect::closeConnect()
{
    db.close();
}
