#ifndef MAIN_B_H
#define MAIN_B_H

#include <QMainWindow>
#include"loginpage.h"
#include "ui_loginpage.h"

#include "loginpage.h"
#include <QApplication>
#include<QPainter>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include"register.h"
#include"sendrecievemess.h"
#include<QScrollArea>
#include<QVBoxLayout>
#include<QHBoxLayout>



namespace Ui {
class Main_b;
}

class Main_b : public QMainWindow
{
    Q_OBJECT

public:
    explicit Main_b( QString token , QString user , QString pass , QWidget *parent = 0);
    ~Main_b();
    void Reply(QNetworkReply * rep);
    friend class GetList;




protected:
    QVector<QLabel*>Labels;
    Ui::Main_b *ui;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *manage;
    QNetworkRequest  req;
    QString token;
    SetQuery * url;
    QNetworkReply * rep;
    QString username;
    QString password;
    QString str_id;
    QString sum_str = "";
private slots:

    void on_searchBut_reply(QNetworkReply * repl);
    void on_searchBut_clicked();
    void on_logout_clicked();
    void on_send_clicked();
};

#endif // MAIN_B_H
