#ifndef RBOOK_H
#define RBOOK_H
#include <QString>


class RBook
{
public:
    RBook();
    RBook(QString titlu, QString autor, int id_carte, double rating=0);
    bool operator==(const RBook& book) const;
    QString titlu;
    QString autor;
    int id_carte;
    double scor=0;
    double Pondere=0;
    double SI=0;
    double rating;
};

#endif // RBOOK_H
