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
    QList<searchResultsItem*> records;
    QList<QListWidgetItem*> items;
signals:
private slots:
   void ChangeContent();
   void AppendBooks(QVector<Book> books);
   void DeleteAllItems();

};
#endif // DASHBOARDUI_H
