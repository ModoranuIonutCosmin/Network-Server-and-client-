#ifndef BOOK_H
#define BOOK_H
#include <QString>

class Book
{
public:
    Book(QString title, QString author, QString genre, QString ISBN, int id_carte);
QString title;
QString author;
QString genre;
QString rating;
QString ISBN;

int id_carte;
};

#endif // BOOK_H
