#include "getlist.h"

GetList::GetList(QString token):Main_b(token)
{

}

void GetList::getuserlist()
{

    QUrl url("http://api.softserver.org:1104/getuserlist");
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

void GetList::getgrouplist()
{

    QUrl url("http://api.softserver.org:1104/getgrouplist");
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
