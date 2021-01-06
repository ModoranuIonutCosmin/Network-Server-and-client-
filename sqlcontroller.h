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
#include "book.h"
class SQLController : QObject
{

    Q_OBJECT
public:
    enum DBTabs
    {
        USERS,
        ACTIVTY,
        BOOKS,
        STORAGE
    };
    static bool Initialized;
    static QSqlDatabase db;
    Q_ENUM(DBTabs)
    SQLController();
    static bool ExistsRecord(DBTabs table, QVector<QString> fields, QVector<QString> values);
    static QVector<Book> GetBooksList(QVector<QString> constraints);
    static QString GetFilePath(int id_carte);
    static void Initialize();
    static SQLController* instance;
};

#endif // SQLCONTROLLER_H
