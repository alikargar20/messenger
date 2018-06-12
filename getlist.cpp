#include "getlist.h"

GetList::GetList(QString token):Main_b(token)
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

    req.setUrl(url->setGetGroupListQuert());
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

    QUrl url("http://api.softserver.org:1104/getchannellist");
    QUrlQuery query;
    query.addQueryItem("token",token);
    url.setQuery(query);
    req.setUrl(url);
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
