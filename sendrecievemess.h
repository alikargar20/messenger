#ifndef SENDRECIEVEMESS_H
#define SENDRECIEVEMESS_H
#include"ui_main_b.h"
#include"main_b.h"
#include"setquery.h"
#include<QNetworkRequest>
class SendRecieveMess
{

    QNetworkRequest req;
    QNetworkAccessManager *net;
public:
    SendRecieveMess();
    void send_user(QString dst_id , QString mess , QString token);
    void recieve();
};

#endif // SENDRECIEVEMESS_H
