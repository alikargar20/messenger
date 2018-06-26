#ifndef GETLIST_H
#define GETLIST_H
#include "main_b.h"
#include "setquery.h"
#include <QThread>

class GetList : protected Main_b
{
private:
    QNetworkReply *reply;
    SetQuery *url;


public:
    GetList(QString token);
    void getuserlist();
    void getgrouplist();
    void getchannellist();
    void updatelist();
    void makeThread();
};

#endif // GETLIST_H
