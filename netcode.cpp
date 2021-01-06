#include "netcode.h"
std::map<QString, std::function<bool(QString, int)>>
                                  NetCODE::functii
                                  =
                                {
                                    {QString("@LOGIN"), NetCODE::Login},
                                    {QString("@SEARCH"), NetCODE::Search},
                                    {QString("@DOWNLOAD"), NetCODE::Download}
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

    if(SQLController::ExistsRecord(SQLController::DBTabs::USERS, fields, values))
    {
        qDebug()<<"Access granted for client with cd="<<clientSD;
        updateConnectionData(clientSD, values[0]);
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
    QString sendString= "";
    for(auto& book : books)
    {
        QString atom = book.title+'|'+book.author+'|'+book.genre +'|' +book.ISBN +'|' +QString::number(book.id_carte) +'|';
        sendString+= atom +'*';
    }
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
    char* fileContent;
    try
    {
        fileContent = new char[download_size];
    }
     catch (std::bad_alloc& re)
    {
        std::cout<<re.what()<<std::endl;
    }
    f.read(fileContent, download_size);

    write(cd, &download_size, sizeof(download_size));
    write(cd, fileContent, download_size*sizeof(unsigned char)); //needs works
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

bool NetCODE::updateConnectionData(int cd, QString& email)
{
    connectionsCS.lock();
    for(auto& conn : *instanta->connections)
    {
        if(conn.cd == cd)
        {
            conn.email = email;
            connectionsCS.unlock();
            return 1;
        }
    }
    connectionsCS.unlock();
    return 0;
}


