#ifndef MAIN_B_H
#define MAIN_B_H

#include <QMainWindow>
#include"loginpage.h"
#include "ui_loginpage.h"
#include "thread.h"
#include <QApplication>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include"register.h"
#include"sendrecievemess.h"
#include<QScrollArea>
#include<QVBoxLayout>
#include<QScrollBar>
#include<QKeyEvent>
#include <QCloseEvent>
#include<QThread>
#include "getlist.h"
#include<QMessageBox>
#include"creation.h"


namespace Ui {
class Main_b;
}

class Main_b :  public QMainWindow
{
    Q_OBJECT

public:
    explicit Main_b( QString token , QString user , QString pass , QWidget *parent = 0);
    ~Main_b();
    void Reply(QNetworkReply * rep);
    void closeEvent(QCloseEvent * e);
    void keyPressEvent(QKeyEvent *event);
    void reply_item_clicked(QListWidgetItem *item);
    void remove_item_in_layout(QLayout *lay);
    void set_mess_groupCre(QNetworkReply * r);
    void set_mess_channelCre(QNetworkReply * r);
    void reply_join(QNetworkReply * r);

private:
    Ui::Main_b *ui;
    QString last_date;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *manage;
    QNetworkAccessManager *channel_create_net;
    QNetworkAccessManager *group_create_net;
    Thread *mThread;
    GetList *list_thread;
    QNetworkAccessManager *cha_join;
    QNetworkAccessManager *gp_join;
    QNetworkRequest  req;
    QNetworkRequest request;
    QString token;
    SetQuery * url;
    QString username;
    QString password;
    QString str_id;
    QWidget *central_scroll_area;
    QVBoxLayout *layout_scroll_area;
    QScrollBar *scrollbar_in_scrollarea;


    



public slots:
    void search_reply(QNetworkReply *repl);
    void showlist(QString str);
    void id_set(QString s);
    void makeLabel(QString txt, QString src);


private slots:

    void on_pushButton_clicked();
    void on_searchBut_clicked();
    void on_send_clicked();


signals:
    void textLabelChanged(QString );
};

#endif // MAIN_B_H
