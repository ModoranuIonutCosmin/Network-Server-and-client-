#include "clienthandlingthread.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <QThread>
#include <QCoreApplication>

ClientHandlingThread::ClientHandlingThread(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(HandleClient()));
    connect(this, SIGNAL(finished()), this, SLOT(CleanUP()));
    timer->start(0);
}

ClientHandlingThread::ClientHandlingThread(int sd, int cd, struct sockaddr addr)
{
    this->sd = sd;
    this->cd = cd;
    this->addr = addr;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(HandleClient()));
    timer->start(0);
}

int ClientHandlingThread::HandleClient()
{
    long len = 0;
    char * buffer;
    long addr = 0;

    addr = (long)((struct sockaddr_in *)&addr)->sin_addr.s_addr;
    buffer = (char *)malloc((1001)*sizeof(char));
    buffer[len] = 0;
    bzero(buffer, 1000);

    /* read message */
    std::cout<<"Ajung aici cu len = "<<len;
    fflush(stdout);
    if(read(cd, buffer, 1000) > 0)
    {
        std::cout<<buffer<<std::endl;
        NetCODE::ParseMessage(QString(buffer), cd);
        free(buffer);

    }
    else
    {
        /* close socket and clean up */
        std::cout<<"Closed already";
        fflush(stdout);
        close(cd);
        free(buffer);
        NetCODE::removeConnection(cd);
//        timer->stop();
        emit finished();
    }


    return 0;
}

int ClientHandlingThread::CleanUP()
{
    timer->stop();
    return 1;

}
