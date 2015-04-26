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

#include <QDebug>

#include <QQueue>
class mess
{
public:
    char s[BT_MESSAGE_SIZE];
    mess(char * s_)
    {
        memcpy(s,s_,BT_MESSAGE_SIZE);
    }
    mess(mess * copy)
    {
        memcpy(s,copy->s,BT_MESSAGE_SIZE);
    }
    mess(mess const& copy)
    {
        memcpy(s,copy.s,BT_MESSAGE_SIZE);
    }
};

class BTtransmitterWorker : public QThread
{
    Q_OBJECT
private:
    QQueue<mess> que;
public:
    bool DispLog;
    bool isconnected;
public:
    explicit BTtransmitterWorker()
    {
        DispLog=false;
    }
    ~BTtransmitterWorker()
    {client->disconnectFromServer();}
public slots:
    void start()
    {
        shutdownview = false;
        qDebug()<<"<BTtransmitter>: worker started";
        run();
    }
    void stop() { shutdownview = true; }
private:
    bool write(char * message);
    QLocalSocket * client;
    void SocketConnect();
signals:
    void UpdatePipeStatus(bool status);
protected slots:
    void addmessage(char * message)
    {
        if (DispLog)
            qDebug()<<"<BTtransmitter>: New message to send";
        que.enqueue(mess(message));
        delete(message);
    }
    void connected()
    {
        qDebug()<<"<BTtransmitter>: New Connection, SUCCESS!";
        isconnected=true;
        emit UpdatePipeStatus(true);
    }
    void disconnected()
    {
        qDebug()<<"<BTtransmitter>: Disconnected";
        isconnected=false;
//        client->disconnect();
        client->abort();        
        emit UpdatePipeStatus(false);
//        client->reset();
    }    
    //void stateChanged ( QLocalSocket::LocalSocketState socketState)
    //{
    //    qDebug()<<"<BTtransmitter>: stateChanged";
    //}
    //void error ( QLocalSocket::LocalSocketError socketError )
    //{
    //    qDebug()<<"<BTtransmitter>: error";
    //}
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
        qDebug()<<("<BTtransmitter> init ok\n");
        connect(this, SIGNAL(wstart()), &worker, SLOT(start()));
        connect(this, SIGNAL(wstop()), &worker, SLOT(stop()));
        connect(&thread, SIGNAL(finished()), &worker, SLOT(deleteLater()));
    }

    void start()
    {
        thread.start();
        qDebug()<<("<BTtransmitter> thread started\n");
        emit wstart();
    }

    void stop() { emit wstop(); }

signals:
    void wstart();
    void wstop();
};

#endif // BTTRANSMITTER_H
