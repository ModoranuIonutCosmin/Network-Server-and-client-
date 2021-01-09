#ifndef PUBLISHPAGE_H
#define PUBLISHPAGE_H

#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "clientthread.h"
#include <limits>
#include <QString>
#include <QFileDialog>

#define MINIMUM_BOOK_TITLE 4
#define MAXIMUM_BOOK_TITLE 50
#define GEN_MINIMUM_STRING 4
#define GEN_MAXIMUM_STRING 29
#define AN_MAXIMUM_STRING 5
#define AN_MINIMUM_STRING 3
#define PATH_MINIMUM_STRING 5
#define PATH_MAXIMUM_STRING PATH_MAX

class PublishPage : public QWidget
{
    Q_OBJECT
public:
    explicit PublishPage(QWidget *parent = nullptr);

    void UserNameUpdated();
    QLineEdit* author;
    QLineEdit* title;
    QLineEdit* an;
    QLineEdit* ISBN;
    QLineEdit* gen;
    QLineEdit* path;
    QPushButton* browse;
    QPushButton* proceed;
    QPushButton* goBack;

    QLabel* AuthorLabel;
    QLabel* ISBNLabel;
    QLabel* genLabel;
    QLabel* titleLabel;
    QLabel* anLabel;
    QLabel* pathLabel;
    QLabel* errorMsg;

    QVBoxLayout* mainLayout;
    QHBoxLayout* authorPair;
    QHBoxLayout* ISBNPair;
    QHBoxLayout* anPair;
    QHBoxLayout* genPair;
    QHBoxLayout* pathPair;
    QHBoxLayout* titlePair;
    QHBoxLayout* proceedLayout;
    QHBoxLayout* goBackLayout;
    void InvalidInput(QString s);
signals:
private slots:
    bool CheckIfValidInputs();
    void BrowseForPath();
};

#endif // PUBLISHPAGE_H
