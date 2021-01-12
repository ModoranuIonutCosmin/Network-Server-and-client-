#include "recommendengine.h"







//R ENGINE


void RecommendEngine::FilterRatingsByBooks(QVector<RRating> &car, QVector<RBook> ac)
{
    QVector<RRating> result;
    result.reserve(300);
    for(int i=0; i< car.size();i++)
    {
        for(int j=0; j<ac.size(); j++)
        {
            if(ac[j].id_carte == car[i].id_carte)
            {
                result.push_back(car[i]);
                break;
            }
        }
    }
    car = result;
}

QVector<RRating> RecommendEngine::FilterRatingsByUser(QVector<RRating> car, int id_user)
{
    QVector<RRating> ret;
    for(int i=0; i< car.size(); i++)
    {
        if(car[i].id_user == id_user)
        {
            ret.push_back(car[i]);
            break;
        }
    }
    return ret;
}

void RecommendEngine::SortMapBySize(std::map<int, QVector<RBook> > &mapa)
{
    std::map<int, QVector<RBook>> ret;
    std::vector<std::pair<int, int>> marimi;

    for (auto& x : mapa)
        marimi.emplace_back(x.second.size(), x.first);
    std::sort(std::begin(marimi), std::end(marimi), [](std::pair<int, int> a, std::pair<int, int> b)
    {
        return a.first > b.first;
    });
    for(auto& marime : marimi)
    {
        auto v = mapa[marime.second];
        std::sort(v.begin(),v.end(),
                [](RBook& a, RBook& b)
                {
                        return a.id_carte<b.id_carte;
                }) ;
        ret[marime.second] = v;
    }
    mapa = ret;
}

QVector<RRating> RecommendEngine::GetUserRating(QVector<RBook> books, int id_user)
{
    QVector<RRating>  ret;
    for(int i=0; i< ratingDataAll.size();i++)
    {
        for(int j=0; j<books.size(); j++)
        {
            if(ratingDataAll[i].id_carte == books[j].id_carte && ratingDataAll[i].id_user == id_user)
            {
                ret.push_back(ratingDataAll[i]);
                break;
            }
        }
    }
    return ret;
}

QVector<RBook> RecommendEngine::In(QVector<RBook> src, QVector<RBook> dst)
{
    QVector<RBook> ret;
    //sunt in dst(input) dar sunt si in src
    for(int i=0; i< src.size(); i++)
    {
        for(int j=0; j<dst.size(); j++)
        {
            if(src[i].id_carte == dst[j].id_carte)
            {
                ret.push_back(dst[j]);
                break;
            }
        }
    }
    return ret;
}

RecommendEngine::RecommendEngine(int id_user_rec)
{
    this->id_user = id_user_rec;
    ratingData.reserve(300);
    bookData.reserve(300);
    CollectDataInitial(id_user_rec);
}

void RecommendEngine::CollectDataInitial(int id_user)
{
    allBooks = SQLController::GetAllBooks();
    bookData = SQLController::GetUsersRatedBooks(id_user); //userBookdata
    auto aux = allBooks;
    RemoveV2fromV1(aux, bookData);
    this->recommandationPool = aux;


    ratingData = SQLController::GetRatingValues();

    for(auto& rating : ratingData)
    {
        if(rating.id_user == id_user)
        {
            userRatings.push_back(rating);
        }
    }
    RemoveV2fromV1(ratingData, userRatings); // ratingData = ratingData - userRatings

    ratingDataAll = ratingData;

    FilterRatingsByBooks(ratingData, bookData); // limiteaza domeniul la cartile citite de user-ul
                                            // care cere recomandarile
    for (const auto& grup : ratingData)
    {
        this->usersClusters[grup.id_user].push_back(GetBook(grup.id_carte));
    }
    //Sorteaza dupa match-uri descrescator grupele
    SortMapBySize(usersClusters);
    std::sort(bookData.begin(), bookData.end(),[](RBook& a, RBook& b)
    {
            return a.id_carte<b.id_carte;
    });
}

