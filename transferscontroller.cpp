#include "transferscontroller.h"

TransfersController::TransfersController()
{

}

int TransfersController::GetFileSize(QString string)
{
    std::ifstream f(string.toStdString(), std::ios_base::binary|std::ios_base::ate);
    return f.tellg();
}
