#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include<QNetworkReply>
class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0, bool b = false);
    void run();

    // if Stop = true, the thread will break
    // out of the loop, and will be disposed
    bool Stop;
    QNetworkReply * repl;
signals:
    // To communicate with Gui Thread
    // we need to emit a signal
    void thread_rec();
    void search_reply(QNetworkReply  *repl);
public slots:

};

#endif // THREAD_H
