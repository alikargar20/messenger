#ifndef CREATION_H
#define CREATION_H
#include<QString>
#include"ui_main_b.h"
#include"main_b.h"
#include"setquery.h"
#include<QNetworkRequest>

class creation
{
public:
    creation();
    void create_group(QString token , QString group_name ,QNetworkAccessManager * network);
    void create_channel(QString token , QString channel_name , QNetworkAccessManager * network);
    QNetworkRequest request;
};

#endif // CREATION_H
