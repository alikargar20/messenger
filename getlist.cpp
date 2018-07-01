#include "getlist.h"
#include "ui_main_b.h"

GetList::GetList(QString token)
{
    url=new SetQuery();
    url->setToken(token);
    manager_user=new QNetworkAccessManager(this);
    manager_group=new QNetworkAccessManager(this);
    manager_channel=new QNetworkAccessManager(this);
    connect(manager_user,QNetworkAccessManager::finished,this,&GetList::getuserlist_reply);
    connect(manager_group,QNetworkAccessManager::finished,this,&GetList::getgrouplist_reply);
    connect(manager_channel,QNetworkAccessManager::finished,this,&GetList::getchannellist_reply);
    updatelist();

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
        QJsonValue value=rep_obj.value("block "+i);
        QJsonObject item= value.toObject();
        users.push_back(item["user_name"].toString());
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
        QJsonValue value=rep_obj.value("block "+i);
        QJsonObject item= value.toObject();
        groups.push_back(item["group_name"].toString());
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
    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    QString mess = rep_obj["message"].toString();
    QStringList pieces = mess.split( "-" );
    QString num_channel = pieces.value( pieces.length() - 2 );
    if(rep_obj["code"].toString()=="200"){
        for(int i=0;i<num_channel.toInt();i++){
        QJsonValue value=rep_obj.value("block "+i);
        QJsonObject item= value.toObject();
        channels.push_back(item["channel_name"].toString());
        }
    }

}
void GetList::updatelist()
{
    getuserlist();
    getchannellist();
    getgrouplist();
}

