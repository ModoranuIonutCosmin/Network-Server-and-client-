#include "transferscontroller.h"

TransfersController::TransfersController()
{

}

int TransfersController::GetFileSize(QString string)
{
    std::ifstream f(string.toStdString(), std::ios_base::binary|std::ios_base::ate);
    return f.tellg();
}

void TransfersController::PlaceFile(const unsigned  char* buffer, int writeLen, QString pathAndName)
{
    std::ofstream f(pathAndName.toStdString(), std::ios::out| std::ios::binary);

//    int writeLen = strlen(buffer);
    try
    {
        f.write((char*)buffer, writeLen);
    }
    catch (std::runtime_error& re)
    {
       qDebug()<<re.what()<<Qt::endl;
       fflush(stdout);
    }

    f.close();
}
