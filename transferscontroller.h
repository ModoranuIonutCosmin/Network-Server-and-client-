#ifndef TRANSFERSCONTROLLER_H
#define TRANSFERSCONTROLLER_H
#include <QString>
#include <fstream>
#include <QtDebug>
class TransfersController
{
public:
    TransfersController();
    static int GetFileSize(QString string);
    static void PlaceFile(const unsigned  char* buffer, int writeLen, QString pathAndName);
};

#endif // TRANSFERSCONTROLLER_H
