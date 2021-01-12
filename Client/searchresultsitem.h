#ifndef SEARCHRESULTSITEM_H
#define SEARCHRESULTSITEM_H

#include <QWidget>
#include <QStatusBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QStandardItem>
#include <QDataWidgetMapper>
#include <QStack>
#include "book.h"
class searchResultsItem : public QWidget
{
    Q_OBJECT
public:
    explicit searchResultsItem(QWidget *parent = nullptr);
    void Setup(QString name, QString autor, QString gen, QString ISBN, QString rating, int an, int id_carte);
    Book Get() const;
signals:
//    void dataChanged(QModelIndex,QModelIndex,QVector<int>);
public:
    QHBoxLayout* mainLayout;
    QStatusBar* iconSB;
    QPixmap* iconPixMap;
    QLabel* labelIcon;
    QLabel* bookName;
    QLabel* author;
    QLabel* genres;
    QLabel* ratingText;
    QLabel* viewsNum;
    QLabel* an;
    QLabel* anLabel;
    QLabel* ISBNLabel;
    QLabel* genresLabel;
    QLabel* authorLabel;
    QLabel* bookNameLabel;
    QLabel* ratingLabel;
    QVBoxLayout* ratingLay;
    QVBoxLayout* anLay          ;
    QVBoxLayout* ISBNLay        ;
    QVBoxLayout* genreLay       ;
    QVBoxLayout* authorLay      ;
    QVBoxLayout* bookNameLay    ;


    QImage image;
    QStandardItemModel* vm;
    QDataWidgetMapper* mapper;
    int id_carte = 999;
    int fullyInitialized = 0;
};

#endif // SEARCHRESULTSITEM_H
