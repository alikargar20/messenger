#include "main_b.h"
#include "getlist.h"
#include "ui_main_b.h"
#include"loginpage.h"
#include "ui_loginpage.h"

Main_b::Main_b(QString token, QString user , QString pass ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main_b)
{
    this->token=token;
    this->username = user;
    this->password = pass;
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&Main_b::Reply);
    url = new SetQuery;

}

Main_b::~Main_b()
{
    delete ui;
}





void Main_b::on_searchBut_clicked()
{
    QString str = ui->search->text();
    req.setUrl(url->setGetUserChatsQuery(str));
    manager->get(req);
    manager->finished(rep);
    QString rep_str = rep->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
    qDebug()<< jobj["message"].toString();



}

void Main_b::on_logout_clicked()
{
    req.setUrl( url -> setLogOutQuery(username ,password));
    manager ->get(req);


}


void Main_b ::Reply(QNetworkReply * rep){

    QString str = rep ->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(str.toUtf8());
    QJsonObject obj=jdoc.object();
    if(obj["code"].toString() == "200"){
        LoginPage *log = new LoginPage;
        setCentralWidget(log);
        log->show();

        //this -> close();
    }


}
