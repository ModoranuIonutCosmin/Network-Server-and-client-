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
    Book(QString title, QString author, QVector<QString> genre, QString ISBN, QString rating, int an );
    Book(QString title, QString author, QVector<QString> genre, QString ISBN, int an );
    static QString DoListAsMessage(QVector<Book>& carti);
    static Book DoMessageAsBook(QString msg);
    QString title;
    QString author;
    QVector<QString> genre;
    int an;
    int id_carte;
    QString rating;
    QString ISBN;

};

#endif // BOOK_H
