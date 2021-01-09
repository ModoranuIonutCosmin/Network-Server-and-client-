#ifndef RECOMMANDATIONS_H
#define RECOMMANDATIONS_H

#include <QObject>
#include <QLineEdit>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
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
    QPushButton* goToRecomandations;

    QList<searchResultsItem*> records;
    QList<QListWidgetItem*> items;
signals:
private slots:
    void DoBooksList(QVector<Book> books);
    void GetClickedBook(QListWidgetItem* item);
};

#endif // RECOMMANDATIONS_H
