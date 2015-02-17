#ifndef BTTRANSMITTER_H
#define BTTRANSMITTER_H

//-----------------------------------------------------
//Класс SOCKET. инициализирующий и обслуживающий.
//Перенаправляющий сообщения в сокет до BTmodul
//-----------------------------------------------------

#include <QObject>
#include <QThread>
#include <qlocalsocket.h>
#include <qlocalserver.h>
#define BT_MESSAGE_SIZE 100


#include <QQueue>
struct mess
{
    char s[BT_MESSAGE_SIZE];
    mess(char * s_)
    {
        memcpy(s,s_,BT_MESSAGE_SIZE);
    }
};

class BTtransmitterWorker : public QThread
{
    Q_OBJECT
public:
    bool DispLog;
    bool isconnected;
    explicit BTtransmitterWorker()
    {}
    ~BTtransmitterWorker()
    {client->disconnectFromServer();}
private:
    QQueue<mess> que;
public slots:
    void start()
    {
        shutdownview = false;
        printf("<BTtransmitter>: worker started\n");
        run();
    }
    void stop() { shutdownview = true; }
private:
    bool write(char * message);
    QLocalSocket * client;
    void SocketConnect();
signals:
protected slots:
    void addmessage(char * message)
    {
        if (DispLog) printf("<BTtransmitter>: New message to send\n");
        que.enqueue(mess(message));
    }
    void connected()
    {
        printf("<BTtransmitter>: New Connection\n");
        isconnected=true;
    }
    void disconnected()
    {
        printf("<BTtransmitter>: Disconnected\n");
        isconnected=false;
//        client->disconnect();
        client->abort();
//        client->reset();
    }    
    void stateChanged ( QLocalSocket::LocalSocketState socketState)
    {
        printf("<BTtransmitter>: stateChanged\n");
    }
    void error ( QLocalSocket::LocalSocketError socketError )
    {
        printf("<BTtransmitter>: error\n");
    }
private:
    void run();
    bool shutdownview;
};


class BTtransmitter : public QThread
{
    Q_OBJECT
public:
    BTtransmitterWorker worker;
    QThread thread;
public:
    explicit BTtransmitter(){}
    ~BTtransmitter() { stop(); thread.terminate(); thread.wait(100); }

    void init()
    {
        worker.moveToThread(&thread);
        printf("<BTtransmitter> init ok\n");
        connect(this, SIGNAL(wstart()), &worker, SLOT(start()));
        connect(this, SIGNAL(wstop()), &worker, SLOT(stop()));
        connect(&thread, SIGNAL(finished()), &worker, SLOT(deleteLater()));
    }

    void start()
    {
        thread.start();
        printf("<BTtransmitter> thread started\n");
        emit wstart();
    }

    void stop() { emit wstop(); }

signals:
    void wstart();
    void wstop();
};

#endif // BTTRANSMITTER_H
