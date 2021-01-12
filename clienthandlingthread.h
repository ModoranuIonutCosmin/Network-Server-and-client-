#ifndef CLIENTHANDLINGTHREAD_H
#define CLIENTHANDLINGTHREAD_H

#include <QObject>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <QThread>
#include <QTimer>
#include <QAbstractEventDispatcher>
#include "netcode.h"
class QThread;


class ClientHandlingThread : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandlingThread(QObject *parent = nullptr);
    explicit ClientHandlingThread(int sd, int cd, struct sockaddr addr);
signals:

    void NotifyUI(QString text);
    void finished();
    void OnNewMessage();
private slots:
    int HandleClient();
    int CleanUP();
private:
    int sd, cd;
    struct sockaddr addr;
    QTimer* timer;
};

#endif // CLIENTHANDLINGTHREAD_H
