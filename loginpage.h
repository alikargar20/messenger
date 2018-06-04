#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include"register.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include<QDebug>
#include<QPixmap>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QFrame>
#include"main_b.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LoginPage(QWidget *parent = 0);
    void login();
    ~LoginPage();
    void replyLog(QNetworkReply * reply);
    QString getToken();

private:

    QNetworkAccessManager *log;
    QString token;
    QNetworkRequest req;
    Ui::LoginPage *ui;
    Register *regist;
public slots:


private slots:
    void on_signup_clicked();
};



#endif // LOGINPAGE_H
