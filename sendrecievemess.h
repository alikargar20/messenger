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
    QNetworkReply * r;
public:
    QNetworkAccessManager *net;
    SendRecieveMess();
    void send_user(QString dst_id , QString mess , QString token);
    void send_group(QString grp_id , QString mess , QString token);
    void send_channel(QString chn_id , QString mess , QString token);
   };

#endif // SENDRECIEVEMESS_H
