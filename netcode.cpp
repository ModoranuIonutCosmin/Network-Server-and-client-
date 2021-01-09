#include "netcode.h"
std::map<QString, std::function<bool(QString, int)>>
                                  NetCODE::functii
                                  =
                                {
                                    {QString("@LOGIN"), NetCODE::Login},
                                    {QString("@SEARCH"), NetCODE::Search},
                                    {QString("@DOWNLOAD"), NetCODE::Download},
                                    {QString("@UPLOAD"), NetCODE::Upload}
                                };
QMutex NetCODE::connectionsCS;
NetCODE* NetCODE::instanta = nullptr;
std::unique_ptr<QVector<Connection>> NetCODE::connections= std::make_unique<QVector<Connection>>();

NetCODE::NetCODE()
{
    //singleton pattern
    if(instanta == nullptr)
    {
        instanta = this;
    }
}

void NetCODE::ParseMessage(QString message, int clientSD)
{
    for(auto const& command : functii)
    {
        if(message.left(command.first.length()) == command.first)
        {
            command.second(message.mid(command.first.length()+1), clientSD);

            break;
        }
    }
}

bool NetCODE::Login(QString args, int clientSD)
{
    qDebug()<<"attempting to login"<<clientSD;
    QVector<QString> fields {"email", "authHash"};
    QVector<QString> values = StringHelpers::Tokenize(args);
    int userID = -1;
    if((userID = SQLController::ExistsRecord(SQLController::DBTabs::USERS, fields, values))>=0)
    {
        qDebug()<<"Access granted for client with cd="<<clientSD;
        updateConnectionData(clientSD, values[0], userID);
        write(clientSD, "Authorized", 1000);
        return 1;
    }
    else
    {
        write(clientSD, "LOGFAIL", 1000);
    }
    return 0;
}

bool NetCODE::Search(QString args, int cd)
{
    QRegExp rx("(\\|)");
    QStringList fields = args.split(rx);
    auto books = SQLController::GetBooksList(fields.toVector());
    QString sendString= Book::DoListAsMessage(books);
    qDebug()<<sendString<<Qt::endl;
    write(cd, sendString.toStdString().c_str(), 1000);
    return 1;

}

bool NetCODE::Download(QString msg, int cd)
{

    int id_carte=msg.toInt(); //tbc on expansion!
    QString fileName ="storage/" + SQLController::GetFilePath(id_carte);

    std::ifstream f(fileName.toStdString(), std::ios::in|std::ios::binary);

    int download_size = TransfersController::GetFileSize(fileName);
    unsigned char* fileContent;
    try
    {
        fileContent = new unsigned char[download_size + 1];
    }
    catch (std::bad_alloc& be)
    {
        std::cout<<be.what()<<std::endl;
    }
    f.read((char*)fileContent, download_size);

    write(cd, &download_size, sizeof(download_size));
    int index = 0;
    while(download_size>0)
    {
        int received = write(cd, fileContent + index, (std::min(download_size, 1499))*sizeof(char)); //needs work

        download_size-=received;
        if(download_size<= 1499)
        {
            int a= 10;
        }
        index += received;
    }

    delete[] fileContent;
    return 1;
}

bool NetCODE::Upload(QString args, int cd)
{
    int uploadSize = 0;
    Book b = Book::DoMessageAsBook(args.split(QRegExp("(\\ )")).toVector()[0]);


    if (read (cd, &uploadSize, sizeof(int)) < 0)
    {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
    }
    unsigned char* fileBuffer;
    try
    {
        fileBuffer = new  unsigned char[uploadSize+1];
    }

    catch(std::bad_alloc& be)
    {
        qDebug()<<be.what()<<Qt::endl;
        return false;
        //n-are memorie, mai incearca sau forteaza un crash cu mesaj
    }
    int received = 0;
    int totalSize = uploadSize;
    int index = 0;
    while(uploadSize>0)
    {
        if(uploadSize <= 1499)
        {
            int a=5;
        }
        unsigned char pachet[1501];

        if ((received = read (cd, pachet, sizeof(unsigned char)*std::min(uploadSize, 1499))) < 0)
        {
                perror ("[client]Eroare la read() de la server.\n");
                return errno;
        }

        uploadSize-= received;
        memcpy(fileBuffer+index,pachet, received*sizeof(unsigned char));
        index+= received;
    }

    int newID = SQLController::RegisterBook(b);
    TransfersController::PlaceFile(fileBuffer, totalSize, "storage/" +b.title.replace(" ","_")+ QString::number(newID)+".pdf");


    delete[] fileBuffer;
    return 1;
}

bool NetCODE::addConnection(Connection con)
{
    QMutexLocker mtx(&connectionsCS);
        connections->append(con);
        mtx.unlock();
        return 1;
}

void NetCODE::removeConnection(int cd)
{
    NetCODE::connectionsCS.lock();
    for(auto i=0;  i< (*connections).size(); i++)
    {
        if((*connections)[i].cd == cd)
        {

           (*connections).remove(i);
           qDebug()<<"\nSterg conn cu cd = "<<cd;
           fflush(stdout);
        }
    }
    NetCODE::connectionsCS.unlock();
}

bool NetCODE::updateConnectionData(int cd, QString& email, int id)
{
    connectionsCS.lock();
    for(auto& conn : *instanta->connections)
    {
        if(conn.cd == cd)
        {
            conn.email = email;
            conn.ID = id;
            connectionsCS.unlock();
            return 1;
        }
    }
    connectionsCS.unlock();
    return 0;
}


