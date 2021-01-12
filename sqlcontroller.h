#ifndef SQLCONTROLLER_H
#define SQLCONTROLLER_H
#include <QVector>
#include <QDebug>
#include <QFileInfo>
#include <QSqlDatabase>
#include "enumhelpers.h"
#include <QSqlQuery>
#include <QDir>
#include <QThread>
#include <QPair>
#include <fstream>
#include <QCryptographicHash>
#include "book.h"
#include "rbook.h"
#include "rrating.h"

#define MAX_RATINGS 300
#define MAX_BOOKS 200

class SQLController : QObject
{

    Q_OBJECT
public:
    enum DBTabs
    {
        USERS,
        ACTIVTY,
        BOOKS,
        STORAGE,
        RATING,
        GENRES
    };
    static bool Initialized;
    static QSqlDatabase db;
    Q_ENUM(DBTabs)
    SQLController();
    //any
    static int ExistsRecord(DBTabs table, QVector<QString> fields, QVector<QString> values);
    //books
    static QVector<Book> GetBooksList(QVector<QString> constraints);
    static QVector<Book> Aggregate(QVector<RBook> rBooks);
    //storage

    static QString GetFilePath(int id_carte);

    //book, storage
    static int RegisterBook(Book& b);


    //rating
    static QString ReadRating(int id_carte, int id_user);
    static bool InsertRating(int id_carte, int id_user, int valoareRating);
    static bool UpdateUserRating(int id_carte, int id_user, int valoareRating);
    static bool UpdateBookRating(int id_carte, double valoare);
    static QPair<int, int> GetSumAndRatingCount(int id_carte);
    static QVector<RBook> GetUsersRatedBooks(int id_user);
    static QVector<RBook> GetAllBooks();
    static QVector<RRating> GetRatingValues();

    //Activity
    static void InsertDownloadActivity(int id_carte, int id_user);

    //security
    static void SanitizeInputs(QString& param);

    static void Initialize();
    static SQLController* instance;



    static void DoStuff();
};

#endif // SQLCONTROLLER_H
