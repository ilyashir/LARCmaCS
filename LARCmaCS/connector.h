#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include <QFile>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>

#include <QtCore>
#include <QtNetwork>

using std::map;
using std::vector;
#include <Set>

struct TcpSender : QObject, QRunnable
{
    Q_OBJECT

public:
    QTcpSocket *socket;
    char leftMotor, rightMotor, kicker, light;
    // leftMotor: [-100, 100] range - backward / forward
    // rightMotor: -//-
    // kicker: 0 / 1 - off / on
    // light: 1 / 2 / 3 / 4 - off / green / orange / red

    explicit TcpSender(QTcpSocket *gotSocket, int gotLeftMotor, int gotRightMotor, int gotKicker, int gotLight)
    {
        socket = gotSocket;
        leftMotor = gotLeftMotor;
        rightMotor = gotRightMotor;
        kicker = gotKicker;
        light = gotLight;
    }

    void run()
    {
        QByteArray buffer;
        buffer.append(leftMotor);
        buffer.append(rightMotor);
        buffer.append(kicker);
        buffer.append(light);

        socket->write(buffer);

        qDebug() << "Written smth";

        emit taskDone();
    }

signals:
    void taskDone();
};

struct ConnectorWorker : QObject
{
    Q_OBJECT
public:
    ConnectorWorker(){}

    int shutdownconnector;
    double *curRuleArray;

    QString filename;
    QFile *ipFile;
    QUdpSocket *udpSocket;
    map<int const, QString> robotAddrMap;
    std::set<int> enabledRobotsSet, curEnabledRobotsSet;
    vector<int> portVector;
    vector<QTcpSocket *> socketVector;
    int tcpSentCount;
    int tcpPort;
    int connectedAllSocketsFlag;

    int gotPacketsNum;


signals:
    void receivedDatagram(QByteArray datagram);
    void receivedAddresses(QByteArray addressDatagram);
    void gotStringAddresses(QByteArray stringAddressDatagram);
    void allNeededRobotsEnabled();
    void allTasksDone();

public slots:
    void start();
    void stop();
    void run(double *ruleArray);
    void udpBroadcastRequestIP();
    void udpProcessPendingDatagrams();
    void getStringAddresses(QByteArray byteAddressDatagram);
    void addIpToMap(QByteArray stringAddressDatagram);
    void initTcpConnections();
    void doTcpWork();
    bool checkAllSockets();
    void sendRuleToAllSockets();
    void onTaskDone();

    void printRobotAddrMap();
    void printSet(std::set<int> givenSet);

private:
    void init();
};

struct Connector : QObject
{
    Q_OBJECT

public:
    ConnectorWorker worker;
    QThread thread;

    explicit Connector(){}
    ~Connector()
    {
        stop();
        thread.terminate();
        thread.wait(100);
    }

    void init()
    {

        worker.moveToThread(&thread);
        qDebug() << "Init connector ok";
        connect(this, SIGNAL(wstart()), &worker, SLOT(start()));
        connect(this, SIGNAL(wstop()), &worker, SLOT(stop()));
        connect(&thread, SIGNAL(finished()), &worker, SLOT(deleteLater()));
    }

    void start()
    {
        thread.start();
        thread.setPriority(QThread::HighestPriority);
        qDebug() << "Connector thread start";
        emit wstart();
    }

    void stop() { emit wstop(); }

signals:
    void wstart();
    void wstop();
};

#endif // CONNECTOR_H
