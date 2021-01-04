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
        };
bool ParseInputOutput::GetResults(QString msg, int sd)
{
    char msgc[1000];
    lastJob = AQUIRE_JOB;
    if (write (sd, (ClientThread::pendingMessage)->toStdString().c_str(), 1000) <= 0)
    {
        perror ("[client]Eroare la write() spre server.\n");
        return errno;
    }
    /* citirea raspunsului dat de server
           (apel blocant pina cind serverul raspunde) */
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
    if (write (sd, (ClientThread::pendingMessage)->toStdString().c_str(), 1000) <= 0)
    {
        perror ("[client]Eroare la write() spre server.\n");
        return errno;
    }
    /* citirea raspunsului dat de server
           (apel blocant pina cind serverul raspunde) */
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
