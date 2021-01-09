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
    Book(QString title, QString author, QString genre, QString ISBN, int id_carte=UNDEFINED_BOOK);
    QString title;
    QString author;
    QString genre;
    QString rating;
    QString ISBN;
    static QVector<Book> ParseBookString(QString mesaj);
int id_carte;
};
Q_DECLARE_METATYPE(QVector<Book>);

#endif // BOOK_H
