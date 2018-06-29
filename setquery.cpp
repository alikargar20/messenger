#include "setquery.h"
#include<QDebug>
SetQuery::SetQuery()
{
    url_str="http://api.softserver.org:1104/";
}

void SetQuery::setToken(QString token)
{
    this->token=token;
}

QUrl SetQuery::setSignUpQuery(QString nUser,QString nPass,QString fName,QString lName)
{
    url.setUrl(url_str+"signup");
    query.addQueryItem("username",nUser);
    query.addQueryItem("password",nPass);
    query.addQueryItem("firsname",fName);
    query.addQueryItem("lastname",lName);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setLoginQuery(QString userName,QString pass)
{
    url.setUrl(url_str+"login");
    query.addQueryItem("username",userName);
    query.addQueryItem("password",pass);
    url.setQuery(query);
    query.clear();
    return url;

}

QUrl SetQuery::setLogOutQuery(QString userName,QString pass)
{
    url.setUrl(url_str+"logout");
    query.addQueryItem("username",userName);
    query.addQueryItem("password",pass);
    url.setQuery(query);
    query.clear();
    return url;

}

QUrl SetQuery::setCreateGroupQuery(QString group_name,QString group_title)
{
    url.setUrl(url_str+"creategroup");
    query.addQueryItem("token",token);
    query.addQueryItem("group_name",group_name);
    query.addQueryItem("group_title",group_title);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setCreateChannelQuery(QString channel_name,QString channel_title)
{
    url.setUrl(url_str+"createchannel");
    query.addQueryItem("token",token);
    query.addQueryItem("channel_name",channel_name);
    query.addQueryItem("channel_title",channel_title);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setGetUserListQuery()
{
    url.setUrl(url_str+"getuserlist");
    query.addQueryItem("token",token);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setGetGroupListQuery()
{
    url.setUrl(url_str+"getgrouplist");
    query.addQueryItem("token",token);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setGetChannelListQuery()
{
    url.setUrl(url_str+"getchannellist");
    query.addQueryItem("token",token);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setGetUserChatsQuery(QString username_dst ,QString date_YYYYMMDDHHmmss )
{
    url.setUrl(url_str+"getuserchats");
    query.addQueryItem("token",token);
    query.addQueryItem("dst",username_dst);
    if(date_YYYYMMDDHHmmss != "")
        query.addQueryItem("date",date_YYYYMMDDHHmmss);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setGetGroupChatsQuery(QString group_dst,QString date_YYYYMMDDHHmmss)
{
    url.setUrl(url_str+"getgroupchats");
    query.addQueryItem("token",token);
    query.addQueryItem("dst",group_dst);
    if(date_YYYYMMDDHHmmss != "")
        query.addQueryItem("date",date_YYYYMMDDHHmmss);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setGetChannelChatsQuery(QString channel_dst,QString date_YYYYMMDDHHmmss)
{
    url.setUrl(url_str+"getchannelchats");
    query.addQueryItem("token",token);
    query.addQueryItem("dst",channel_dst);
    if(date_YYYYMMDDHHmmss != "")
        query.addQueryItem("date",date_YYYYMMDDHHmmss);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setJoinGroupQuery(QString group_name)
{
    url.setUrl(url_str+"joingroup");
    query.addQueryItem("token",token);
    query.addQueryItem("group_name",group_name);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setJoinChannelQuery(QString channel_name)
{
    url.setUrl(url_str+"joinchannel");
    query.addQueryItem("token",token);
    query.addQueryItem("channel",channel_name);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setSendMessageUser(QString username_dst, QString body)
{
    url.setUrl(url_str+"sendmessageuser");
    query.addQueryItem("token",token);
    query.addQueryItem("dst",username_dst);
    query.addQueryItem("body",body);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setSendMessageGroup(QString group_dst, QString body)
{
    url.setUrl(url_str+"sendmessagegroup");
    query.addQueryItem("token",token);
    query.addQueryItem("dst",group_dst);
    query.addQueryItem("body",body);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setSendMessageChannel(QString channel_dst, QString body)
{
    url.setUrl(url_str+"sendmessagechannel");
    query.addQueryItem("token",token);
    query.addQueryItem("dst",channel_dst);
    query.addQueryItem("body",body);
    url.setQuery(query);
    query.clear();
    return url;
}

QUrl SetQuery::setGetNameQuery(QString username)
{
    url.setUrl(url_str+"getname");
    query.addQueryItem("username",username);
    url.setQuery(query);
    query.clear();
    return url;
}
