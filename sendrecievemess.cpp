#include "sendrecievemess.h"

SendRecieveMess::SendRecieveMess()
{
    net = new QNetworkAccessManager;
    //connect(net , &QNetworkAccessManager::finished , this , &SendRecieveMess::reply_recieve);
}


void SendRecieveMess::send_user(QString dst_id , QString mess , QString token){

    SetQuery *url;
    url = new SetQuery;
    url->setToken(token);
    req.setUrl( url->setSendMessageUser(dst_id , mess));
    net->get(req);
}


void SendRecieveMess::send_group(QString grp_id , QString mess , QString token){

    SetQuery *url;
    url = new SetQuery;
    url->setToken(token);
    req.setUrl(url->setSendMessageGroup(grp_id , mess));
    net->get(req);


}


void SendRecieveMess::send_channel(QString chn_id , QString mess , QString token){

    SetQuery *url;
    url = new SetQuery;
    url->setToken(token);
    req.setUrl(url->setSendMessageChannel(chn_id , mess));
    net->get(req);

}
