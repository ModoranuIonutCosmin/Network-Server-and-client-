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
    QPushButton* loginButton;
    QPushButton* goBack;
    QVBoxLayout* mainLayout;
    QLabel* name;
    QLabel* rating;
    Book date;
    int id_carte = 0;
signals:
private slots:
    void Download();

};

#endif // BOOKINSPECT_H
