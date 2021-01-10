#ifndef NETCODE_H
#define NETCODE_H
#include <QString>
#include <map>
#include <functional>
#include <QMutex>
#include <QtConcurrent/QtConcurrent>
#include "sqlcontroller.h"
#include "connection.h"
#include "stringhelpers.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <fstream>
#include <QPair>
#include "transferscontroller.h"

class NetCODE
{
public:
    static QMutex connectionsCS;

    static std::map<QString, std::function<bool(QString, int)>> functii;
    NetCODE();
    static void ParseMessage(QString, int);
    static bool Login(QString, int);
    static bool Search(QString, int);
    static bool Download(QString, int);
    static bool Upload(QString, int);
    static bool Rate(QString, int);
    static bool addConnection(Connection con);
    static int GetIDFromCD(int cd);
    static void removeConnection(int cd);
    static bool updateConnectionData(int cd, QString& email, int id);
    static NetCODE* instanta ;
public: //private:
     static std::unique_ptr<QVector<Connection>> connections;
};

#endif // NETCODE_H
