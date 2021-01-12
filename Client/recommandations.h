#ifndef RECOMMANDATIONS_H
#define RECOMMANDATIONS_H

#include <QObject>
#include <QLineEdit>
#include <QVector>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include "clientthread.h"
#include "book.h"
#include "searchresultsitem.h"
class Recommandations : public QWidget
{
    Q_OBJECT
public:
    explicit Recommandations(QWidget *parent = nullptr);
    QMenuBar* menu;
    QMenu* settings;
    QListWidget* searchResults;
    QVBoxLayout* mainLayout;
    QHBoxLayout* sideMenuAndContent;
    QVBoxLayout* sideMenu;
    QVBoxLayout* content;
    QLineEdit* author;
    QLineEdit* ISBN;
    QLineEdit* gen;
    QLabel* AuthorLabel;
    QLabel* ISBNLabel;
    QLabel* genLabel;
    QLabel* title;
    QWidget* filterHide;

    QLineEdit* searchField;
    QPushButton* searchButton;
    QPushButton* goBack;
    QPushButton* loadRecommandations;

    QList<searchResultsItem*> records;
    QList<QListWidgetItem*> items;
    void DeleteAllItems();

signals:
    void MoveToPage(QListWidgetItem*);
    void DoBookPage(Book b);
private slots:
    void DoBooksList(QVector<Book> books);
    void GetClickedItem(QListWidgetItem*);
    void GetRecommandations();

};

#endif // RECOMMANDATIONS_H