QVector<RBook> RecommendEngine::GetRecommandations()
{
    double pCoefficient;
    QVector<RRating> userRATINGS = userRatings;

    for(auto& grup : usersClusters)
    {
        userRATINGS = userRatings;
        QVector<RBook> temp = this->In(grup.second, bookData);

        QVector<RRating> temp1 = GetUserRating(temp, grup.first); //for user
        FilterRatingsByBooks(userRATINGS, temp); //for inputs
        QVector<RRating> temp2 = userRATINGS;

        std::vector<double> rating_input;
        std::vector<double> rating_user;

        double sum_input=0;
        double sum_user=0;
        double sum_input_p=0;
        double sum_user_p=0;
        double sum_mixed_p=0;
        for(int ii =0; ii<temp2.size(); ii++)
        {
            rating_input.push_back(temp2[ii].rating);
            rating_user.push_back(temp1[ii].rating);
//            sum_input+= temp2[ii].rating;
//            sum_user+= temp1[ii].rating;
//            sum_input_p+= temp2[ii].rating*temp2[ii].rating;
//            sum_user_p+=temp1[ii].rating*temp1[ii].rating;
//            sum_mixed_p+= temp2[ii].rating*temp1[ii].rating;
        }
        int nrRatings = rating_input.size();
        if(nrRatings == 0) continue;
        double avg_input, avg_user;
        avg_input = std::accumulate(rating_input.begin(), rating_input.end(), 0) /(double)nrRatings;
        avg_user = std::accumulate(rating_user.begin(), rating_user.end(), 0)/(double)nrRatings;
         double sx=0,sy=0,sxy=0;
        for(int i=0; i<nrRatings; i++)
        {
            sxy += (temp1[i].rating - avg_user)*(temp2[i].rating - avg_input);
            sx += pow(temp1[i].rating - avg_user, 2);
            sy += pow(temp2[i].rating - avg_input, 2);
        }


//        sx =sum_input_p - pow(sum_input_p,2)/(double)nrRatings;
//        sy = sum_user_p - pow(sum_user_p, 2)/(double)nrRatings;
//        sxy= sum_mixed_p - (sum_input_p*sum_user_p)/(double)nrRatings;
        if(sx!=0 and sy!=0)
            pCoefficient = sxy/(double)sqrt(sx*sy);
        else
            pCoefficient=0;
        indicatoriPearson[grup.first]= pCoefficient;
    }
    for(auto& user : usersClusters)
    {
        QVector<RRating> tmp = ratingDataAll;
        QVector<RBook> complement = allBooks;
        this->RemoveV2fromV1(complement, bookData);
        this->FilterRatingsByBooks(tmp, complement);
        for(auto& rating : tmp)
        {
            auto& b = this->GetBookGlobal(rating.id_carte);
            b.Pondere += (double)indicatoriPearson[rating.id_user];
            b.SI += indicatoriPearson[rating.id_user]*(double)rating.rating;
        }
    }
    for(auto& book: allBooks)
    {
        if(book.SI!=0 and book.Pondere!=0)
        {
            book.scor =(double) book.SI / book.Pondere;
        }
        else
        {
            book.scor=0;
        }

    }
    std::sort(allBooks.begin(), allBooks.end(), [](RBook&a, RBook&b)
    {
        return a.scor>b.scor;
    });
    auto backup = allBooks;
    backup.resize(std::min(MAX_BOOKS, allBooks.size()));
    return backup;
}

RBook& RecommendEngine::GetBook(int id_carte)
{
    for(auto& carte : bookData)
    {
        if(carte.id_carte == id_carte)
           return carte;
    }
    throw(std::runtime_error("Not good"));
}

RBook& RecommendEngine::GetBookGlobal(int id_carte)
{
    for(auto& carte : allBooks)
    {
        if(carte.id_carte == id_carte)
           return carte;
    }
    throw(std::runtime_error("Not good"));
}

















template<typename T>
void RecommendEngine::RemoveV2fromV1(QVector<T> &v1, QVector<T> v2)
{
    for(int i=0; i< v2.size(); i++)
    {
       v1.removeAll(v2[i]);
    }
}
