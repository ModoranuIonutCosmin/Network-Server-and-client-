#include "sqlcontroller.h"

SQLController* SQLController::instance = nullptr;
bool SQLController::Initialized = false;
QSqlDatabase SQLController::db;
SQLController::SQLController()
{

}

int SQLController::ExistsRecord(DBTabs table, QVector<QString> fields, QVector<QString> values)
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
       return qry.value(4).toInt();
   }
   return -1;
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

QString SQLController::GetFilePath(int id_carte)
{
    if(Initialized == false)
        Initialize();
    QString querry = "SELECT name FROM STORAGE WHERE id_carte = " + QString::number(id_carte);
    QSqlQuery qry(db);
    qry.exec(querry);
    if(qry.next())
    {
        return qry.value(0).toString();
    }
    return " ";
}

int SQLController::RegisterBook(Book &b)
{
    int newID = -1;
    QString querry = QString("INSERT INTO BOOKS (Titlu, Autor, Gen, ISBN, An) ")+
                     +"VALUES ('" + b.title +"','" +b.author+"','"+ b.genre+"','" + b.ISBN +"',"+
                     b.an+")";
    QSqlQuery qry(db);
    qry.exec(querry);
    qry.exec("SELECT id_carte FROM BOOKS WHERE id_carte = (SELECT MAX(id_carte)  FROM BOOKS)");
    if(qry.next() < 0)
    {
        qDebug()<<"Eroare la MAX() in register book"<<Qt::endl;
    }
    newID = qry.value(0).toInt();
    qry.exec("insert into STORAGE VALUES ("+QString::number(newID)+",'"+b.title.replace(" ","_")+ QString::number(newID)+".pdf')");

    return newID;
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
