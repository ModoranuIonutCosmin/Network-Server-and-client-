#include "recommandations.h"

Recommandations::Recommandations(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    sideMenu = new QVBoxLayout();
    content = new QVBoxLayout();
    sideMenuAndContent = new QHBoxLayout();

    menu= new QMenuBar();
    settings = new QMenu("text");

    title = new QLabel("Books recommended for you");
    title->setAlignment(Qt::AlignHCenter);
//    searchField = new QLineEdit(this);
//    author = new QLineEdit(this);
//    ISBN = new QLineEdit(this);
//    gen = new QLineEdit(this);
    //    filtersON = new QCheckBox("Filters", this);

//    AuthorLabel = new QLabel("Author:", this);
//    genLabel = new QLabel("Gen:", this);
//    ISBNLabel = new QLabel("ISBN:", this);



    goBack = new QPushButton("GO back", this);
    searchResults = new QListWidget(this);




    sideMenu->addStretch(1);
    sideMenu->addWidget(goBack);
    sideMenu->addStretch(1);
    sideMenu->setAlignment(goBack, Qt::AlignVCenter);
    sideMenu->setAlignment(goToRecomandations, Qt::AlignVCenter);


    menu->addMenu(settings);

    content->addWidget(searchResults);


    sideMenuAndContent->addLayout(sideMenu);
    sideMenuAndContent->addLayout(content);

    mainLayout->addWidget(menu);
    mainLayout->addWidget(title);
    mainLayout->addLayout(sideMenuAndContent);


//    connect(this->searchButton, SIGNAL(clicked()), this, SLOT(ChangeContent()));
//    connect(this->goBack, SIGNAL(clicked()), this, SLOT(DeleteAllItems()));
    connect(searchResults, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(GetClickedBook(QListWidgetItem*)));
//    connect(&tryAgain, SIGNAL(timeout()), this, SLOT(CheckSpam()));
}

void Recommandations::DoBooksList(QVector<Book> books)
{
    for(auto& book: books)
    {
        auto v = new searchResultsItem();
        auto h = new QListWidgetItem();
        h->setSizeHint(QSize(80, 100));
        searchResults->addItem(h);
        records.append(v);
        items.append(h);
        searchResults->setItemWidget(h, v);
        records.back()->Setup(book.title, book.author, book.genre, book.ISBN, book.rating, book.an, book.id_carte);

        fflush(stdout);
    }
}

void Recommandations::GetClickedBook(QListWidgetItem *item)
{

}
