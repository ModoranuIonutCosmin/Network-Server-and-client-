#include "sqlcontroller.h"

SQLController* SQLController::instance = nullptr;
bool SQLController::Initialized = false;
QSqlDatabase SQLController::db;
SQLController::SQLController()
{

}

int SQLController::ExistsRecord(DBTabs table, QVector<QString> fields, QVector<QString> values)
{
    for(int i=0;i< values.size(); i++)
    {
        SanitizeInputs(values[i]);
    }
    if(Initialized == false)
        Initialize();
    QString querryText = "SELECT * FROM " + EnumHelpers::QtEnumToString(table) +" WHERE (";
    if(fields.length()!= values.length())
    {
        qDebug()<<"Bad stuff happening in SQL exists records";
        return 0;
    }
    for(int i=0; i< fields.length();i++)
        if(fields[i] == "authHash")
    {
        values[i] = QString(QCryptographicHash::hash(values[i].toStdString().c_str(), QCryptographicHash::Sha256).toHex());
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
       if(table == DBTabs::USERS)
           return qry.value(4).toInt();
       else
           return 1;
   }
   return -1;
}

QVector<Book> SQLController::GetBooksList(QVector<QString> constraints)
{
    for(int i=0;i< constraints.size(); i++)
    {
        SanitizeInputs(constraints[i]);
    }
    QVector<Book> books;
    const QVector<QString> fields = {"Titlu", "Autor", "Gen", "ISBN", "rating", "an"};
    if(SQLController::Initialized == false)
        Initialize();
    for(int i=0; i<constraints.size(); i++)
    {
        if(constraints[i]==" ")
            constraints[i]="";
    }
    QString querryText = "SELECT Titlu,Autor,Gen,ISBN,rating, an,id_carte FROM " + EnumHelpers::QtEnumToString(BOOKS) +" WHERE (";
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
        //aici e an dupa rating, invers
        QString titlu = qry.value(0).toString();
        QString autor = qry.value(1).toString();
        QString gen = qry.value(2).toString();
        QString isbn = qry.value(3).toString();
        int an = qry.value(5).toString().toInt();
        QString rating = qry.value(4).toString();
        int id_carte = qry.value(6).toInt();
        QVector<QString> genuri{gen};
        Book carte(titlu,autor,genuri,isbn, rating, an);
        carte.id_carte = id_carte;
        books.append(carte);
    }
    return books;
}

