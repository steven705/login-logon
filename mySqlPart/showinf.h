#ifndef SHOWINF_H
#define SHOWINF_H

#include <QWidget>
#include<QPaintEvent>
#include<QPixmap>
#include<qpainter.h>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QFont>
#include<QFileDialog>
#include <QByteArray>
#include "dbType.h"
#include <QComboBox>

//负责显示信息

namespace Ui {
class ShowInf;
}

class ShowInf : public QWidget
{
    Q_OBJECT

public:
    explicit ShowInf(QWidget *parent = nullptr);
    ~ShowInf();

     void setPath(QString path)
     {
         pixPath=path;
         this->update();
     }

     //设置初始信息
     void set(QString name,QString bir,QString sex,QString note,QString suffix,QByteArray br)
     {
         this->nameShow->setText(name);
         this->birthdayShow->setText(bir);
         this->sexShow->setText(sex);
         this->noteShow->setText(note);
         QString suff;
         this->pict.loadFromData(br, suff.toLatin1());
         pixPath = name + "pict." + suffix;
         this->update();
     }
     //更换头像
     void changePic();
     //切换用户
     void changeUser();
     //修改资料
     void changeData();
protected:
    void paintEvent(QPaintEvent *event);

signals:
    void changedPic(tabel_userInf myUser);
signals:
    void goingChangeInf();
signals:
    void goingChangeUser();

private:
    Ui::ShowInf *ui;
    QLabel* name;
    QLabel* nameShow;
    QLabel* birthday;
    QLabel* birthdayShow;
    QLabel* sex;
    QLabel* sexShow;
    QLabel* note;
    QLabel* noteShow;
    QPixmap pict;
    QString pixPath;
    QPushButton* myBtn;

    QPushButton* switchUser;
    QPushButton* updateUser;
};

#endif // SHOWINF_H
