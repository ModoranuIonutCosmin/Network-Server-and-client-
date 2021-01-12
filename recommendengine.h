#ifndef RECOMMENDENGINE_H
#define RECOMMENDENGINE_H

#include <QString>
#include <QVector>
#include <cmath>
#include <algorithm>
#include "sqlcontroller.h"
#include "rbook.h"
#include "rrating.h"
#define MAX_BOOKS 10


class RecommendEngine
{

public:
    template<typename T>
    static void RemoveV2fromV1(QVector<T>& v1, QVector<T>v2);
    static void FilterRatingsByBooks(QVector<RRating>& car, QVector<RBook> ac);
    static QVector<RRating> FilterRatingsByUser (QVector<RRating> car, int id_user);
    static void SortMapBySize(std::map<int, QVector<RBook>>& mapa);
    QVector<RRating> GetUserRating(QVector<RBook>, int);
    static QVector<RBook> In(QVector<RBook>src, QVector<RBook>dst);
    RecommendEngine(int);
    void CollectDataInitial(int);
    QVector<RBook> GetRecommandations();
    RBook& GetBook(int);
    RBook& GetBookGlobal(int);
    QVector<RBook> allBooks;  //toate cartile
    QVector<RBook> bookData;  //cartile la care user-ul a dat rating
    QVector<RRating> ratingData; //toate rating-urile date(initial) ->
                            //(doar rating-urile la bookdata)
    QVector<RRating> ratingDataAll;
    QVector<RRating> userRatings; //rating-urile date de user(se elimina din ratingData)
    QVector<RBook> recommandationPool; //cartile ce pot fi recomandate initial
    std::map<int, QVector<RBook>> usersClusters;
    std::map<int, double> indicatoriPearson;
    int id_user; //user to recommend for
};

#endif // RECOMMENDENGINE_H
