#include "clientwindow.h"

#include <thread>
#include <future>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <QApplication>
#include "book.h"


/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;



int main(int argc, char *argv[])
{
    qRegisterMetaType<QVector<Book> >();
    QApplication a(argc, argv);

    ClientWindow w;
    w.show();
    a.exec();

    return 1;
}
