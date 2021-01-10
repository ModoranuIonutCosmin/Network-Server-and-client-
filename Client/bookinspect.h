#ifndef BOOKINSPECT_H
#define BOOKINSPECT_H

#include <QtDebug>
#include <QFileDialog>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include "transfer.h"
#include "clientthread.h"
class BookInspect : public QWidget
{
    Q_OBJECT
public:
    explicit BookInspect(Book b, QWidget *parent = nullptr);
    void Setuip(int id, QString nume);
    QPushButton* downloadButton;
    QPushButton* goBack;
    QPushButton* oneStar;
    QPushButton* twoStars;
    QPushButton* threeStars;
    QPushButton* fourStars;
    QPushButton* fiveStars;
    QPushButton* rateButton;
    QPushButton* refresh;
    QVBoxLayout* mainLayout;
    QVBoxLayout* ratingLayout;
    QHBoxLayout* buttonLayout;
    QHBoxLayout* refreshLayout;
    QLabel* name;
    QLabel* rating;
    Book date;
    double ratingPoints = -1;
    int id_carte;
signals:
private slots:
    void Download();
    void ChangeRating(int, double);
    void ChangeRatingToOne();
    void ChangeRatingToTwo();
    void ChangeRatingToThree();
    void ChangeRatingToFour();
    void ChangeRatingToFive();
    void RequestRatingChange();
    void UpdateData();

};

#endif // BOOKINSPECT_H
