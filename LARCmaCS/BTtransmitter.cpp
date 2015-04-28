#include "BTtransmitter.h"
#include "Windows.h"

#define PipeAdress "BTmodul"

#include <QtWidgets/QApplication>

void BTtransmitterWorker::run()
{
    isconnected=false;
    client = new QLocalSocket();
    connect(client,SIGNAL(connected()),this,SLOT(connected()));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
    //connect(client,SIGNAL(error ( QLocalSocket::LocalSocketError)),
    //        this,SLOT(error ( QLocalSocket::LocalSocketError)));
    //connect(client,SIGNAL(stateChanged ( QLocalSocket::LocalSocketState )),
    //        this,SLOT(stateChanged ( QLocalSocket::LocalSocketState)));
    while (!shutdownview)
    {
        qDebug()<<"<BTtransmitter>: White connect...";
        while((isconnected==false) && (!shutdownview))
        {
           Sleep(50);
           SocketConnect();
           QApplication::processEvents();
        }
        while((isconnected) && (!shutdownview))
        {
            if (!que.empty())
            {
                if (write(que.dequeue().s)==0)
                {
                    client->abort();
                }
            }
            else
            {
                Sleep(1);
                QApplication::processEvents();
            }
        }
        QApplication::processEvents();
    }
}
bool BTtransmitterWorker::write(char * message)
{
/*
    if (false==client->isValid ())
        printf("-------------------\n");
    QLocalSocket::LocalSocketState state=client->state();
    if (state==QLocalSocket::UnconnectedState)
        printf("...................QLocalSocket::UnconnectedState\n");
    if (state==QLocalSocket::ConnectingState)
        printf("...................QLocalSocket::ConnectingState\n");
    if (state==QLocalSocket::ConnectedState)
        printf("...................QLocalSocket::ConnectedState\n");
    if (state==QLocalSocket::ClosingState)
        printf("...................QLocalSocket::ClosingState\n");*/
    if (DispLog) qDebug() << "Element:" << message;
    if (client->isWritable())
    {
        qint64 re=client->write(message,BT_MESSAGE_SIZE );
        if (re>0)
        {
            if (BT_MESSAGE_SIZE!=re)
                 qDebug()<<"<BTtransmitter>: WARING! socket insufficient size buffer by write "<<re;
            else if (DispLog) qDebug()<<("<BTtransmitter>: OK");
            return 1;
        }
        else
        {
            qDebug()<<"<BTtransmitter>: Error writing to socket #"<<re;
            return 0;
        }
    }
    else
    {
        qDebug()<<"<BTtransmitter>: Error, socket is not Writable";
        return 0;
    }
}

void BTtransmitterWorker::SocketConnect()
{
    client->connectToServer("BTmodul",QIODevice::WriteOnly);
}
