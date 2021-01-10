#include "book.h"

Book::Book()
{

}

Book::Book(QString title, QString author, QString genre, QString ISBN, QString rating, int an, int id_carte) : title(title), author(author), rating(rating), an(an), genre(genre), ISBN(ISBN), id_carte(id_carte)
{

}

QVector<Book> Book::ParseBookString(QString mesaj)
{
    QVector<Book> ret;
    QVector<QString> bookStrings; //"Titlu", "Autor", "Gen", "ISBN", "rating", "an", "id_carte
    QRegExp rx("(\\*)");
    bookStrings = mesaj.split(rx).toVector();
    bookStrings.removeLast();
    //! needs extra parsing
    for(auto str : bookStrings)
    {
        QRegExp rx1("(\\|)");
        QVector<QString> stats =  str.split(rx1).toVector();
        Book carte(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5].toInt(), stats[6].toInt() );
        ret.append(carte);
    }
    return ret;
}
