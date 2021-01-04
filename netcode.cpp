#include "netcode.h"
std::map<QString, std::function<bool(QString, int)>>
                                  NetCODE::functii
                                  =
                                {
                                    {QString("@LOGIN"), NetCODE::Login},
                                    {QString("@SEARCH"), NetCODE::Search},
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
        QString atom = book.title+'|'+book.author+'|'+book.genre +'|' +book.ISBN;
        sendString+= atom +'*';
    }
    qDebug()<<sendString<<Qt::endl;
    write(cd, sendString.toStdString().c_str(), 1000);
    return 1;

}

bool NetCODE::addConnection(Connection con)
{
    QMutexLocker mtx(&connectionsCS);
        connections->append(con);
        mtx.unlock();
    return 1;
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


