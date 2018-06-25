#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui2(new Ui::Register)
{
    url=new SetQuery();
    ui2->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui2->signup , &QPushButton::clicked , this , &Register :: reg);
    connect(manager,&QNetworkAccessManager::finished,this,&Register::reply);

}



void Register :: reg(){

    QString nUser = ui2 -> nUser ->text();
    QString nPass = ui2 ->nPass ->text();
    QString nPro = ui2 ->nPro ->text();
    QString fName = ui2 ->Fname->text();
    QString lName = ui2->Lname->text();


    req.setUrl(url->setSignUpQuery(nUser,nPass,fName,lName));
    manager->get(req);

}


void Register ::reply(QNetworkReply *reply){

    QString rep_str = reply->readAll();

    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj=jdoc.object();

    //jobj["token"].toString();
    //jobj["id"].toString();
    if( jobj["code"].toString() == "200"){

        ui2->textEdit->setText( "    You Signed Up Successfully!!");
    }

    else{

        ui2->textEdit->setText(jobj["message"].toString());
    }
}

Register::~Register()
{
    delete ui2;
}

void Register::on_login_clicked()
{
    this->close();
}
