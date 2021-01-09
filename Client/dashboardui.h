#ifndef DASHBOARDUI_H
#define DASHBOARDUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMenuBar>
#include <QThread>
#include "searchresultsitem.h"
#include <memory>
#include <QList>
#include <QStack>
#include <QCheckBox>
#include "spoiler.h"
#include "clientthread.h"
#include "book.h"

//spam control
#define MAX_CLICKS_PER_TIME 7
#define TIME 20000

class DashboardUI : public QWidget
{
    Q_OBJECT
public:
    explicit DashboardUI(QWidget *parent = nullptr);

    QMenuBar* menu;
    QMenu* settings;
    QListWidget* searchResults;
    QVBoxLayout* mainLayout;
    QHBoxLayout* sideMenuAndContent;
    QVBoxLayout* sideMenu;
    QVBoxLayout* content;
    QHBoxLayout* searchBar;
    QHBoxLayout* filters;
    QLineEdit* author;
    QLineEdit* ISBN;
    QLineEdit* gen;
    QLabel* AuthorLabel;
    QLabel* ISBNLabel;
    QLabel* genLabel;
    QCheckBox* filtersON;
    QWidget* filterHide;
    Spoiler* spoiler;

    QLineEdit* searchField;
    QPushButton* searchButton;
    QPushButton* goBack;
    QPushButton* goToRecomandations;
    QPushButton* publish;
    QList<searchResultsItem*> records;
    QList<QListWidgetItem*> items;

    //spam protection
    QTimer tryAgain;
    size_t NoClicks=0;

    static int ultima_carte;
signals:
   void DoBookPage(Book b);
   void DoRecommandationsPage();
private slots:
   void ChangeContent();
   void AppendBooks(QVector<Book> books);
   void GetClickedBook(QListWidgetItem* item);
   void ShowRecommandations();
   void DeleteAllItems();
   void CheckSpam();

};
#endif // DASHBOARDUI_H
