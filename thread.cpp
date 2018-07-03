#include "thread.h"
#include<QStringList>
Thread::Thread(QString token, QObject *parent) : QThread(parent)
{
    url=new SetQuery;
    url->setToken(token);
    manager=new QNetworkAccessManager(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(receive_thread()));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getChat(QNetworkReply*)));
    timer->start(1000);
}

void Thread::setId(QString id)
{
    this->id=id;
}

void Thread::setLastDate(QString date)
{
    last_date=date;
}

void Thread::receive_thread()
{

    if(id != ""){
    req.setUrl(url->setGetUserChatsQuery(id,last_date));
    manager->get(req);
    }
}

void Thread::getChat(QNetworkReply *repl)
{
    QString rep_str = repl->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
    QString mess = jobj["message"].toString();
    QStringList pieces = mess.split( "-" );
    QString num_messages = pieces.value( pieces.length() - 2 );
     if(jobj["code"].toString() == "200"){
             QString txt;
             QString last;
             for(int cnt = 0 ; cnt < num_messages.toInt() ; cnt++ ){
                QString block_str = "block ";
                block_str += QString::number(cnt);
                QJsonObject j = jobj.value(block_str).toObject();
                txt=j.value("body").toString();
                last=j.value("date").toString();
                last.remove('-');
                last.remove(' ');
                last.remove(':');
                if(last_date==last)
                      continue;
                if(txt != ""){
                    if(txt.length()>62){
                        for(int i=1;i<=txt.length()/62;i++)
                        txt.insert(i*62,"\n");
                    }


                if(cnt == num_messages.toInt() - 1){
                    last_date=j.value("date").toString();
                    last_date.remove('-');
                    last_date.remove(' ');
                    last_date.remove(':');
                     }
                    emit get_finished(txt,j.value("src").toString());
                 }
            }
        }
}
