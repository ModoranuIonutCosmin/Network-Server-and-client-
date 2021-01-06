#include "transfer.h"
std::unique_ptr<QString> Transfer::browsePath = std::make_unique<QString>(" ");
QMutex Transfer::transferProtect;
Transfer::Transfer()
{

}

void Transfer::PlaceFile(const  char* buffer, int writeLen)
{
    Transfer::transferProtect.lock();
    std::ofstream f((*browsePath).toStdString(), std::ios::out| std::ios::binary);
    Transfer::transferProtect.unlock();
//    int writeLen = strlen(buffer);
    try
    {
        f.write(buffer, writeLen);
    }
    catch (std::runtime_error& re)
    {
       qDebug()<<re.what()<<Qt::endl;
       fflush(stdout);
    }

    f.close();
}
