#include "clientthread.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <QCoreApplication>
#define READ_SIZE 12000
std::unique_ptr<QString> ClientThread::pendingMessage = std::make_unique<QString>(" ");
std::mutex ClientThread::messageProtect;
std::unique_ptr<QString> ClientThread::userEmail = std::make_unique<QString>("");
double ClientThread::currentRating = -1;
int ClientThread::ServerLive = 1;
int ClientThread::userRating = -1;

ClientThread::ClientThread(QObject *parent) : QObject(parent)
{
    if(InitializeClient()<0) return;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(HandleClient()));
    timer->start(0);

}

int ClientThread::InitializeClient()
{

    struct sockaddr_in address;	// structura folosita pentru conectare
    char argv[10][256]={" ", "127.0.0.1", "2024"};


    /* create socket */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock <= 0)
    {
        fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
        return -3;
    }

    /* connect to server */
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));
    address.sin_addr.s_addr = inet_addr(argv[1]);

    if (::connect(sock, (struct sockaddr *)&address, sizeof(address)))
    {
        fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
        fflush(stdout);
        return -5;
    }
    return 0;
}

void ClientThread::DoCleanup()
{
    switch((ParseInputOutput::lastJob))
    {
        case LOGIN_JOB:
        if(ParseInputOutput::LoginResult)
        {
            emit loginSuccesful();
        }
        else
        {
            emit loginFailed();
        }
        break;
        case AQUIRE_JOB:
             emit sendBooks(ParseInputOutput::result);
        break;
        case RATE_JOB:
            emit ModifyRating(ClientThread::userRating, ClientThread::currentRating);
        break;
            case RECOMMEND_JOB:
            emit sendBooksRec(ParseInputOutput::result);
        break;
    default:
        break;
    }
}

int ClientThread::HandleClient()
{
    char msg[READ_SIZE];
    /* citirea mesajului */
    bzero (msg, READ_SIZE);
//    printf ("[client]Introduceti un nume: ");
//    fflush (stdout);
    if(*pendingMessage == " ") {
                                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                return 0;
                               }
    if (write (sock, (ClientThread::pendingMessage)->toStdString().c_str(), READ_SIZE) <= 0) \
        //changed sign
    {
        qDebug()<<"Server closed"<<Qt::endl;
        fflush(stdout);
        close(sock);
        emit finished();
        return errno;
    }

    /* citirea raspunsului dat de server
           (apel blocant pina cind serverul raspunde) */
    ParseInputOutput::Parse(pendingMessage, sock); //parseaza si foloseste inputul primit

    DoCleanup();

    QCoreApplication::processEvents();
    if(ServerLive == 0)
        emit finished();
    fflush(stdout);

    return 1;
}
