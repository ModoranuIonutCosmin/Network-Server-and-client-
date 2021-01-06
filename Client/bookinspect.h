#ifndef BOOKINSPECT_H
#define BOOKINSPECT_H

#include <QtDebug>
#include <QFileDialog>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include "transfer.h"
#include "clientthread.h"
class BookInspect : public QWidget
{
    Q_OBJECT
public:
    explicit BookInspect(int id_carte, QWidget *parent = nullptr);
    void Setuip(int id);
    QPushButton* loginButton;
    QVBoxLayout* mainLayout;
    int id_carte = 0;
signals:
private slots:
    void Download();

};

#endif // BOOKINSPECT_H