QVector<Book> SQLController::Aggregate(QVector<RBook> rBooks)
{
    if(Initialized == false)
        Initialize();
    QVector<Book> books;
    QString querry = "SELECT Titlu,Autor,Gen,ISBN,rating, an,id_carte FROM BOOKS WHERE ID_CARTE IN (";
    for(auto& rBook : rBooks)
    {
        querry+= QString::number(rBook.id_carte)+",";
    }
    querry[querry.length()-1] = ')';
    QSqlQuery qry(db);
    qry.exec(querry);
    while(qry.next())
    {
        //aici e an dupa rating, invers
        QString titlu = qry.value(0).toString();
        QString autor = qry.value(1).toString();
        QString gen = qry.value(2).toString();
        QString isbn = qry.value(3).toString();
        int an = qry.value(5).toString().toInt();
        QString rating = qry.value(4).toString();
        int id_carte = qry.value(6).toInt();
        QVector<QString> genuri{gen};
        Book carte(titlu,autor,genuri,isbn, rating, an);
        carte.id_carte = id_carte;
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
    //Sanitaze params
    SanitizeInputs(b.ISBN);
    SanitizeInputs(b.author);
    SanitizeInputs(b.genre[0]);
    SanitizeInputs(b.rating);
    SanitizeInputs(b.title);

    if(Initialized == false)
        Initialize();
    QString querry = QString("INSERT INTO BOOKS (Titlu, Autor, Gen, ISBN, An, rating) ")+
                     +"VALUES ('" + b.title +"','" +b.author+"','"+ b.genre[0]+"','" + b.ISBN +"',"+
                     QString::number(b.an)+",0)";
    QSqlQuery qry(db);
    qry.exec(querry);
    qry.exec("SELECT id_carte FROM BOOKS WHERE id_carte = (SELECT MAX(id_carte)  FROM BOOKS)");
    if(qry.next() == 0)
    {
        qDebug()<<"Eroare la MAX() in register book"<<Qt::endl;
    }
    newID = qry.value(0).toInt();
    qry.exec("insert into STORAGE VALUES ("+QString::number(newID)+",'"+b.title.replace(" ","_")+QString::number(newID)+ ".pdf')"); //
    for(auto& gen : b.genre)
    {
        qry.exec("insert into GENRES values (" + QString::number(newID) +",'" +gen +"')");
    }
    return newID;
}

QString SQLController::ReadRating(int id_carte, int id_user)
{
    if(Initialized == false)
        Initialize();
    QString querryUser = "SELECT rating FROM RATING WHERE id_user = " +QString::number(id_user)+
                         " AND id_carte =" + QString::number(id_carte);
    QString querryText = "SELECT rating FROM BOOKS WHERE id_carte = " + QString::number(id_carte);
    QSqlQuery qry(db);
    int userRating = -1;
    double totalRating = 0;

    qry.exec(querryUser);
    if(qry.next())
    {
        userRating = qry.value(0).toInt();
    }
    qry.exec(querryText);
    if(qry.next())
    {
        totalRating = qry.value(0).toDouble();
    }

    return QString::number(userRating) +" "+ QString::number(totalRating, 'f', 2);

}

bool SQLController::InsertRating(int id_carte, int id_user, int valoareRating)
{
    if(Initialized == false)
        Initialize();
    QString querry = "INSERT INTO RATING VALUES("+QString::number(id_carte)+
                     ","+QString::number(id_user)+","+QString::number(valoareRating)+")";
    QSqlQuery qry(db);
    qry.exec(querry);
    return true;
}

bool SQLController::UpdateUserRating(int id_carte, int id_user, int valoareRating)
{
    if(Initialized == false)
        Initialize();
    QString querry = "UPDATE RATING SET rating =" +QString::number(valoareRating) +
            " WHERE id_carte=" + QString::number(id_carte) + " AND id_user=" + QString::number(id_user) ;
    QSqlQuery qry(db);
    qry.exec(querry);
    return true;
}

bool SQLController::UpdateBookRating(int id_carte, double valoare)
{
    if(Initialized == false)
        Initialize();
    QString querry = "UPDATE BOOKS SET rating =" +QString::number(valoare) +
            " WHERE id_carte=" + QString::number(id_carte) ;
    QSqlQuery qry(db);
    qry.exec(querry);
    return true;
}

QPair<int, int> SQLController::GetSumAndRatingCount(int id_carte)
{
    if(Initialized == false)
        Initialize();
    QString querry = "SELECT count(*), sum(rating) FROM rating WHERE id_carte = " +
            QString::number(id_carte);
    QSqlQuery qry(db);
    qry.exec(querry);
    if(qry.next())
    {
        return {qry.value(1).toInt(), qry.value(0).toInt()};
    }
    return {-1, -1};
}

QVector<RBook> SQLController::GetUsersRatedBooks(int id_user)
{
    if(Initialized == false)
        Initialize();
    QVector<RBook> ret;

    QString querry = "SELECT TITLU, AUTOR,b.ID_CARTE,b.RATING FROM BOOKS b JOIN RATING r ON b.id_carte = r.id_carte WHERE ID_USER="+QString::number(id_user);
    QSqlQuery qry(db);
    qry.exec(querry);
    while(qry.next())
    {
            QString titlu = qry.value(0).toString();
            QString autor= qry.value(1).toString();
            int id_carte= qry.value(2).toInt();
            double rating= qry.value(3).toDouble();
            RBook carte(titlu, autor, id_carte, rating);
            ret.push_back(carte);
    }
    return ret;
}

QVector<RBook> SQLController::GetAllBooks()
{
    if(Initialized == false)
        Initialize();
    QVector<RBook> ret;

    QString querry = "SELECT TITLU, AUTOR,ID_CARTE,RATING FROM BOOKS LIMIT " + QString::number(MAX_BOOKS);
            QSqlQuery qry(db);
    qry.exec(querry);
    while(qry.next())
    {
        QString titlu = qry.value(0).toString();
        QString autor= qry.value(1).toString();
        int id_carte= qry.value(2).toInt();
        double rating= qry.value(3).toDouble();
        RBook carte(titlu, autor, id_carte, rating);
        ret.push_back(carte);
    }
    return ret;
}

QVector<RRating> SQLController::GetRatingValues()
{
    if(Initialized == false)
        Initialize();
    QVector<RRating> ret;
    QString querry = "SELECT* FROM RATING LIMIT " +QString::number(MAX_RATINGS);
    QSqlQuery qry(db);
    qry.exec(querry);
    while(qry.next())
    {
        int id_carte = qry.value(0).toInt();
        int id_user  = qry.value(1).toInt() ;
        int rating   = qry.value(2).toInt();
        RRating rate (id_carte, id_user,rating);
        ret.push_back(rate);
    }
    return ret;
}

void SQLController::InsertDownloadActivity(int id_carte, int id_user)
{
    if(Initialized == false)
        Initialize();
    QSqlQuery qry(db);
    QString querry = "INSERT INTO ACTIVITY (id_carte, id_user, tip, data) VALUES("+
            QString::number(id_carte)+","+QString::number(id_user)+",'DOWNLOAD', date('now'))";
    qry.exec(querry);
}

void SQLController::SanitizeInputs(QString& param)
{
    param = param.replace('\'', ' ');
    param = param.replace('"', ' ');

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

void SQLController::DoStuff()
{
    if(Initialized == false)
        Initialize();
    std::ifstream f("inputfile.txt");
    QSqlQuery qry(db);


    std::string line, a ,b, c;
    while(std::getline(f, line))
    {
        Book b;

        QString line1(line.c_str());
        QVector<QString> vec = line1.split("\t").toVector();
        b.title = vec[0];
        b.genre.push_back(vec[2].replace('_', ' '));
        b.author=vec[1];
        b.an = 2020;
//        b.rating = "0";
        b.ISBN = "1-2-3-4324-12";
        RegisterBook(b);

    }

}
