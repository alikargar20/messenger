#ifndef GETLIST_H
#define GETLIST_H
#include "main_b.h"
#include "setquery.h"
#include <QThread>

class GetList:public QObject
{
private:
    Q_OBJECT
    SetQuery *url;
    QNetworkRequest  req;
    QNetworkAccessManager *manager_user;
    QNetworkAccessManager *manager_group;
    QNetworkAccessManager *manager_channel;
    QStringList users;
    QStringList groups;
    QStringList channels;

public:
    GetList(QString token);
    void getuserlist();
    void getgrouplist();
    void getchannellist();
    void updatelist();
    void getuserlist_reply(QNetworkReply *repl);
    void getgrouplist_reply(QNetworkReply *repl);
    void getchannellist_reply(QNetworkReply *repl);
};

#endif // GETLIST_H
