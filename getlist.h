#ifndef GETLIST_H
#define GETLIST_H
#include "main_b.h"

class GetList : protected Main_b
{
private:
    QNetworkReply *reply;
public:
    GetList(QString token);
    void getuserlist();
    void getgrouplist();
    void getchannellist();
    void updatelist();
};

#endif // GETLIST_H
