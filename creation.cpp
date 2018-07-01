#include "creation.h"

creation::creation()
{
}


void creation::create_channel(QString token , QString channel_name , QNetworkAccessManager * network){
    SetQuery *url;
    url = new SetQuery;
    url->setToken(token);
    request.setUrl( url->setCreateChannelQuery(channel_name , ""));
    network->get(request);

}


void creation::create_group(QString token , QString group_name , QNetworkAccessManager * network){
    SetQuery *url;
    url = new SetQuery;
    url->setToken(token);
    request.setUrl( url->setCreateGroupQuery(group_name , ""));
    network->get(request);

}
