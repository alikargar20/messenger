#include "loginpage.h"
#include "ui_login.h"
#include "main_b.h"
#include<QPixmap>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include"register.h"
#include<QDebug>
#include<QFrame>
LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this ->setStyleSheet("background-image: url(/home/siavash/Desktop/5.jpeg);");
    log = new QNetworkAccessManager(this);
    connect(ui -> login , &QPushButton::clicked , this , &LoginPage :: login );

    connect(log,&QNetworkAccessManager::finished,this,&LoginPage::replyLog);


}

void LoginPage::replyLog(QNetworkReply * reply){

    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    token=rep_obj["token"].toString();

    ui->textEdit->setText(rep_obj["message"].toString());
    if(rep_obj["code"].toString() == "200" ){
        Main_b *w = new Main_b(token,this);
        w->show();
        setCentralWidget(w);
        this->hide();


    }



}

QString LoginPage::getToken()
{
    return token;
}



void LoginPage::login(){

    QString  username = ui -> user ->text();
    QString  password = ui -> pass ->text();
    QUrl url("http://api.softserver.org:1104/login");
    QUrlQuery query;
    query.addQueryItem("username" , username);
    query.addQueryItem("password" , password);
    url.setQuery(query);
    req.setUrl(url);
    log->get(req);


}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::on_signup_clicked()
{
    regist = new Register(this);
    regist -> show();

}
