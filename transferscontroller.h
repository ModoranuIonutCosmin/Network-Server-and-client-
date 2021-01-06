#ifndef TRANSFERSCONTROLLER_H
#define TRANSFERSCONTROLLER_H
#include <QString>
#include <fstream>
class TransfersController
{
public:
    TransfersController();
    static int GetFileSize(QString string);
};

#endif // TRANSFERSCONTROLLER_H
