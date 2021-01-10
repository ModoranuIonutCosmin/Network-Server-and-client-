#include "recommendengine.h"







//R ENGINE


void RecommendEngine::FilterRatingsByUser(QVector<RRating> &car, QVector<RBook> ac)
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

    FilterRatingsByUser(ratingData, bookData); // limiteaza domeniul la cartile citite de user-ul
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
    for(auto& grup : usersClusters)
    {
        int nrRatings = grup.second.size();
        QVector<RBook> temp = this->In(grup.second, bookData);
        QVector<double> rating_input;
        QVector<double> rating_user;
        double sum_input=0;
        double sum_user=0;
        double sum_input_p=0;
        double sum_user_p=0;
        double sum_mixed_p=0;
        for(int ii =0; ii<temp.size(); ii++)
        {
            rating_input.append(temp[ii].rating);
            rating_user.append(grup.second[ii].rating);
            sum_input+= temp[ii].rating;
            sum_user+= grup.second[ii].rating;
            sum_input_p+= temp[ii].rating*temp[ii].rating;
            sum_user_p+=grup.second[ii].rating*grup.second[ii].rating;
            sum_mixed_p+= grup.second[ii].rating*temp[ii].rating;
        }
        double sx=0,sy=0,sxy=0;
        sx =sum_input_p - pow(sum_input_p,2)/(double)nrRatings;
        sy = sum_user_p - pow(sum_user_p, 2)/(double)nrRatings;
        sxy= sum_mixed_p - (sum_input_p*sum_user_p)/(double)nrRatings;
        if(sx!=0 and sy!=0)
            pCoefficient = sxy/((double)sqrt(sx*sy));
        else
            pCoefficient=0;
        indicatoriPearson[grup.first]= pCoefficient;
    }
    for(auto& rating : ratingDataAll)
    {
        auto b = this->GetBookGlobal(rating.id_carte);
        b.Pondere += (double)indicatoriPearson[rating.id_user];
        b.SI += indicatoriPearson[rating.id_user]*(double)rating.rating;
    }
    for(auto& book: allBooks)
    {
        book.scor =(double) book.SI / book.Pondere;
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
