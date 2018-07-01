#include "main_b.h"
#include "getlist.h"
#include "ui_main_b.h"
#include"loginpage.h"
#include "ui_loginpage.h"
#include"thread.h"

Main_b::Main_b(QString token, QString user , QString pass ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main_b)
{

    this->token=token;
    this->username = user;
    this->password = pass;
    ui->setupUi(this);
    mThread = new Thread(this);
    hThread = new Thread(this);
    list_thread=new GetList(token,this);
    manager = new QNetworkAccessManager(this);
    manage = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&Main_b::Reply);
    connect(manage,&QNetworkAccessManager::finished,this,&Main_b::search_reply);
    connect(mThread, SIGNAL(thread_rec()),
                this, SLOT(thread_rec()));
    connect(list_thread,SIGNAL(get_finished(QString)),this,SLOT(showlist(QString)));



    url = new SetQuery;
    url->setToken(token);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    central_scroll_area = new QWidget;
    ui->scrollArea->setWidget(central_scroll_area);
    ui->scrollArea->setWidgetResizable(true);
    layout_scroll_area = new QVBoxLayout(central_scroll_area);
    ui->listWidget->setStyleSheet("background-image: url(:/model/image/label2.jpg);");
    layout_scroll_area->setAlignment(central_scroll_area,Qt::AlignBottom);
    //layout_scroll_area->setStretch(0,20);
    scrollbar_in_scrollarea  =new QScrollBar(Qt::Vertical);
    scrollbar_in_scrollarea=ui->scrollArea->verticalScrollBar();
    scrollbar_in_scrollarea->setSliderDown(true);
    central_scroll_area->setStyleSheet("background-image: url(:/model/image/5.jpg);");





}

Main_b::~Main_b()
{
    mThread->Stop = true;
    hThread->Stop = true;
    delete list_thread;
    delete ui;
}




void Main_b::on_searchBut_clicked()
{
    str_id = ui->search->text();
    req.setUrl(url->setGetUserChatsQuery(str_id));
    manage->get(req);
    mThread->start();
    hThread->start();
}

void Main_b::thread_rec(){

    req.setUrl(url->setGetUserChatsQuery(str_id));
    manage->get(req);


}


void Main_b::search_reply(QNetworkReply  *repl){

    QString rep_str = repl->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
    QString mess = jobj["message"].toString();
    QStringList pieces = mess.split( "-" );
    QString num_messages = pieces.value( pieces.length() - 2 );
     if(jobj["code"].toString() == "200"){

        ui->search->setText("");
        ui->label->setText(str_id);

    }
     for(int cnt = 0 ; cnt < num_messages.toInt() ; cnt++ ){
        QString block_str = "block ";
        block_str += QString::number(cnt);
        QJsonObject j = jobj.value(block_str).toObject();
        if(j.value("body").toString() != ""){
            if(j.value("body").toString().length()>62){
                for(int i=1;i<=j.value("body").toString().length()/62;i++)
                j.value("body").toString().insert(i*62,"\n");
            }

        QLabel *label2 = new QLabel(j.value("body").toString());
        label2->setWordWrap(true);
        label2->setLineWidth(535);
        if(j.value("src") == username){
            label2->setAlignment(Qt::AlignRight);
        }
        else{
            label2->setAlignment(Qt::AlignLeft);
        }
        layout_scroll_area->addWidget(label2,0,Qt::AlignBottom);
        scrollbar_in_scrollarea->setSliderPosition(scrollbar_in_scrollarea->maximumHeight());
        }





     }




}

void Main_b::on_logout_clicked()
{
    req.setUrl( url -> setLogOutQuery(username ,password));
    manager ->get(req);


}


void Main_b ::Reply(QNetworkReply * rep){
    delete list_thread;
    QString str = rep ->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(str.toUtf8());
    QJsonObject obj=jdoc.object();
    if(obj["code"].toString() == "200"){

        LoginPage *log = new LoginPage;
        setCentralWidget(log);
        log->setGeometry(300,40,795,715);
        log->show();


    }



}

void Main_b::closeEvent(QCloseEvent *e)
{

     e->accept();


}


void Main_b::on_send_clicked()
{
    QString str_mess = ui->typekon->text();
    SendRecieveMess send_obj;
    if(str_mess != ""){
    send_obj.send_user(str_id , str_mess , token);
    ui->typekon->setText("");
    if(str_mess.length()>62){
        for(int i=1;i<=str_mess.length()/62;i++){
            str_mess.insert(i*62,"\n");
        }
    }
    QLabel *label1 = new QLabel(str_mess);
   // label1->setPixmap(QPixmap(":/model/image/label1.png"));
    label1->setAlignment(Qt::AlignRight);
    label1->setWordWrap(true);
    layout_scroll_area->addWidget(label1,0,Qt::AlignBottom);
    scrollbar_in_scrollarea->setSliderPosition(scrollbar_in_scrollarea->maximumHeight());
    }
}




void Main_b::keyPressEvent (QKeyEvent *event)
{
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
        on_send_clicked();
    }
}

void Main_b::showlist(QString str)
{

    ui->listWidget->addItem(str);

}

