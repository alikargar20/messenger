#include "thread.h"

Thread::Thread(QString token, QObject *parent) : QThread(parent)
{
    url=new SetQuery;
    url->setToken(token);
    manager=new QNetworkAccessManager(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(receive_thread()));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getChat(QNetworkReply*)));
    timer->start(500);
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
<<<<<<< HEAD
    while(true)
    {
        QMutex mutex;
        // prevent other threads from changing the "Stop" value
        mutex.lock();
        if(this->Stop) break;
        mutex.unlock();

        // emit the signal for the count label
       // emit search_reply(repl);
        emit thread_rec();

        // slowdown the count change, msec
        this->msleep(7000);
=======
    if(id != ""){
    req.setUrl(url->setGetUserChatsQuery(id,last_date));
    manager->get(req);
>>>>>>> 3a2a7b4b854554e07119c17bb9a60a9792f6eccc
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
    qDebug()<<num_messages;
     if(jobj["code"].toString() == "200"){
             QString txt;
             for(int cnt = 0 ; cnt < num_messages.toInt() ; cnt++ ){
                QString block_str = "block ";
                block_str += QString::number(cnt);
               // qDebug()<<block_str;
                QJsonObject j = jobj.value(block_str).toObject();
                txt=j.value("body").toString();
                qDebug()<<txt;
                if(last_date==j.value("date").toString())
                    continue;
                if(txt != ""){
                    if(txt.length()>62){
                        for(int i=1;i<=txt.length()/62;i++)
                        txt.insert(i*62,"\n");
                    }


                if(cnt == num_messages.toInt() - 1){
                    last_date=j.value("date").toString();
                     }
                qDebug()<<j.value("src").toString()<<" :: "<<txt;
                    emit get_finished(txt,j.value("src").toString());
                 }
            }
        }
}

