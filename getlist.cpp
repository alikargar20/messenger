#include "getlist.h"




GetList::GetList(QString token, QObject *parent):QThread(parent)
{
    timer=new QTimer(this);
    url=new SetQuery();
    url->setToken(token);
    manager_user=new QNetworkAccessManager(this);
    manager_group=new QNetworkAccessManager(this);
    manager_channel=new QNetworkAccessManager(this);
    connect(manager_user,&QNetworkAccessManager::finished,this,&GetList::getuserlist_reply);
    connect(manager_group,&QNetworkAccessManager::finished,this,&GetList::getgrouplist_reply);
    connect(manager_channel,&QNetworkAccessManager::finished,this,&GetList::getchannellist_reply);
    connect(timer,SIGNAL(timeout()),this,SLOT(getuserlist()));
    connect(timer,SIGNAL(timeout()),this,SLOT(getgrouplist()));
    connect(timer,SIGNAL(timeout()),this,SLOT(getchannellist()));
    timer->start(500);

}

void GetList::getuserlist()
{
    req.setUrl(url->setGetUserListQuery());
    manager_user->get(req);
}
void GetList::getuserlist_reply(QNetworkReply *repl){

    QString rep_str = repl->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    QString mess = rep_obj["message"].toString();
    QStringList pieces = mess.split( "-" );
    QString num_user = pieces.value( pieces.length() - 2 );
    if(rep_obj["code"].toString()=="200"){
      for(int i=0;i<num_user.toInt();i++){
        QString block_str = "block ";
        block_str += QString::number(i);
        QJsonObject j=rep_obj.value(block_str).toObject();
        if(j.value("src").toString() != ""&&is_not_repetetive(users,j.value("src").toString())){
        users<<j.value("src").toString();
        emit get_finished(j.value("src").toString());
        }
      }
    }
}


void GetList::getgrouplist()
{
    req.setUrl(url->setGetGroupListQuery());
    manager_group->get(req);
}

void GetList::getgrouplist_reply(QNetworkReply *repl)
{

    QString rep_str = repl->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    QString mess = rep_obj["message"].toString();
    QStringList pieces = mess.split( "-" );
    QString num_group = pieces.value( pieces.length() - 2 );
    if(rep_obj["code"].toString()=="200"){
        for(int i=0;i<num_group.toInt();i++){
            QString block_str = "block ";
            block_str += QString::number(i);
            QJsonObject j=rep_obj.value(block_str).toObject();
            if(j.value("group_name").toString() != ""&&is_not_repetetive(groups,j.value("group_name").toString())){
            groups<<j.value("group_name").toString();
            emit get_finished(j.value("group_name").toString());
            }
        }

    }

}

void GetList::getchannellist()
{
    req.setUrl(url->setGetChannelListQuery());
    manager_channel->get(req);
}

void GetList::getchannellist_reply(QNetworkReply *repl)
{

    QString rep_str = repl->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    QString mess = rep_obj["message"].toString();
    QStringList pieces = mess.split( "-" );
    QString num_channel = pieces.value( pieces.length() - 2 );
    if(rep_obj["code"].toString()=="200"){
        for(int i=0;i<num_channel.toInt();i++){
            QString block_str = "block ";
            block_str += QString::number(i);
            QJsonObject j=rep_obj.value(block_str).toObject();
            if(j.value("channel_name").toString() != ""&&is_not_repetetive(channels,j.value("channel_name").toString())){
            channels<<j.value("channel_name").toString();
            emit get_finished(j.value("channel_name").toString());
            }
        }
    }

}

bool GetList::is_not_repetetive(QStringList list, QString str)
{
    bool found=true;
    QStringList::Iterator it;
    for(it=list.begin();it != list.end();it++){
        if((*it)==str)
            found=false;
    }
    return found;
}



