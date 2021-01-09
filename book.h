#ifndef BOOK_H
#define BOOK_H
#include <QRegExp>
#include <QString>
#include <QVector>
#include <QStringList>
class Book
{
public:
    Book();
    Book(QString title, QString author, QString genre, QString ISBN,  int id_carte);
    Book(QString title, QString author, QString genre, QString ISBN, QString an );
    static QString DoListAsMessage(QVector<Book>& carti);
    static Book DoMessageAsBook(QString msg);
QString title;
QString author;
QString genre;
QString an;
QString rating;
QString ISBN;

int id_carte;
};

#endif // BOOK_H
