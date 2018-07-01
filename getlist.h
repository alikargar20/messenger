#ifndef GETLIST_H
#define GETLIST_H
#include "setquery.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QTimer>
#include <QThread>
#include <QMutex>


class GetList:public QThread
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
    QTimer *timer;



public:

    GetList(QString token, QObject *parent = 0);
    void getuserlist_reply(QNetworkReply *repl);
    void getgrouplist_reply(QNetworkReply *repl);
    void getchannellist_reply(QNetworkReply *repl);
    QStringList get_users();
    QStringList get_groups();
    QStringList get_channnels();
    bool is_not_repetetive(QStringList list,QString str);

signals:
    void get_finished(QString);
public slots:
    void getuserlist();
    void getgrouplist();
    void getchannellist();
};

#endif // GETLIST_H
