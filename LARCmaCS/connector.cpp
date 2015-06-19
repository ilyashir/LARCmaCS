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


    dat[0]='<';
    dat[1]='b';
    dat[2]='r';
    dat[3]='o';
    dat[4]='a';
    dat[5]='d';
    dat[6]=' ';

    dat[10]='c';
    dat[11]='>';

    //-----SERIALPORT-----
    QStringList portList;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (int i=0;i<ports.size();++i)
        portList.append(ports[i].portName());
    emit sendPortList(portList);
    //-----SERIALPORT-----

    udpSocket = new QUdpSocket(this);
    if (udpSocket->bind(UDP_ADDR, 3000))
        qDebug()<<"UDP OK!";
    else
        qDebug()<<"UDP FAIL!"<<udpSocket->errorString();

    connectedAllSocketsFlag = false;
    curRuleArray = new char[4 * 7]; // FIXME!

    gotPacketsNum = 0;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(udpBroadcastRequestIP()));
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(udpProcessPendingDatagrams()));

    qDebug()<<"INIT CONNECTOR OK";
}

void ConnectorWorker::openPort(QString pName)
{
    //<SERIALPORT>
    qDebug()<<pName;
    port = new QSerialPort(this);
    connect(port,SIGNAL(readyRead()),this,SLOT(readPort()));
    port->setPortName(pName);
    if (port->open(QIODevice::ReadWrite))
    {
        port->setBaudRate(QSerialPort::Baud115200);
        port->setDataBits(QSerialPort::Data8);
        port->setFlowControl(QSerialPort::NoFlowControl);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);
        qDebug()<<"PORT OPENED!";
    }
    else
        qDebug()<<"PORT ERROR!";
    //</SERIALPORT>
}


void ConnectorWorker::readPort()
{
    QString str;
    while(port->canReadLine())
    {
        str = port->readLine().left(5);
        qDebug()<<str;
        //str = str.tri
        if (str.contains("bro"))
        {
            if (!macList.contains(str))
            {
                //addrMap[lst[1]] = connectedRobots++;
                macList.push_back(str);
                emit robotAdded(str);
            }
        }
        //qDebug()<<port->readLine();
    }
}

void ConnectorWorker::receiveMacArray(QString * macArray)
{
    for (int i=0;i<12;++i)
    {
        qDebug()<<macArray[i];
        if (macArray[i].compare(""))//if robot exists
        {
            if (macArray[i].contains("bro")) //if it's arduino
                numIP[i+1] = macArray[i];
            else
                numIP[i+1] = macIP[macArray[i]]; //if it's TRIK
        }
    }
    qDebug()<<numIP;
    connectedAllSocketsFlag = true;
}

void ConnectorWorker::stopBroadcast()
{
    qDebug()<<"BROADCAST STOPPED!";
    timer->stop();


}

void ConnectorWorker::startBroadcast()
{
    qDebug()<<"BROADCAST STARTED!";
    timer->start(500);
}

void ConnectorWorker::run(int N, QByteArray command){
    //qDebug()<<N<<" "<<(int)command[5]<<(int)command[6];
    if (numIP[N].contains("bro"))   //if the packet is for arduino
    {
        if (port->isOpen())
        {

//            QByteArray str;
//            str.append('<');
//            str.append(numIP[N].toUtf8());
//            str.append(' ');
//            //QString str = QString("<")+ numIP[N] + QString(" ");
//            //qDebug()<<command.mid(5,3).size();
//            str.append(command.mid(5,3));
//            str.append("c>",2);
//            qDebug()<<str.size()<<" "<<(int)str[10];
            dat[7] = command[5];
            dat[8] = command[6];
            dat[9] = command[7];
            qDebug()<<(int)dat[7]<<" "<<(int)dat[8]<<" "<<(int)dat[9]<<" "<<dat[10];
            port->write(dat,12);
        }

    }
    else                            //if the packet is for TRIK
        udpSocket->writeDatagram(command,QHostAddress(numIP[N]),3001);
}

void ConnectorWorker::udpBroadcastRequestIP()
{
    qDebug() << "ENTERED BROADCASTING with state" << QThread::currentThread();
    qDebug()<<udpSocket->bytesAvailable();

    QByteArray datagram = "req";

    udpSocket->writeDatagram(datagram,QHostAddress::Broadcast, 3001);
    if(port->isOpen())
    {
        char * ard_broad = "<broad 123b>";
        port->write(ard_broad,12);

    }

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
