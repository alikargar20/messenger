#include "main_b.h"
#include "ui_main_b.h"


Main_b::Main_b(QString token,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main_b)
{
    this->token=token;
    qDebug()<<this->token;
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
  //  connect(manager,&QNetworkAccessManager::finished,this,&intro::reg_Reply);




}

Main_b::~Main_b()
{
    delete ui;
}

void Main_b::getuserlist()
{
    QUrl url("http://api.softserver.org:1104/getuserlist");
    QUrlQuery query;
    query.addQueryItem("token",token);
    url.setQuery(query);
    req.setUrl(url);
    manager->get(req);
}
