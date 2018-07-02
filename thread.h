#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QTimer>
#include "setquery.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QString token,QObject *parent = 0);
    void setId(QString id);
    void setLastDate(QString date);
private:
    QTimer *timer;
    QString last_date;
    QString id;
    SetQuery *url;
    QNetworkRequest  req;
    QNetworkAccessManager *manager;
signals:
    void get_finished(QString,QString);


public slots:
    void receive_thread();
    void getChat(QNetworkReply* repl);

};

#endif // THREAD_H
