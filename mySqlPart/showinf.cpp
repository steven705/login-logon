#include "showinf.h"
#include "ui_showinf.h"

ShowInf::ShowInf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowInf)
{
    ui->setupUi(this);
    this->setFixedSize(600,900);
    name=new QLabel(this);
    nameShow=new QLabel(this);
    birthday=new QLabel(this);
    birthdayShow=new QLabel(this);
    sex=new QLabel(this);
    sexShow=new QLabel(this);
    note=new QLabel(this);
    noteShow=new QLabel(this);
    myBtn=new QPushButton(this);


    QFont font("华文行楷", 17, 15);
    name->setText("姓名");
    name->move(100,450);
    name->setFont(font);
    name->resize(100,50);
    birthday->setText("生日");
    birthday->move(100,550);
    birthday->setFont(font);
    birthday->resize(100,50);
    sex->setText("性别");
    sex->move(100,650);
    sex->setFont(font);
    sex->resize(100,50);
    note->setText("个性签");
    note->move(100,750);
    note->setFont(font);
    note->resize(100,50);


    nameShow->move(250,450);
    nameShow->setFont(font);
    nameShow->resize(300,40);
    birthdayShow->move(250,550);
    birthdayShow->setFont(font);
    birthdayShow->resize(300,40);
    sexShow->move(250,650);
    sexShow->setFont(font);
    sexShow->resize(300,40);
    noteShow->move(250,750);
    noteShow->setFont(font);
    noteShow->resize(300,40);


    QFont font2("楷体", 10, 15);

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

    switchUser=new QPushButton(this);
    updateUser=new QPushButton(this);

    switchUser->setText("切换用户");
    updateUser->setText("更新信息");
    switchUser->move(250,830);
    updateUser->move(450,830);
    switchUser->resize(150,50);
    updateUser->resize(150,50);
    switchUser->setStyleSheet(btnStyle1);
    updateUser->setStyleSheet(btnStyle1);
    switchUser->setFont(font2);
    updateUser->setFont(font2);



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
    myBtn->resize(100,55);
    myBtn->move(440,300);
    myBtn->setStyleSheet(btnStyle2);
    myBtn->setFont(font2);
    pixPath="";

    //关联按钮
    connect(myBtn,&QPushButton::clicked,this,&ShowInf::changePic);
    connect(switchUser,&QPushButton::clicked,this,&ShowInf::changeUser);
    connect(updateUser,&QPushButton::clicked,this,&ShowInf::changeData);

    //setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #8386ec,stop:0.5 #474ac1 ,stop:1 #22259f)");

}
void ShowInf::paintEvent(QPaintEvent *event)
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
//更换头像
void ShowInf::changePic()
{
	QString file_name = QFileDialog::getOpenFileName(this,
		QString("open Iamge"),
		".",
		QString("image files(*.jpg *.png *.bmp *.jfif)"));
    if (file_name!="")
    {
        pixPath = file_name;
     
        tabel_userInf myUser;
        myUser.userPetName = this->nameShow->text();
        myUser.birthday = this->birthdayShow->text();
        myUser.sex = sexShow->text();
        myUser.path = file_name;
        emit changedPic(myUser);
        pict.load(file_name);
        this->update();
    }
}
//切换用户
void ShowInf::changeUser()
{
    emit goingChangeUser();
    close();
}
//修改资料
void ShowInf::changeData()
{
    emit goingChangeInf();
}
ShowInf::~ShowInf()
{
    delete ui;
}
