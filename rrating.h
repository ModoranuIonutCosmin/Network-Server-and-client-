#ifndef RRATING_H
#define RRATING_H


class RRating
{
public:
    RRating();
    RRating(int id_carte, int id_user, int rating);
    bool operator==(const RRating& rating) const;
    int id_carte;
    int id_user ;
    int rating  ;
};

#endif // RRATING_H
