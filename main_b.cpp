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
    mThread = new Thread(token,this);
    list_thread=new GetList(token,this);
    manager = new QNetworkAccessManager(this);
    manage = new QNetworkAccessManager(this);
    channel_create_net = new QNetworkAccessManager(this);
    group_create_net = new QNetworkAccessManager(this);
    cha_join = new QNetworkAccessManager(this);
    gp_join = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&Main_b::Reply);
    connect(manage,&QNetworkAccessManager::finished,this,&Main_b::search_reply);
    connect(mThread, SIGNAL(get_finished(QString,QString)),this, SLOT(makeLabel(QString,QString)));
    connect(list_thread,SIGNAL(get_finished(QString)),this,SLOT(showlist(QString)));
    connect(group_create_net , &QNetworkAccessManager::finished , this , &Main_b::set_mess_groupCre);
    connect(channel_create_net , &QNetworkAccessManager::finished , this , &Main_b::set_mess_channelCre);
    connect(ui->listWidget,&QListWidget::itemClicked,this,&Main_b::reply_item_clicked);
    connect(cha_join , &QNetworkAccessManager::finished , this , &Main_b::reply_join);
    connect(gp_join , &QNetworkAccessManager::finished , this , &Main_b::reply_join);
    connect(this,SIGNAL(textLabelChanged(QString)),this,SLOT(id_set(QString)));


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
    ui->comboBox->addItem("Join Channel");
    ui->comboBox->addItem("Join Group");






}

Main_b::~Main_b()
{

    delete list_thread;
    delete mThread;
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





void Main_b::search_reply(QNetworkReply  *repl){

    QString rep_str = repl->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
    QString mess = jobj["message"].toString();
    QStringList pieces = mess.split( "-" );
    QString num_messages = pieces.value( pieces.length() - 2 );
     if(jobj["code"].toString() == "200"){

        ui->label->setText(str_id);
        emit textLabelChanged(str_id);
        remove_item_in_layout(layout_scroll_area);


     QString txt;
     for(int cnt = 0 ; cnt < num_messages.toInt() ; cnt++ ){
        QString block_str = "block ";
        block_str += QString::number(cnt);
        QJsonObject j = jobj.value(block_str).toObject();
        txt=j.value("body").toString();
        if(last_date==j.value("date").toString())
            continue;
        if(txt != ""){
            if(txt.length()>62){
                for(int i=1;i<=txt.length()/62;i++)
                txt.insert(i*62,"\n");
            }
        makeLabel(txt,j.value("src").toString());
        if(cnt == num_messages.toInt() - 1){
            last_date=j.value("date").toString();
        }

        }
        }


    }

}


void Main_b ::Reply(QNetworkReply * rep){
    delete list_thread;
    delete mThread;
    QString str = rep ->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(str.toUtf8());
    QJsonObject obj=jdoc.object();
    if(obj["code"].toString() == "200"){

        LoginPage *log = new LoginPage;
        log->show();
        setCentralWidget(log);
        log->setGeometry(300,40,795,715);


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
    send_obj.send_channel(str_id,str_mess,token);
    send_obj.send_group(str_id,str_mess,token);
    ui->typekon->setText("");
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
    emit textLabelChanged(str_id);


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
        QString filename="/home/siavash/git messanger/messenger_L/save.txt";
        QFile file( filename );
        if ( file.open(QIODevice::WriteOnly) )
        {
            QTextStream stream( &file );

            stream << "00"<< endl ;


    }
        file.close();
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


    else if(str_combo == "Join Channel"){

        QString channel_name = ui->creation_name->text();
        request.setUrl(url->setJoinChannelQuery(channel_name));
        cha_join->get(request);

    }


    else if(str_combo == "Join group"){

        QString group_name = ui->creation_name->text();
        request.setUrl(url->setJoinGroupQuery(group_name));
        gp_join->get(request);

    }
}

void Main_b::reply_join(QNetworkReply * r){
    QString str = r ->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(str.toUtf8());
    QJsonObject obj=jdoc.object();
    qDebug()<<obj["message"].toString();
    ui->createlabel->setText(obj["message"].toString());
}

void Main_b::showlist(QString str)
{
    ui->listWidget->addItem(str);
}

void Main_b::id_set(QString s)
{
    mThread->setId(s);
    mThread->setLastDate("");

}

void Main_b::makeLabel(QString txt, QString src)
{
    QLabel *label2 = new QLabel(txt);
    label2->setWordWrap(true);
    if(src == username){
        label2->setAlignment(Qt::AlignRight);
    }
    else{
        label2->setAlignment(Qt::AlignLeft);
    }
    layout_scroll_area->addWidget(label2,0,Qt::AlignBottom);
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());

}



