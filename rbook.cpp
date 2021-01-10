#include "rbook.h"




//S DATE
RBook::RBook()
{

}

RBook::RBook(QString titlu, QString autor, int id_carte, double rating)
{
    this->titlu = titlu;
    this->autor = autor;
    this->id_carte = id_carte;
    this->rating = rating;
}

bool RBook::operator==(const RBook &book) const
{
    if(book.autor != this->autor) return false;
    if(book.id_carte != this->id_carte) return false;
    if(book.titlu != this->titlu) return false;
    return true;
}
