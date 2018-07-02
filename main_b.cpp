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
    channel_create_net = new QNetworkAccessManager(this);
    group_create_net = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&Main_b::Reply);
    connect(manage,&QNetworkAccessManager::finished,this,&Main_b::search_reply);
    connect(mThread, SIGNAL(thread_rec()),this, SLOT(thread_rec()));
    connect(list_thread,SIGNAL(get_finished(QString)),this,SLOT(showlist(QString)));
    connect(mThread, SIGNAL(thread_rec()),this, SLOT(thread_rec()));
    connect(hThread, SIGNAL(search_reply(QNetworkReply  *repl)),this, SLOT(search_reply(QNetworkReply  *repl)));
    connect(group_create_net , &QNetworkAccessManager::finished , this , &Main_b::set_mess_groupCre);
    connect(channel_create_net , &QNetworkAccessManager::finished , this , &Main_b::set_mess_channelCre);
    connect(ui->listWidget,&QListWidget::itemClicked,this,&Main_b::reply_item_clicked);


    url = new SetQuery;
    url->setToken(token);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    central_scroll_area = new QWidget;
    ui->scrollArea->setWidget(central_scroll_area);
    ui->scrollArea->setWidgetResizable(true);
    layout_scroll_area = new QVBoxLayout(central_scroll_area);
    ui->listWidget->setStyleSheet("background-image: url(:/model/image/label2.jpg);");
    layout_scroll_area->setAlignment(central_scroll_area,Qt::AlignBottom);
    scrollbar_in_scrollarea  =new QScrollBar(Qt::Vertical);
    scrollbar_in_scrollarea=ui->scrollArea->verticalScrollBar();
    scrollbar_in_scrollarea->setSliderDown(true);
    central_scroll_area->setStyleSheet("background-image: url(:/model/image/5.jpg);");
    ui->comboBox->addItem("Create Channel");
    ui->comboBox->addItem("Create Group");
    ui->comboBox->addItem("Log Out");

    mThread->start();


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
    req.setUrl(url->setGetGroupChatsQuery(str_id));
    manage->get(req);
    req.setUrl(url->setGetChannelChatsQuery(str_id));
    manage->get(req);
    //mThread->start();

}
void Main_b::set_mess_groupCre(QNetworkReply * r){
    QString rep_str = r->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
    ui->createlabel->setText(jobj["message"].toString());

}

void Main_b::set_mess_channelCre(QNetworkReply * r){
    QString rep_str = r->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
    ui->createlabel->setText(jobj["message"].toString());

}


void Main_b::thread_rec(){
    str_id=ui->label->text();
   // qDebug()<<str_id;
    if(str_id != ""){
    req.setUrl(url->setGetUserChatsQuery(str_id,last_date));
    manage->get(req);
    }
}


void Main_b::search_reply(QNetworkReply  *repl){

    QString rep_str = repl->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
    QString mess = jobj["message"].toString();
    QStringList pieces = mess.split( "-" );
    QString num_messages = pieces.value( pieces.length() - 2 );
     if(jobj["code"].toString() == "200"){

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
        if(j.value("src") == username){
            label2->setAlignment(Qt::AlignRight);
        }
        else{
            label2->setAlignment(Qt::AlignLeft);
        }
        layout_scroll_area->addWidget(label2,0,Qt::AlignBottom);
        ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
        if(cnt == num_messages.toInt() - 1)
            last_date=j.value("date").toString();
            last_date.remove('-');
            last_date.remove(' ');
            last_date.remove(':');
            long long date=last_date.toLongLong()+1;
            qDebug()<<date;
            last_date=date;
            qDebug()<<last_date;
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
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
    }
}




void Main_b::keyPressEvent (QKeyEvent *event)
{
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
        on_send_clicked();
    }
}

void Main_b::reply_item_clicked(QListWidgetItem *item)
{
    remove_item_in_layout(layout_scroll_area);
    last_date="";
    ui->label->setText(item->text());
    str_id = ui->label->text();
//    req.setUrl(url->setGetUserChatsQuery(str_id));
//    manage->get(req);

}

void Main_b::remove_item_in_layout(QLayout *lay)
{
    QLayoutItem* child;
    while(lay->count()!=0)
        {
            child = lay->takeAt(0);
            if(child->layout() != 0)
            {
                remove_item_in_layout(child->layout());
            }
            else if(child->widget() != 0)
            {
                delete child->widget();
            }

            delete child;
        }
}

void Main_b::on_pushButton_clicked()
{
    QString str_combo = ui->comboBox->currentText();
    if(str_combo == "Log Out"){
        req.setUrl( url -> setLogOutQuery(username ,password));
        manager ->get(req);

    }

    else if(str_combo == "Create Group"){

        QString group_name = ui->creation_name->text();
        creation group_cre;
        group_cre.create_group(token , group_name , group_create_net);


    }

    else if(str_combo == "Create Channel"){

        QString channel_name = ui->creation_name->text();
        creation channel_cre;
        channel_cre.create_channel(token , channel_name , channel_create_net);
    }
}

void Main_b::showlist(QString str)
{

    ui->listWidget->addItem(str);

}

