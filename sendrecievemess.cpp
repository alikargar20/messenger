#include "sendrecievemess.h"

SendRecieveMess::SendRecieveMess()
{
    net = new QNetworkAccessManager;
    //connect(net , &QNetworkAccessManager::finished , this , &SendRecieveMess::reply_recieve);
}


void SendRecieveMess::send_user(QString dst_id , QString mess , QString token){

    SetQuery *url;
    url = new SetQuery;
    url->setToken(token);
    req.setUrl( url->setSendMessageUser(dst_id , mess));
    net->get(req);
}


void SendRecieveMess::recieve_user(QString token , QString dst){
    SetQuery *url;
    url = new SetQuery;
    url->setToken(token);
    req.setUrl(url->setGetUserChatsQuery(dst));
    net->get(req);
    qDebug()<<"GDSFHSh";
    //connect(net , &QNetworkAccessManager::finished , this , &SendRecieveMess::reply_recieve);

    }



void SendRecieveMess::reply_recieve(QNetworkReply *reply){
    qDebug()<<"SDF";
       QByteArray data = reply->readAll();
       qDebug() << data;
       QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
       QJsonObject jsonReply = jsonDoc.object();

       QJsonObject response = jsonReply["block 0"].toObject();
       qDebug()<<response["dst"].toString()<<"-->"<<response["body"].toString();
       //QJsonArray  data     = jsonReply["body"].toArray();
       //qDebug() << data;



}
