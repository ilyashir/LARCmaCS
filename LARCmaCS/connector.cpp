#include <stdlib.h>
#include <iostream>
#include <QMap>

#include "connector.h"

//#define UDP_ADDR QHostAddress("192.168.1.255")
#define UDP_ADDR QHostAddress::Any
//#define UDP_ADDR QHostAddress::LocalHost

void ConnectorWorker::start()
{
    qDebug() << "Connector worker started";
    shutdownconnector = false;
   // QApplication::processEvents();
    init();
}


void ConnectorWorker::stop()
{
    shutdownconnector = true;
}

void ConnectorWorker::init()
{
    qDebug() << "Initializing connector.worker";

    connectedSockets = 0;
    connectedRobots = 0;
    //filename = "numMAC.txt";
    command.resize(6);
    command[0]='r';
    command[1]='u';
    command[2]='l';
    command[3]='e';
    command[4]=' ';



    udpSocket = new QUdpSocket(this);
    if (udpSocket->bind(UDP_ADDR, 3000))
        qDebug()<<"UDP OK!";
    else
        qDebug()<<"UDP FAIL!"<<udpSocket->errorString();

    //udpSocket->bind(QHostAddress::LocalHost, 3001);

//    tcpSentCount = 0;
//    tcpPort = 2000;
    connectedAllSocketsFlag = false;


    curRuleArray = new char[4 * 7]; // FIXME!

    gotPacketsNum = 0;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(udpBroadcastRequestIP()));
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(udpProcessPendingDatagrams()));

    qDebug()<<"INIT CONNECTOR OK";
}

void ConnectorWorker::receiveMacArray(QString * macArray)
{
    for (int i=0;i<12;++i)
    {
        qDebug()<<macArray[i];
        if (macArray[i].compare(""))
            numIP[i+1] = macIP[macArray[i]];
    }
    qDebug()<<numIP;
    connectedAllSocketsFlag = true;
}

void ConnectorWorker::stopBroadcast()
{
    qDebug()<<"BROADCAST STOPPED!";
    timer->stop();
    //emit sendMacs(macList);
    //connectedAllSocketsFlag = true;
   // if (curEnabledRobotsSet.size()>0)

}

void ConnectorWorker::startBroadcast()
{
    qDebug()<<"BROADCAST STARTED!";
    timer->start(500);
}

void ConnectorWorker::run(int N, QByteArray command){
    qDebug()<<N<<" "<<(int)command[5]<<(int)command[6];
    udpSocket->writeDatagram(command,QHostAddress(numIP[N]),3001);
}

void ConnectorWorker::udpBroadcastRequestIP()
{
    qDebug() << "ENTERED BROADCASTING with state" << QThread::currentThread();
    qDebug()<<udpSocket->bytesAvailable();

    QByteArray datagram = "req";

    udpSocket->writeDatagram(datagram,QHostAddress::Broadcast, 3001);

}

void ConnectorWorker::udpProcessPendingDatagrams()
{
      qDebug()<<"DATAGRAM!";
      QByteArray datagram;
      QHostAddress *robotAddress = new QHostAddress();
      while (udpSocket->hasPendingDatagrams()) {

          datagram.resize(udpSocket->pendingDatagramSize());
          udpSocket->readDatagram(datagram.data(), datagram.size(),robotAddress);
          QString str(datagram);

          QStringList lst = str.split(' ');
          if (!lst[0].compare("mac"))
          {
              //macList.cont
            if (!macList.contains(lst[1]))
            {
                //addrMap[lst[1]] = connectedRobots++;
                macList.push_back(lst[1]);
                macIP[lst[1]] = robotAddress->toString();
                emit robotAdded(lst[1]);
            }
//            datagram = (QString("num ")+QString::number(addrMap[lst[1]])).toUtf8();
//            udpSocket->writeDatagram(datagram,*robotAddress,3001);
          }
      }

}
