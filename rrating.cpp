#include "rrating.h"

RRating::RRating()
{

}

RRating::RRating(int id_carte, int id_user, int rating)
{
    this->id_carte = id_carte;
    this->id_user = id_user;
    this->rating = rating;
}

bool RRating::operator==(const RRating &rating) const
{
    if(this->id_carte != rating.id_carte) return false;
    if(this->id_user != rating.id_user) return false;
    if(this->rating != rating.rating) return false;
    return true;
}
