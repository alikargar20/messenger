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
    manage = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&Main_b::Reply);
    connect(manage,&QNetworkAccessManager::finished,this,&Main_b::on_searchBut_reply);

    url = new SetQuery;
    url->setToken(token);
}

Main_b::~Main_b()
{
    delete ui;
}





void Main_b::on_searchBut_clicked()
{
    str_id = ui->search->text();
    req.setUrl(url->setGetUserChatsQuery(str_id));
    manage->get(req);




}


void Main_b::on_searchBut_reply(QNetworkReply * repl){
    QString rep_str = repl->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
    qDebug()<<jobj["message"].toString();
    if(jobj["code"].toString() == "200"){
        ui->search->setText("");
        ui->label->setText(str_id);

    }


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



void Main_b::on_send_clicked()
{   int cnt = 50 , cnt2 = 50;
    QString str_mess = ui->typekon->text();
    //ui->label_2->setText(str_mess);
    SendRecieveMess send_obj;
    send_obj.send_user(str_id , str_mess , token);
    ui->typekon->setText("");
    //////////////////////
    QWidget *central=new QWidget;
    QVBoxLayout *box = new QVBoxLayout(ui->scrollArea);
    ui->scrollArea->setWidget(central);
    ui->scrollArea->setWidgetResizable(true);

    //for(int cnt = 0 ; cnt < 50 ; cnt++){

        QWidget *wid = new QWidget;
        QHBoxLayout *lay = new QHBoxLayout(wid);
        QLabel *lab1 = new QLabel("sadf");
        QLabel *lab2 = new QLabel("sadfsfdhsh");
        lay->addWidget(lab1);
        lay->addWidget(lab2);
        box->addWidget(wid);

    //}
}

