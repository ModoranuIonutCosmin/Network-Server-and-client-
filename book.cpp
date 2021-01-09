#include "book.h"

Book::Book()
{

}

Book::Book(QString title, QString author, QString genre, QString ISBN, int id_carte) : title(title), author(author), genre(genre), ISBN(ISBN), id_carte(id_carte)
{

}

Book::Book(QString title, QString author, QString genre, QString ISBN, QString an) :title(title), author(author), genre(genre), ISBN(ISBN),  an(an)
{

}

QString Book::DoListAsMessage(QVector<Book>& carti)
{
    QString sendString = "";
    for(auto& book : carti)
    {
        QString atom = book.title+'|'+book.author+'|'+book.genre +'|' +book.ISBN +'|' +QString::number(book.id_carte) +'|';
        sendString+= atom +'*';
    }
    return sendString;
}

Book Book::DoMessageAsBook(QString str)
{
    QRegExp rx1("(\\|)");
    QVector<QString> stats =  str.split(rx1).toVector(); // T A G I A
    Book ret(stats[0], stats[1], stats[2], stats[3], stats[4]);
    return ret;
}
