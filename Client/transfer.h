#ifndef TRANSFER_H
#define TRANSFER_H

#include <fstream>
#include <QString>
#include <QMutex>
#include <memory>
#include <QtDebug>
class Transfer
{
public:

    Transfer();
    static QMutex transferProtect;
    static std::unique_ptr<QString> browsePath;
    static void PlaceFile(const char*, int);
};

#endif // TRANSFER_H
