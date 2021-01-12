#include "connection.h"

int Connection::IDCurrent = 0;
Connection::Connection()
{

}

Connection::Connection(int cd, sockaddr adresaIP, int length)
{
    this->cd =cd;
    this->adresaIP = adresaIP;
    this->length = length;
}

Connection::Connection(const Connection &other)
{
    this->ID=other.ID;
    this->IDCurrent = other.IDCurrent;
    this->adresaIP = other.adresaIP;
    this->cd = other.cd;
    this->email = other.email;
    this->length = other.length;

}

void Connection::operator=(const Connection &other)
{
    this->ID=other.ID;
    this->IDCurrent = other.IDCurrent;
    this->adresaIP = other.adresaIP;
    this->cd = other.cd;
    this->email = other.email;
    this->length = other.length;
}


