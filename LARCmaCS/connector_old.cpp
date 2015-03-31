#include <stdlib.h>
#include <iostream>

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

    connectedSockets=0;
    filename = "numMAC.txt"; 

    ipFile = new QFile(filename);

//    QTextStream fileIn(ipFile);

//    while (!fileIn.atEnd()) {
//        QString line = fileIn.readLine();
//        int robotNum = (line.split(" ").value(0)).toInt();
//        QString mac = line.split(" ").value(1);
//        enabledRobotsSet.insert(robotNum);
//    }
    enabledRobotsSet.insert(1);
    enabledRobotsSet.insert(2);
    enabledRobotsSet.insert(3);
    udpSocket = new QUdpSocket(this);
    if (udpSocket->bind(UDP_ADDR, 3000))
        qDebug()<<"UDP OK!";
    else
        qDebug()<<"UDP FAIL!"<<udpSocket->errorString();

    //udpSocket->bind(QHostAddress::LocalHost, 3001);

    tcpSentCount = 0;
    tcpPort = 2000;
    connectedAllSocketsFlag = false;

    curRuleArray = new double[4 * 7]; // (временно) 5 - количество строк матрицы, 5 - длина каждой строки матрицы,



    gotPacketsNum = 0;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(udpBroadcastRequestIP()));
    //timer->start(500);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(udpProcessPendingDatagrams()));
    connect(this, SIGNAL(receivedAddresses(QByteArray)), this, SLOT(getStringAddresses(QByteArray)));
    connect(this, SIGNAL(gotStringAddresses(QByteArray)), this, SLOT(addIpToMap(QByteArray)));
    connect(this, SIGNAL(allNeededRobotsEnabled()), this, SLOT(doTcpWork()));
    qDebug()<<"INIT CONNECTOR OK";
}

void ConnectorWorker::stopBroadcast()
{
    qDebug()<<"BROADCAST STOPPED!";
    timer->stop();
   // if (curEnabledRobotsSet.size()>0)

}

void ConnectorWorker::startBroadcast()
{
    qDebug()<<"BROADCAST STARTED!";
    timer->start(500);
}

void ConnectorWorker::run(double *gotRuleArray) {
    qDebug() << "Started connector.worker.run() in thread" << QThread::currentThread();

    gotPacketsNum++;
    qDebug() << "Num CONNECTOR:" << gotPacketsNum;

    memcpy(curRuleArray, gotRuleArray, 4 * 7 * sizeof(double));

    if (connectedAllSocketsFlag)
        doTcpWork();
}

void ConnectorWorker::udpBroadcastRequestIP()
{
    qDebug() << "ENTERED BROADCASTING with state" << QThread::currentThread();
    qDebug()<<udpSocket->bytesAvailable();

    QByteArray datagram = "requestIP";

    //for (int i = 0; i < 1; i++) {
        udpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress("192.168.43.255"), 3000);
    //}
}

void ConnectorWorker::udpProcessPendingDatagrams()
{
    qDebug() << "ENTERED PROCESSING";

    while (udpSocket->hasPendingDatagrams()) {
        qDebug() << "Processing() from thread" << QThread::currentThread();
        qDebug() << "New pending datagram";

        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        qDebug() << "Received datagram: " << datagram.data() << "of size" << datagram.size();

        if (datagram.size() == 10) {
            qDebug() << "Got message of 10 symbols";
            getStringAddresses(datagram);
        }
    }
}

// Get string MAC and IP datagram from byte MAC and IP of a specific robot
// addressDatagram - strictly 10 bytes: first 6 bytes - MAC, next 4 - IP
void ConnectorWorker::getStringAddresses(QByteArray byteAddressDatagram)
{
    QByteArray macByte;
    QString ipString;

    qDebug() << "This datagram is address: " << byteAddressDatagram.data();

    // Casting to unsigned char because got unsigned MAC and IP but QByteArray.at() gives signed char
    for (int i = 0; i < 6; i++)
        macByte.append((unsigned char)byteAddressDatagram.at(i));

    for (int i = 6; i < 10; i++)
        ipString.append(QString::number((unsigned char)(byteAddressDatagram.at(i))) + ".");
    ipString = ipString.mid(0, ipString.length() - 1);

    qDebug() << "IP with dots is" << ipString;

    QString macString = macByte.toHex();
    qDebug() << "MAC is" << macString;


    QByteArray stringAddressDatagram;
    stringAddressDatagram.append(macString + " " + ipString);

    gotStringAddresses(stringAddressDatagram);
}

