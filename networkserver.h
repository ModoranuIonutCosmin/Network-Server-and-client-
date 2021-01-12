#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <QTimer>
#include <QMainWindow>
#include "netcode.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <future>
#include <iostream>
#include <QThread>
#include <QMutex>
#include <QAbstractEventDispatcher>
#include "clienthandlingthread.h"
#include <QCoreApplication>
class NetworkServer : public QObject
{
    Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = nullptr);
    static void CloseDown(int);
    static std::unique_ptr<QString> instructiune;
    static QMutex instructionProtect;
signals:
    void finished();
    void closeAll();
    void OnMessageReceived(QString text);

private slots:
    int StartServer();
    int RelayText(QString text);
    int ListenCon();
    int CloseDown();
private:
    QTimer* timer;

    static int sock;

};

#endif // NETWORKSERVER_H
