#include "networkserver.h"

/* portul folosit */
#define PORT 2024
extern int errno;

std::unique_ptr<QString> NetworkServer::instructiune= std::make_unique<QString>("");
int NetworkServer::sock;
QMutex NetworkServer::instructionProtect;
NetworkServer::NetworkServer(QObject *parent) : QObject(parent)
{
    //StartServer();
//    signal(SIGHUP, CloseDown);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ListenCon()));
    timer->start(0);
}

void NetworkServer::CloseDown(int)
{
    close(sock);
}


//needs formatting!!!!<>
int NetworkServer::StartServer()
{

    struct sockaddr_in address;

    int val = 1;
    const struct linger opt = { .l_onoff = 1, .l_linger = 0 };


    fflush(stdout);
//    close(sock);


    /* create socket */
        this->sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock <= 0)
        {
            fprintf(stderr, ": error: cannot create socket\n");
            return -3;
        }
        int err1 = setsockopt(sock, SOL_SOCKET, SO_LINGER, &opt, sizeof(opt));
        int err2 = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,  &val, sizeof(val));
        int err3 = setsockopt(sock, SOL_SOCKET, SO_REUSEPORT,  &val, sizeof(val));
        perror(" ");
         //FA PORTUL SA FIE REFOLOSIBIL IMEDIAT (nu sunt riscuri de misdirectionare)


        /* bind socket to port */
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
        int enable = 1;

        while (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
        {
            std::cout<<"Attempting to bind again!";
            perror("");
            fflush(stdout);
            QThread::sleep(3);
        }

        /* listen on port */
        if (listen(sock, 32) < 0) //cat tin maxim in coada?
        {

            return -5;
        }

        printf(": ready and listening\n");



      return 0;
}

int NetworkServer::RelayText(QString text)
{
    emit OnMessageReceived(text);
    std::cout<<"Doing stuff 0101";
    return 43;
}

int NetworkServer::ListenCon()
{
    Connection * connection;


    fflush(stdout);
    /* accept incoming connections */
    int done = 0;
    QString string;
     instructionProtect.lock();
    if((string = *instructiune) == "SHUTDOWN")
    {

        for(auto& conn : *(NetCODE::connections))
        {
            close(conn.cd);
        }
        qDebug()<<"Server shuts down!";
        fflush(stdout);
        close(this->sock);
        instructionProtect.unlock();
        timer->stop();
        emit finished();
        return 1;
        done = 1;
    }
    if(done == 0) instructionProtect.unlock();
    connection = new Connection();
    connection->email="";
    connection->cd = accept(this->sock, (struct sockaddr *) &(connection->adresaIP), (socklen_t *) &(connection->length));
    if(errno == 22)
    {
        std::cout<<"oops";
        fflush(stdout);
    }
    if (connection->cd <= 0)
    {

         std::cout<<"Socket closed"<<sock<<std::endl;
    }
    else
    {
        /* start a new thread but do not wait for it */
        std::cout<<"Avem conexiune noua!!!!!"<<std::endl;
        std::cout<<"Pana acum avem urmatoarele conexiuni ca useri logati"<<std::endl;
        NetCODE::connectionsCS.lock();
        for(auto& conn : *(NetCODE::connections))
        {
            std::cout<<conn.email.toStdString()<<std::endl;
        }
        NetCODE::connectionsCS.unlock();
        Connection t = *connection;
        NetCODE::addConnection(t);
        fflush(stdout);
        QThread* Thread = new QThread;
        ClientHandlingThread* worker = new ClientHandlingThread(sock, connection->cd, connection->adresaIP);
        worker->moveToThread(Thread);

//        connect(this, SIGNAL(closeAll()), worker, SLOT(CleanUP()));
//        connect(worker, SIGNAL(NotifyUI(QString)), this, SLOT(RelayText(QString)), Qt::QueuedConnection);
        connect(Thread, SIGNAL(started()), worker, SLOT(HandleClient()));
        connect(worker, SIGNAL(finished()), Thread, SLOT(quit()));
        connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(Thread, SIGNAL(finished()), Thread, SLOT(deleteLater()));

        Thread->start();
        //leak
    }
    delete connection;

//    QCoreApplication::processEvents();
    return 1;
}

int NetworkServer::CloseDown()
{
//    close(sock);
//    this->timer->stop();
//    qDebug()<<"Server shuts down\n";
//    fflush(stdout);
//    emit closeAll();
//    emit finished();
}
