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

//��¼����
void Widget::userLogin()
{
	mylogin = new login;
	mylogin->show();

	//��ʾ��Ϣ
	connect(mylogin, &login::send, [&](QString name, QString password)
		{
			userShowInf(name, password);
		});

	//ע�����û�
	connect(mylogin, &login::sendlogon, this, &Widget::userLogon);

}

//չʾ����
void Widget::userShowInf(QString name, QString password)
{
	//�����ݿ���һ����֤
	//���һ���û���Ϣ
	tabel_userInf myUser;
	myUser.userName = name;
	myUser.password = password;
	bool isOk = myDb->login(myUser);
	if (isOk)
	{
		todolistName = name;
		todolistPassword = password;

		mylogin->close();
		//�����µĴ�����ʾ
		showUserInf = new ShowInf();
		showUserInf->set(myUser.userPetName, myUser.birthday, myUser.sex, myUser.note, myUser.suffix, myUser.byteArray);
		//�޸�ͷ��
		connect(showUserInf, &ShowInf::changedPic, [&](tabel_userInf myUser)
			{
				//��������ָ���û�������
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
		//�޸��û�
		connect(showUserInf, &ShowInf::goingChangeUser, [=]()
			{
				mybtn->clicked(true);
			});
		//�޸�����
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
		//��ʾ����������
		mylogin->errorPrompt();
	}
}

//ע�Ჿ��
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
				QMessageBox::information(this, "��ʾ", "�˻�������");
			}
		});
	
}

Widget::~Widget()
{
    delete ui;
}

