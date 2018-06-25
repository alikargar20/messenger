#include "getlist.h"
#include "ui_main_b.h"

GetList::GetList(QString token):Main_b(token , username , password)
{
    url=new SetQuery();
    url->setToken(token);
}

void GetList::getuserlist()
{

    req.setUrl(url->setGetUserListQuery());
    manager->get(req);
    manager->finished(reply);
    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    if(rep_obj["code"].toString()=="200"){

    }
}

void GetList::getgrouplist()
{

    req.setUrl(url->setGetGroupListQuery());
    manager->get(req);
    manager->finished(reply);
    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    if(rep_obj["code"].toString()=="200"){

    }
}

void GetList::getchannellist()
{

    req.setUrl(url->setGetChannelListQuery());
    manager->get(req);
    manager->finished(reply);
    QString rep_str = reply->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject rep_obj=jdoc.object();
    if(rep_obj["code"].toString()=="200"){

    }
}

void GetList::updatelist()
{

    getuserlist();
    getchannellist();
    getgrouplist();
}
