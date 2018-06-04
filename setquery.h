#ifndef SETQUERY_H
#define SETQUERY_H
#include <QString>
#include <QUrl>
#include <QUrlQuery>
class SetQuery
{
private:
    QString  token;
    QUrl  outurl;
    QUrlQuery query;
public:
    SetQuery();
    QUrl setSignUpQuery();
    QUrl setLoginQuery();
    QUrl setLogOutQuery();
    QUrl setCreateGroupQuery();
    QUrl setCreateChannelQuery();
    QUrl setGetUserListQuery();
    QUrl setGetGroupListQuert();
    QUrl setGetChannelListQuery();
    QUrl setGetUserChatsQuery();
    QUrl setGetGroupChatsQuery();
    QUrl setGetChannelChatsQuery();
    //
};

#endif // SETQUERY_H
