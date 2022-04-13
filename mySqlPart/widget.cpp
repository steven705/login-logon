#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    myDb=new mySqlConnect(this);
    if(myDb->connect())
    {
         QMessageBox::information(this, "infor", "success");
    }
    else
    {
         QMessageBox::information(this, "infor", "fail");
           //qDebug()<<"error open database because"<<db.lastError().text();
    }
    mybtn=new QPushButton(this);
    connect(mybtn, &QPushButton::clicked, this,&Widget::userLogin);
}

//登录部分
void Widget::userLogin()
{
	mylogin = new login;
	mylogin->show();

	//显示信息
	connect(mylogin, &login::send, [&](QString name, QString password)
		{
			userShowInf(name, password);
		});

	//注册新用户
	connect(mylogin, &login::sendlogon, this, &Widget::userLogon);

}

//展示部分
void Widget::userShowInf(QString name, QString password)
{
	//用数据库做一下验证
	//获得一下用户信息
	tabel_userInf myUser;
	myUser.userName = name;
	myUser.password = password;
	bool isOk = myDb->login(myUser);
	if (isOk)
	{
		todolistName = name;
		todolistPassword = password;

		mylogin->close();
		//调出新的窗口显示
		showUserInf = new ShowInf();
		showUserInf->set(myUser.userPetName, myUser.birthday, myUser.sex, myUser.note, myUser.suffix, myUser.byteArray);
		//修改头像
		connect(showUserInf, &ShowInf::changedPic, [&](tabel_userInf myUser)
			{
				//在这里需指定用户和密码
				myUser.userName = todolistName;
				myUser.password = todolistPassword;
				bool is = myDb->del(myUser);
				if (is)
				{
					QMessageBox::information(this, "infor", "success");
				}
				else
				{
					QMessageBox::information(this, "infor", "fail");
				}
				bool isOk= myDb->changeUserInf(myUser);
				if (isOk)
				{
					QMessageBox::information(this, "infor", "success");
				}
				else
				{
					QMessageBox::information(this, "infor", "fail");
				}
			});
		//修改用户
		connect(showUserInf, &ShowInf::goingChangeUser, [=]()
			{
				mybtn->clicked(true);
			});
		//修改资料
		connect(showUserInf, &ShowInf::goingChangeInf, [=]()
			{
				mylogon = new logon;
				mylogon->set(myUser);
				mylogon->show();
				connect(mylogon, &logon::changedInf, [&](tabel_userInf myUser)
					{
						bool st = myDb->logon(myUser);
						if (st)
						{
							mylogon->close();
							mybtn->clicked(true);
						}
						else
						{
							bool is = myDb->del(myUser);
							if (is)
							{
								QMessageBox::information(this, "ask", "Are you sure modify it?");
							}
							else
							{
								QMessageBox::information(this, "infor", "fail");
							}
							bool isOk = myDb->changeUserInf(myUser);
							if (isOk)
							{
								QMessageBox::information(this, "infor", "success");
							}
							else
							{
								QMessageBox::information(this, "infor", "fail");
							}
						}
					});
			});
		showUserInf->show();
	}
	else
	{
		//提示其重新输入
		mylogin->errorPrompt();
	}
}

//注册部分
void Widget::userLogon()
{
	mylogon = new logon;
	mylogon->show();
	mylogin->close();
	connect(mylogon, &logon::sendlogonInf, [&](tabel_userInf userInfToLogon)
		{
			bool st = myDb->logon(userInfToLogon);
			if (st)
			{
				mylogon->close();
				mybtn->clicked(true);
			}
			else
			{
				QMessageBox::information(this, "提示", "账户重命名");
			}
		});
	
}

Widget::~Widget()
{
    delete ui;
}

