#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

	QString btnStyle1 =
		"QPushButton{\
                color: rgb(255, 255, 255);\
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(166,164,208), stop:0.3 rgb(171,152,230), stop:1 rgb(152,140,220));\
                border:1px;\
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px;  \
            }\
            QPushButton:pressed{    \
                color: rgb(255, 255, 255); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(240,156,121), stop:0.3 rgb(220,160,140), stop:1 rgb(230,140,120));  \
                border:1px;  \
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px; \
            }";
    QFont font("楷体", 15, 10);
    this->resize(600, 250);
    ui->label->resize(100, 40);
    ui->label_2->resize(100, 40);
	ui->label->move(80, 20);
	ui->label_2->move(80, 80);
    ui->pushButton->resize(140, 50);
    ui->pushButton_2->resize(140, 50);
    ui->lineEdit->move(220, 30);
    ui->lineEdit_2->move(220, 90);
	ui->lineEdit->resize(300, 30);
	ui->lineEdit_2->resize(300, 30);
	ui->pushButton->move(110, 150);
	ui->pushButton_2->move(350, 150);
    ui->pushButton->setStyleSheet(btnStyle1);
    ui->pushButton_2->setStyleSheet(btnStyle1);
    ui->label_2->setFont(font);
    ui->label->setFont(font);
	ui->pushButton->setFont(font);
	ui->pushButton_2->setFont(font);

    QFont font2("Times New Roman", 12, 10);
    ui->lineEdit->setFont(font2);
	ui->lineEdit->setValidator(new QRegularExpressionValidator
	(QRegularExpression("^[(\\s|\\S)+]{0,50}$"), this));
}

login::~login()
{
    delete ui;
}

//通知主窗口验证
//让主窗口告知是否关闭此窗口
void login::on_pushButton_clicked()
{
    QString name=ui->lineEdit->text();
    QString passord=ui->lineEdit_2->text();
    emit send(name,passord);
}

//注册用户
void login::on_pushButton_2_clicked()
{
    emit sendlogon();
    this->close();
}

//错误提示
void login::errorPrompt()
{
    ui->lineEdit_2->clear();
    QMessageBox::information(this, "提示", "用户名或者密码错误");
}
