#include "loginpage.h"
#include "ui_loginpage.h"




LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    url=new SetQuery();
    setGeometry(300,0,795,715);
    this->setFixedSize(795,715);
    ui->setupUi(this);
    this->setStyleSheet("background-image: url(:/model/image/5.jpeg);");
    log = new QNetworkAccessManager(this);
    connect(ui -> login , &QPushButton::clicked , this , &LoginPage :: login );
    connect(log,&QNetworkAccessManager::finished,this,&LoginPage::replyLog);
    //ui->image->setBackgroundRole();
    ui->image->setPixmap(QPixmap(":/model/image/ggg_3.png"));

}

void LoginPage::replyLog(QNetworkReply * reply){
    ui->progressBar->setValue(70);
    ui->progressBar->setValue(100);
    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    token=rep_obj["token"].toString();

    ui->textEdit->setText(rep_obj["message"].toString());
    if(rep_obj["code"].toString() == "200" ){
        Main_b *w = new Main_b(token,this);
        w->show();
        setCentralWidget(w);
        w->setGeometry(300,0,802,606);
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
    req.setUrl(url->setLoginQuery(username,password));
    log->get(req);
    ui->progressBar->setValue(20);
    ui->progressBar->setValue(50);

}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::on_signup_clicked()
{
    regist = new Register(this);
    regist -> show();
    regist->setGeometry(500,140,750,560);
    regist->setFixedSize(750,560);
}
