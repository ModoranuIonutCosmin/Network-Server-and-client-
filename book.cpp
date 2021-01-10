#include "book.h"

Book::Book()
{

}

Book::Book(QString title, QString author, QVector<QString> genre, QString ISBN, QString rating, int an )
    : title(title), author(author),genre(genre), ISBN(ISBN),rating(rating), an(an)
{
    QRegExp rx("(\\;)");
    this->genre = genre[0].split(rx).toVector();
}

Book::Book(QString title, QString author, QVector<QString> genre, QString ISBN, int an):
    title(title), author(author),genre(genre), ISBN(ISBN), an(an)
{

}


QString Book::DoListAsMessage(QVector<Book>& carti)
{
    QString sendString = "";
    for(auto& book : carti)
    {
        QString atom = book.title+'|'+book.author+'|'+book.genre[0] +'|' +book.ISBN +'|'+ book.rating+'|'+QString::number(book.an)+'|' +QString::number(book.id_carte) +'|';
        sendString+= atom +'*';
    }
    return sendString;
}

Book Book::DoMessageAsBook(QString str)
{
    QRegExp rx1("(\\|)");
    QVector<QString> stats =  str.split(rx1).toVector(); // T A G I R A
    QString genuri = stats[2];
    QVector<QString> genres = genuri.split(QRegExp("(\\;)")).toVector();
    Book ret(stats[0].replace(' ', '_'), stats[1], genres, stats[3], stats[4].toInt());
//    ret.id_carte = stats[6].toInt();
    return ret;
}
