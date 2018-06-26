#include "sendrecievemess.h"

SendRecieveMess::SendRecieveMess()
{
    net = new QNetworkAccessManager;
}


void SendRecieveMess::send_user(QString dst_id , QString mess , QString token){

    SetQuery *url;
    url = new SetQuery;
    url->setToken(token);
    req.setUrl( url->setSendMessageUser(dst_id , mess));
    net->get(req);
}
