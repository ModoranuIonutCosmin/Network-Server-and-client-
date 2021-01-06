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
    void Setup(QString name, QString autor, QString gen, QString ISBN, int id_carte);
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
    int id_carte = 999;
};

#endif // SEARCHRESULTSITEM_H
