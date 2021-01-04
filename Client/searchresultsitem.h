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
class searchResultsItem : public QWidget
{
    Q_OBJECT
public:
    explicit searchResultsItem(QWidget *parent = nullptr);
    void Setup(QString name, QString rating, QString views);
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
    QImage image;
    QStandardItemModel* vm;
    QDataWidgetMapper* mapper;

};

#endif // SEARCHRESULTSITEM_H
