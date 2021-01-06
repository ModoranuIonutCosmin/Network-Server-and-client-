#include "networkserver.h"

/* portul folosit */
#define PORT 2024
extern int errno;


NetworkServer::NetworkServer(QObject *parent) : QObject(parent)
{
    //StartServer();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ListenCon()));
    timer->start(0);
}


//needs formatting!!!!<>
int NetworkServer::StartServer()
{

    struct sockaddr_in address;



    /* create socket */
        this->sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock <= 0)
        {
            fprintf(stderr, ": error: cannot create socket\n");
            return -3;
        }

        /* bind socket to port */
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
        int enable = 1;

        while (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
        {
            std::cout<<"Attempting to bind again!";
            fflush(stdout);
            QThread::sleep(3);
        }

        /* listen on port */
        if (listen(sock, 500) < 0)
        {

            return -5;
        }
        int val = 1;
        setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(int));
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
    connection = new Connection();
    connection->email="";
    connection->role=-1;
    connection->cd = accept(this->sock, (struct sockaddr *) &(connection->adresaIP), (socklen_t *) &(connection->length));
    if(errno == 22)
    {
        std::cout<<"oops";
        fflush(stdout);
    }
    if (connection->cd <= 0)
    {
       delete connection;
         std::cout<<"TRying"<<sock<<std::endl;
    }
    else
    {
        /* start a new thread but do not wait for it */
        std::cout<<"Avem conexiune noua!!!!!"<<std::endl;
        std::cout<<"Pana acum avem urmatoarele conexiuni"<<std::endl;
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
        connect(worker, SIGNAL(NotifyUI(QString)), this, SLOT(RelayText(QString)), Qt::QueuedConnection);
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
