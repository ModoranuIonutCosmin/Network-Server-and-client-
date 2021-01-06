#include "parseinputoutput.h"

int ParseInputOutput::lastJob = 0;
QVector<Book> ParseInputOutput::result = {};
bool ParseInputOutput::LoginResult = false;

std::map<QString, std::function<bool(QString, int)>>
                                 ParseInputOutput::functii
                                  =
                                {
                                    {QString("@LOGIN"), ParseInputOutput::Login},
                                    {QString("@SEARCH"), ParseInputOutput::GetResults},
                                    {QString("@DOWNLOAD"), ParseInputOutput::DownloadFile}
        };
bool ParseInputOutput::GetResults(QString msg, int sd)
{
    char msgc[1000];
    lastJob = AQUIRE_JOB;

    if (read (sd, msgc, 1000) < 0)
    {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
    }

    /* afisam mesajul primit */
    std::cout<<"[client]Mesajul primit este:"<< msgc<<std::endl;
    fflush(stdout);
    QString msgC(msgc);
    result = (Book::ParseBookString(msgC));
    return true;
}

bool ParseInputOutput::Login(QString msg, int sd)
{
    char msgc[1000];
    lastJob = LOGIN_JOB;

    if (read (sd, msgc, 1000) < 0)
    {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
    }
    if(strstr(msgc, "Authorized") == msgc)
    {
        LoginResult = true;
    }
    /* afisam mesajul primit */
    std::cout<<"[client]Mesajul primit este:"<< msgc<<std::endl;
    fflush(stdout);
    return LoginResult;
}

ParseInputOutput::ParseInputOutput()
{

}

bool ParseInputOutput::Parse(std::unique_ptr<QString>& pendingMsg, int sd)
{
    qDebug()<<*pendingMsg<<" \n";
    result.clear();
    LoginResult=false;
    for(auto const& command : functii)
    {
        if(pendingMsg->left(command.first.length()) == command.first)
        {
            command.second(pendingMsg->mid(command.first.length()+1), sd);
            ClientThread::messageProtect.lock();
            *pendingMsg = " ";
            ClientThread::messageProtect.unlock();
            break;
        }
    }
    *pendingMsg = " ";
    qDebug()<<"OOPS";
    return 1;
}

bool ParseInputOutput::DownloadFile(QString msg, int sd)
{
    int downloadSize = 0;

    if (read (sd, &downloadSize, sizeof(int)) < 0)
    {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
    }
    char* fileBuffer;
    try
    {
        fileBuffer = new  char[downloadSize+1];
    }

    catch(std::bad_alloc& be)
    {
        qDebug()<<be.what()<<Qt::endl;
        //n-are memorie, mai incearca sau forteaza un crash cu mesaj
    }
    int received = 0;
    if ((received = read (sd, fileBuffer, sizeof(unsigned char)*downloadSize)) < 0)
    {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
    }

    Transfer::PlaceFile(fileBuffer, downloadSize);


    delete[] fileBuffer;
    return 1;
}
