#include "book.h"

Book::Book()
{

}

Book::Book(QString title, QString author, QString genre, QString ISBN, int id_carte) : title(title), author(author), genre(genre), ISBN(ISBN), id_carte(id_carte)
{

}

QVector<Book> Book::ParseBookString(QString mesaj)
{
    QVector<Book> ret;
    QVector<QString> bookStrings; //"Titlu", "Autor", "Gen", "ISBN", "Views"
    QRegExp rx("(\\*)");
    bookStrings = mesaj.split(rx).toVector();
    bookStrings.removeLast();
    //! needs extra parsing </possibleBug>
    for(auto str : bookStrings)
    {
        QRegExp rx1("(\\|)");
        QVector<QString> stats =  str.split(rx1).toVector();
        Book carte(stats[0], stats[1], stats[2], stats[3], stats[4].toInt());
        ret.append(carte);
    }
    return ret;
}