void ConnectorWorker::addIpToMap(QByteArray datagram)
{
    QString macAndIp = QString::fromUtf8(datagram); // "macAddress ipAddress" like string
    QString macAddr = macAndIp.split(" ").value(0);
    QString ipAddr = macAndIp.split(" ").value(1);

    bool dFound = 0;

    if (ipFile->open(QIODevice::ReadWrite)) {
        QTextStream fileIn(ipFile);

        while (!fileIn.atEnd()) {
            QString line = fileIn.readLine();
            int robotNum = (line.split(" ").value(0)).toInt();
            QString mac = line.split(" ").value(1);
            qDebug()<<"--------------MAC FROM FILE: "<<mac;
            if (!mac.compare(macAddr) && (enabledRobotsSet.find(robotNum) != enabledRobotsSet.end())
                    && (curEnabledRobotsSet.find(robotNum) == curEnabledRobotsSet.end())) {
                qDebug() << "Now will be added: robotNum:" << robotNum << "macAddr" << macAddr << "IPAddr:" << ipAddr;

                robotAddrMap.insert(std::pair<int const, QString>(robotNum, ipAddr));

                curEnabledRobotsSet.insert(robotNum);

                emit robotAdded(QString::number(robotNum)+QString(" ")+macAddr);
                dFound = 1;
                break;
            }
        }
        ipFile->close();
    }

    printRobotAddrMap();

    if (dFound)
        qDebug() << "Got MAC is in numMAC file, OK";
    else
        qDebug() << "Got MAC is not in numMAC file";


    qDebug() << "Current robots with their IPs added are:";
    printSet(curEnabledRobotsSet);
    qDebug() << "All robots to have their IPs added are:";
    printSet(enabledRobotsSet);

    if (curEnabledRobotsSet == enabledRobotsSet) {
        qDebug() << "Got all enabled robots' IPs";

        timer->stop();
        emit allNeededRobotsEnabled();
        initTcpConnections();
    }
    else
        qDebug() << "Got not all enabled robot's IPs";
}

void ConnectorWorker::initTcpConnections()
{
    qDebug() << "Initing tcp";
    for(map<int const, QString>::const_iterator robotAddrMapIter = robotAddrMap.begin(); robotAddrMapIter != robotAddrMap.end(); robotAddrMapIter++) {
        QTcpSocket *newSocket = new QTcpSocket();
        connect(newSocket,SIGNAL(connected()),this,SLOT(tcpConnected()));
        newSocket->connectToHost(robotAddrMapIter->second, tcpPort);
        socketVector.push_back(newSocket);
    }
}

void ConnectorWorker::tcpConnected()
{
    if (++connectedSockets == curEnabledRobotsSet.size())
    {

        connectedAllSocketsFlag = true;
    }
}

void ConnectorWorker::doTcpWork()
{

    sendRuleToAllSockets();
    qDebug()<<"TCP SENDING";
}

bool ConnectorWorker::checkAllSockets()
{
    vector<QTcpSocket *>::const_iterator iter;
    int i;
    for(iter = socketVector.begin(), i = 0; iter != socketVector.end() && i < socketVector.size(); iter++, i++) {
        //(*iter)->waitForConnected(2000); // timeout 2s for example
        //(QTcpSocket*)(*iter)->wa


        if ((*iter)->state() != QAbstractSocket::ConnectedState) {
            qDebug() << "Bad socket state on socket with number in map" << i;
            qDebug() << "State is:" << (*iter)->state();
            return false;
        }
        else
            qDebug() << "Connected socket state!";
    }

    return true;
}

void ConnectorWorker::sendRuleToAllSockets()
{
    qDebug() << "Started sending asynchroniously to all servers";
    int leftMotor, rightMotor, kicker, light;
    for (int j = 0; j < 4; j++) {
        if (curRuleArray[j] == 0)
            continue;
        else
         if (curRuleArray[j] == 1)
         {
            int RulNom=0;
            qDebug() << "About to send";
            for(vector<QTcpSocket *>::const_iterator iter = socketVector.begin(); iter != socketVector.end(); iter++) {
                RulNom++;
                if (curRuleArray[1 * 4 * (j + 1)]==RulNom || curRuleArray[1 * 4 * (j + 1)]==0)
                {
                    leftMotor = curRuleArray[2 * 4 * (j + 1)];
                    rightMotor = curRuleArray[3 * 4 * (j + 1)];
                    kicker = curRuleArray[4 * 4 * (j + 1)];
                    light = curRuleArray[5 * 4 * (j + 1)];

                    TcpSender *tcpSender = new TcpSender(*iter, leftMotor, rightMotor, kicker, light);
                    tcpSender->setAutoDelete(true);

                    connect(tcpSender, SIGNAL(taskDone()), this, SLOT(onTaskDone()));

                    QThreadPool *newPooledThread = QThreadPool::globalInstance();
                    newPooledThread->start(tcpSender);

                    qDebug() << QThreadPool::globalInstance()->activeThreadCount() << "pooled thread(s) started";
                }
            }
        }
    }
}

void ConnectorWorker::onTaskDone()
{
    qDebug() << "Some TcpSender task done";
    tcpSentCount++;

    qDebug() << "Had to send to" << enabledRobotsSet.size() << "robots";
    qDebug() << "Now sent to" << tcpSentCount << "robots";
    // неоч аккуратно, может быть равно при том, что посланы не все О_О, или еще как
    if (tcpSentCount == enabledRobotsSet.size()) {
        qDebug() << "All Tasks done!";
        tcpSentCount = 0;
        emit allTasksDone();
    }
}

void ConnectorWorker::printRobotAddrMap()
{
    qDebug() << "START PRINTING MAP";

    for(map<int const, QString>::const_iterator iter = robotAddrMap.begin(); iter != robotAddrMap.end(); iter++)
        qDebug() << iter->first << " => " << iter->second;

    qDebug() << "END PRINTING MAP";
}

void ConnectorWorker::printSet(std::set<int> givenSet)
{
    qDebug() << "START PRINTING SET";

    for(std::set<int>::const_iterator iter = givenSet.begin(); iter != givenSet.end(); iter++)
        qDebug() << *iter;

    qDebug() << "END PRINTING SET";
}

