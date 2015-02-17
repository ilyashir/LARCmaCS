#include "BTtransmitter.h"
#include "Windows.h"

#define PipeAdress "BTmodul"

#include <QtWidgets/QApplication>

void BTtransmitterWorker::run()
{
    isconnected=false;
    DispLog=true;
    client = new QLocalSocket();
    connect(client,SIGNAL(connected()),this,SLOT(connected()));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
    //connect(client,SIGNAL(error ( QLocalSocket::LocalSocketError socketError )),
    //        this,SLOT(error ( QLocalSocket::LocalSocketError socketError )));
    //connect(client,SIGNAL(stateChanged ( QLocalSocket::LocalSocketState socketState )),
    //        this,SLOT(stateChanged ( QLocalSocket::LocalSocketState socketState )));
    while (1)
    {
        printf("<BTtransmitter>: White connect...\n");
        SocketConnect();
        while(isconnected)
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
        Sleep(1000);
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
    qDebug() << "Element:" << message;
    if (client->isWritable())
    {
        if (DispLog) printf("Wtire : ");
        qint64 re=client->write(message,BT_MESSAGE_SIZE );
        if (re>0)
        {
            if (BT_MESSAGE_SIZE!=re)
                printf("WARING! socket insufficient size buffer by write %d\n",re);
            else if (DispLog) printf("OK\n");
            return 1;
        }
        else
        {
            if (DispLog) printf("Error_socket_write %d\n",re);
            return 0;
        }
    }
    else
    {
        if (DispLog) printf("Error, socket is not Writable\n");
        return 0;
    }
}

void BTtransmitterWorker::SocketConnect()
{
    client->connectToServer("BTmodul",QIODevice::WriteOnly);
}
