#ifndef SENDRECIEVEMESS_H
#define SENDRECIEVEMESS_H
#include"ui_main_b.h"
#include"main_b.h"
#include"setquery.h"
#include<QNetworkRequest>
#include<QTimer>
class SendRecieveMess:public QObject
{
    Q_OBJECT
    QNetworkRequest req;

public:
    QNetworkAccessManager *net;
    SendRecieveMess();
    void send_user(QString dst_id , QString mess , QString token);
    void recieve_user(QString token , QString dst);
    void reply_recieve(QNetworkReply*);
};

#endif // SENDRECIEVEMESS_H
