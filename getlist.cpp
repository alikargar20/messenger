#include "getlist.h"
#include "ui_main_b.h"

GetList::GetList(QString token):Main_b(token , username , password)
{
    url=new SetQuery();
    url->setToken(token);
}

void GetList::getuserlist()
{
    QStringList counter;
    QString cnt;
    req.setUrl(url->setGetUserListQuery());
    manager->get(req);
    manager->finished(reply);
    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();


    if(rep_obj["code"].toString()=="200"){
        counter=rep_obj["message"].toString().split("-");
        cnt=counter.at(1);
        for(int i=0;i<cnt.toInt();i++){
        QJsonValue value=rep_obj.value("block "+i);
        QJsonObject item= value.toObject();
        ui->listWidget->addItem(item["user_name"].toString());

        }

    }
}

void GetList::getgrouplist()
{
    QStringList counter;
    QString cnt;
    req.setUrl(url->setGetGroupListQuery());
    manager->get(req);
    manager->finished(reply);
    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    if(rep_obj["code"].toString()=="200"){
        counter=rep_obj["message"].toString().split("-");
        cnt=counter.at(1);
        for(int i=0;i<cnt.toInt();i++){
        QJsonValue value=rep_obj.value("block "+i);
        QJsonObject item= value.toObject();
        ui->listWidget->addItem(item["group_name"].toString());

        }

    }
}

void GetList::getchannellist()
{
    QStringList counter;
    QString cnt;
    req.setUrl(url->setGetChannelListQuery());
    manager->get(req);
    manager->finished(reply);
    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    if(rep_obj["code"].toString()=="200"){
        counter=rep_obj["message"].toString().split("-");
        cnt=counter.at(1);
        for(int i=0;i<cnt.toInt();i++){
        QJsonValue value=rep_obj.value("block "+i);
        QJsonObject item= value.toObject();
        ui->listWidget->addItem(item["channel_name"].toString());

        }
    }
}

void GetList::updatelist()
{

    getuserlist();
    getchannellist();
    getgrouplist();
}

void GetList::makeThread()
{
    QThread th;

}
