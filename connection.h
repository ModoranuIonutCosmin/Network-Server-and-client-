#ifndef CONNECTION_H
#define CONNECTION_H
#include <sys/socket.h>
#include <QString>

class Connection
{

public:
    Connection();
    Connection(int cd, sockaddr adresaIP, int length);
    Connection(const Connection& other);
    void operator=(const Connection& other);
    static int IDCurrent; //porneste cu 0 si scade cand pleaca un client
    QString email="";
    int ID;
    socklen_t length;
    sockaddr adresaIP;
    int cd;
};

#endif // CONNECTION_H
