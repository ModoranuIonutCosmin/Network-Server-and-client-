#include "transfer.h"
std::unique_ptr<QString> Transfer::browsePath = std::make_unique<QString>(" ");
std::unique_ptr<QString> Transfer::uploadFilePath = std::make_unique<QString>("");
QMutex Transfer::transferProtect;
Transfer::Transfer()
{

}

void Transfer::PlaceFile(const unsigned char* buffer, int writeLen)
{
    Transfer::transferProtect.lock();
    std::ofstream f((*browsePath).toStdString(), std::ios::out| std::ios::binary);
    Transfer::transferProtect.unlock();
//    int writeLen = strlen(buffer);
    try
    {
        f.write((char*) &buffer[0], writeLen);
    }
    catch (std::runtime_error& re)
    {
       qDebug()<<re.what()<<Qt::endl;
       fflush(stdout);
    }

    f.close();
}

int Transfer::GetFileSize(QString string)
{

        std::ifstream f(string.toStdString(), std::ios_base::binary|std::ios_base::ate);
        return f.tellg();
}
