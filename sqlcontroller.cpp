#include "sqlcontroller.h"

SQLController* SQLController::instance = nullptr;
bool SQLController::Initialized = false;
QSqlDatabase SQLController::db;
SQLController::SQLController()
{

}

bool SQLController::ExistsRecord(DBTabs table, QVector<QString> fields, QVector<QString> values)
{
    if(Initialized == false)
        Initialize();
    QString querryText = "SELECT 'AAA' FROM " + EnumHelpers::QtEnumToString(table) +" WHERE (";
    if(fields.length()!= values.length())
    {
        qDebug()<<"Bad stuff happening in SQL exists records";
        return 0;
    }
    for(int i=0; i<fields.length(); i++)
    {
        querryText +=fields[i] + "='" + values[i] + "' AND ";
    }
    querryText += "1=1)";
    QSqlQuery qry(db);
    qry.exec(querryText);
   if(qry.next())
   {
       qDebug()<<"Successful login";
       return 1;
   }
   return 0;
}

QVector<Book> SQLController::GetBooksList(QVector<QString> constraints)
{
    QVector<Book> books;
    const QVector<QString> fields = {"Titlu", "Autor", "Gen", "ISBN"};
    if(SQLController::Initialized == false)
        Initialize();
    for(int i=0; i<constraints.size(); i++)
    {
        if(constraints[i]==" ")
            constraints[i]="";
    }
    QString querryText = "SELECT Titlu,Autor,Gen,ISBN,id_carte FROM " + EnumHelpers::QtEnumToString(BOOKS) +" WHERE (";
    if(fields.length()!= constraints.length())
    {
        qDebug()<<"Bad stuff happening in SQL exists records";
        return { };
    }
    for(int i=0; i<fields.length(); i++)
    {
        querryText +=fields[i] + " LIKE " + "'%" +constraints[i] +"%' " + "AND ";
    }
    querryText += "1=1)";
    QSqlQuery qry(db);
    qry.exec(querryText);
    while(qry.next())
    {
        QString titlu = qry.value(0).toString();
        QString autor = qry.value(1).toString();
        QString gen = qry.value(2).toString();
        QString isbn = qry.value(3).toString();
        int id_carte = qry.value(4).toInt();
        Book carte(titlu,autor,gen,isbn,id_carte);
        books.append(carte);
    }
    return books;
}

void SQLController::Initialize()
{
    QString absolutePath = QDir::currentPath() + ("/userdata.sql");
    if(Initialized == false)
    {
        auto name = "my_db_" + QString::number((quint64)QThread::currentThread(), 16);
        if(QSqlDatabase::contains(name))
            db= QSqlDatabase::database(name);
        else
        {
            db = QSqlDatabase::addDatabase( "QSQLITE", name);
            db.setDatabaseName(absolutePath);
        }
        if(db.open())
        {
              qDebug()<<"Stuff went OK"<<Qt::endl;
              Initialized = true;
        }
        else
        {

               qDebug()<<"Stuff went wrong"<<Qt::endl;
        }
    }

}