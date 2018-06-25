#ifndef MAIN_B_H
#define MAIN_B_H

#include <QMainWindow>
#include"loginpage.h"
#include "ui_loginpage.h"

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




protected:
    Ui::Main_b *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest  req;
    QString token;
    SetQuery * url;
    QNetworkReply * rep;
    QString username;
    QString password;
private slots:


    void on_searchBut_clicked();
    void on_logout_clicked();
};

#endif // MAIN_B_H
