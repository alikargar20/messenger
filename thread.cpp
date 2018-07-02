#include "thread.h"
#include <QDebug>
#include <QMutex>
Thread::Thread(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
}

// run() will be called when a thread starts
void Thread::run()
{
    while(true)
    {
        QMutex mutex;
        // prevent other threads from changing the "Stop" value
        mutex.lock();
        if(this->Stop) break;
        mutex.unlock();

        // emit the signal for the count label
       // emit search_reply(repl);
        emit thread_rec();

        // slowdown the count change, msec
        this->msleep(7000);
    }
}
