#ifndef LOGON_H
#define LOGON_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QDateEdit>
#include <QPaintEvent>
#include <QPainter>
#include <QFileDialog>
#include <QFont>
#include "dbType.h"
#include <QFile>
#include <QComboBox>
#include <QDate>

namespace Ui
{
class logon;
}


//用来注册和修改信息
class logon : public QWidget
{
    Q_OBJECT

public:
    explicit logon(QWidget* parent = nullptr);
    ~logon();

    void init();

    //
    void set(tabel_userInf tinf)
    {
        this->myBtn->setVisible(false);
        nowSt = 1;
        this->nameShow->setText(tinf.userName);
        this->nameShow->setReadOnly(true);
        this->passwordShow->setText(tinf.password);
        QStringList l = tinf.birthday.split("-");
        QDate date(l[0].toInt(),l[1].toInt(),l[2].toInt());
        this->petnameShow->setText(tinf.userPetName);
        this->birthdayShow->setDate(date);
        this->sexShow->setCurrentText(tinf.sex);
        this->noteShow->setText(tinf.note);
    }

protected:
    void paintEvent(QPaintEvent* event);

public slots:
    void logonToDb();
signals:
	void changedInf(tabel_userInf myUser);

signals:
	void sendlogonInf(tabel_userInf &toSend);

private:
    //当前状态 0表示注册 1表示修改
    int nowSt;
    Ui::logon *ui;
    QLabel* name;
    QLineEdit* nameShow;
    QLabel* password;
    QLineEdit* passwordShow;
    QLabel* petname;
    QLineEdit* petnameShow;
    QLabel* birthday;
    QDateEdit* birthdayShow;
    QLabel* sex;
    QComboBox* sexShow;
    QLabel* note;
    QLineEdit* noteShow;
    //头像 头像路径
    QPixmap pict;
    QString pixPath;
    //挑选头像
    QPushButton* myBtn;

    QPushButton* tryLogon;
    QPushButton* quitLogon;

    //注册用户的信息

};

#endif // LOGON_H
