#ifndef BOOK_H
#define BOOK_H
#include <QString>
#include <QVector>
#include <QRegExp>
#include <QStringList>
#include <QMetaType>
#define UNDEFINED_BOOK 999
class Book
{
public:
    Book();
    Book(QString title, QString author, QString genre, QString ISBN,QString rating, int an, int id_carte);
    QString title;
    QString author;
    QString genre;
    QString rating;
    QString ISBN;
    int an;
    int id_carte;

    static QVector<Book> ParseBookString(QString mesaj);

};
Q_DECLARE_METATYPE(QVector<Book>);
Q_DECLARE_METATYPE(Book);

#endif // BOOK_H
