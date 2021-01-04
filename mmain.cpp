#include "serverwindow.h"

#include <QApplication>

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <future>
#include <iostream>
#include <QThread>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWindow w;

    w.show();
    a.exec();

    return 0;
}
