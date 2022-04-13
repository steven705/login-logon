#include "logon.h"
#include "ui_logon.h"

logon::logon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logon)
{
    ui->setupUi(this);
    init();
}
void logon::init()
{
    nowSt = 0;

    this->resize(600,1100);
    name=new QLabel(this);
    nameShow=new QLineEdit(this);
    password=new QLabel(this);
    passwordShow=new QLineEdit(this);
    petname=new QLabel(this);
    petnameShow=new QLineEdit(this);
    birthday=new QLabel(this);
    birthdayShow=new QDateEdit(this);
    sex=new QLabel(this);
    sexShow=new QComboBox(this);
    sexShow->addItem("男");
    sexShow->addItem("女");
    note=new QLabel(this);
    noteShow=new QLineEdit(this);
    myBtn=new QPushButton(this);


    QFont font("华文行楷", 17, 15);
    name->setText("用户名");
    name->move(100,450);
    name->setFont(font);
    name->resize(100,50);

    password->setText("密码");
    password->move(100,550);
    password->setFont(font);
    password->resize(100,50);

    petname->setText("姓名");
    petname->move(100,650);
    petname->setFont(font);
    petname->resize(100,50);

    birthday->setText("生日");
    birthday->move(100,750);
    birthday->setFont(font);
    birthday->resize(100,50);
    sex->setText("性别");
    sex->move(100,850);
    sex->setFont(font);
    sex->resize(100,50);
    note->setText("个性签");
    note->move(100,950);

    note->setFont(font);
    note->resize(100,50);


    nameShow->move(250,450);
    nameShow->setFont(font);
    nameShow->resize(300,40);

    passwordShow->move(250,550);
    passwordShow->setFont(font);
    passwordShow->resize(300,40);

    petnameShow->move(250,650);
    petnameShow->setFont(font);
    petnameShow->resize(300,40);

    birthdayShow->move(250,750);
    birthdayShow->setFont(font);
    birthdayShow->resize(300,40);
    birthdayShow->setDisplayFormat("yyyy-MM-dd");


    sexShow->move(250,850);
    sexShow->setFont(font);
    sexShow->resize(300,40);

    noteShow->move(250,950);
    noteShow->setFont(font);
    noteShow->resize(300,40);



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
	tryLogon=new QPushButton(this);
	quitLogon = new QPushButton(this);
    tryLogon->setText("确认");
	quitLogon->setText("退出");
    tryLogon->move(250, 1000);
    quitLogon->move(450, 1000);
    tryLogon->resize(150, 50);
    quitLogon->resize(150, 50);
    tryLogon->setStyleSheet(btnStyle1);
    quitLogon->setStyleSheet(btnStyle1);

	connect(tryLogon, &QPushButton::clicked, this, &logon::logonToDb);
    connect(quitLogon, &QPushButton::clicked, [=]() {
        this->close();
        });

    //换头像

	QString btnStyle2 =
		"QPushButton{\
                color: rgb(255, 255, 255);\
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(166,164,208), stop:0.3 rgb(171,152,230), stop:1 rgb(152,140,220));\
                border:1px;\
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px;  \
            }\
            QPushButton:hover{\
                color: rgb(255, 255, 255); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(130,120,226), stop:0.3 rgb(120,130,230), stop:1 rgb(125,140,226));\
                border:1px;  \
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px; \
            }\
            QPushButton:pressed{    \
                color: rgb(255, 255, 255); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(240,156,121), stop:0.3 rgb(220,160,140), stop:1 rgb(230,140,120));  \
                border:1px;  \
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px; \
            }";

	myBtn->setText("更改头像");
	myBtn->resize(100, 55);
	myBtn->move(440, 300);
	myBtn->setStyleSheet(btnStyle2);
    //QFont font("楷体", 10, 15);
    //myBtn->setFont(font);

    connect(myBtn, &QPushButton::clicked, [=]() {
		QString file_name = QFileDialog::getOpenFileName(this,
			QString("open Iamge"),
			".",
			QString("image files(*.jpg *.png *.bmp *.jfif)"));
		if (file_name != "")
		{
			pixPath = file_name;
			this->update();
            pict.load(pixPath);
			//告知主窗口更新头像
		}
        });
    pixPath = "";

}
void logon::paintEvent(QPaintEvent* event)
{
    if (pixPath!="")
    {
		QPainter painter(this);
		painter.setRenderHints(QPainter::Antialiasing, true);

		QPainterPath path;
		path.addEllipse(QPoint(300, 200), 150, 150);
		painter.setClipPath(path);

		painter.drawPixmap(QRect(150, 50, 300, 300), pict);
    }

}
void logon::logonToDb()
{
    tabel_userInf toSend;
    toSend.userName = nameShow->text();
    toSend.password = passwordShow->text();
    toSend.userPetName = petnameShow->text();
    toSend.birthday = birthdayShow->text();
    toSend.sex = sexShow->currentText();
    QStringList list = pixPath.split('.');
    toSend.suffix = list[list.size() - 1];
    toSend.pixmap = pict;
    toSend.path = pixPath;
    toSend.note = noteShow->text();
    if (nowSt==0)
    {
        emit sendlogonInf(toSend);
    }
    else
    {
        emit changedInf(toSend);
    }


}
logon::~logon()
{
    delete ui;
}
