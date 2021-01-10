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
                                    {QString("@DOWNLOAD"), ParseInputOutput::DownloadFile},
                                    {QString("@UPLOAD"), ParseInputOutput::UploadFile},
                                    {QString("@RATE"), ParseInputOutput::Rate}
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
        auto tmp = *(ClientThread::userEmail) = msg.split(QRegExp("(\\ )")).toVector()[0];

    }
    /* afisam mesajul primit */
    std::cout<<"[client]Mesajul primit este:"<< msgc<<std::endl;
    fflush(stdout);
    return LoginResult;
}

bool ParseInputOutput::Rate(QString msg, int sd)
{
    int rating=0;
    ParseInputOutput::lastJob = RATE_JOB;
    char mesaj[1001];
    memset(mesaj, 0, 1000);
    QStringList args = msg.split(QRegExp("(\\ )"));
    if(args.length()<2) return false;
        // doar verificare
        int id_carte = args[1].toInt();
        if (read (sd, mesaj, 1000) < 0)
        {
            perror ("[client]Eroare la read() de la server.\n");
            return errno;
        }
        QString tmpMesage(mesaj);
        QStringList parsedMsg = tmpMesage.split(QRegExp("(\\ )"));

        ClientThread::userRating = parsedMsg[0].toInt();
        ClientThread::currentRating = parsedMsg[1].toDouble();
        qDebug()<<tmpMesage;
        return true;

//    return false;
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
    return 1;
}

bool ParseInputOutput::DownloadFile(QString msg, int sd)
{
    int downloadSize = 0;
    int totalSize=0;
    lastJob = DOWNLOAD_JOB;
    if (read (sd, &downloadSize, sizeof(int)) < 0)
    {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
    }
    unsigned char* fileBuffer;
    try
    {
        fileBuffer = new  unsigned char[downloadSize+1];
    }

    catch(std::bad_alloc& be)
    {
        qDebug()<<be.what()<<Qt::endl;
        //n-are memorie, mai incearca sau forteaza un crash cu mesaj
    }
    int received = 0;
    totalSize = downloadSize;
    int index = 0;
    while(downloadSize>0)
    {
        if(downloadSize <= 1499)
        {
            int a=5;
        }
        unsigned char pachet[1501];

        if ((received = read (sd, pachet, sizeof(unsigned char)*std::min(downloadSize, 1499))) < 0)
        {
                perror ("[client]Eroare la read() de la server.\n");
                return errno;
        }

        downloadSize-= received;
        memcpy(fileBuffer+index,pachet, received*sizeof(unsigned char));
        index+= received;
    }

    Transfer::PlaceFile(fileBuffer, totalSize);


    delete[] fileBuffer;
    return 1;
}

bool ParseInputOutput::UploadFile(QString msg, int sd)
{
    QString path = *(Transfer::uploadFilePath);
    std::ifstream f(path.toStdString(), std::ios::in|std::ios::binary);
    lastJob = UPLOAD_JOB;
    int upload_size = Transfer::GetFileSize(path);
    unsigned char* fileContent;
    try
    {
        fileContent = new unsigned char[upload_size+1];
    }
     catch (std::bad_alloc& be)
    {
        std::cout<<be.what()<<std::endl;
    }
    f.read((char*)fileContent, upload_size);
    write(sd, &upload_size, sizeof(upload_size));
    int index = 0;
    while(upload_size>0)
    {
       int received = write(sd, fileContent + index, (std::min(upload_size, 1499))*sizeof(unsigned char)); //needs work

       upload_size-=received;
       if(upload_size<= 1499)
       {
           int a= 10;
       }
       index += received;
    }
    delete[] fileContent;
    return 1;
}
