#include "dashboardui.h"

DashboardUI::DashboardUI(QWidget *parent) : QWidget(parent)
{



    mainLayout = new QVBoxLayout(this);
    sideMenu = new QVBoxLayout();
    content = new QVBoxLayout();
    searchBar = new QHBoxLayout();
    sideMenuAndContent = new QHBoxLayout();
    filters = new QHBoxLayout();

    menu= new QMenuBar();
    settings = new QMenu("text");

    searchField = new QLineEdit(this);
    author = new QLineEdit(this);
    ISBN = new QLineEdit(this);
    gen = new QLineEdit(this);
    //    filtersON = new QCheckBox("Filters", this);

    AuthorLabel = new QLabel("Author:", this);
    genLabel = new QLabel("Gen:", this);
    ISBNLabel = new QLabel("ISBN:", this);

    searchButton = new QPushButton("Search", this);
    goBack = new QPushButton("GO back", this);
    searchResults = new QListWidget(this);


    searchBar->addWidget(searchField);
    searchBar->addWidget(searchButton);

    filters->addWidget(AuthorLabel);
    filters->addWidget(author);
    filters->addWidget(ISBNLabel);
    filters->addWidget(ISBN);
    filters->addWidget(genLabel);
    filters->addWidget(gen);


    sideMenu->addWidget(goBack);


    menu->addMenu(settings);

    spoiler=new Spoiler("Filters");
    spoiler->setContentLayout(*filters);
    content->addLayout(searchBar);
    content->addWidget(spoiler);
    content->addWidget(searchResults);


    sideMenuAndContent->addLayout(sideMenu);
    sideMenuAndContent->addLayout(content);

    mainLayout->addWidget(menu);
    mainLayout->addLayout(sideMenuAndContent);


    connect(this->searchButton, SIGNAL(clicked()), this, SLOT(ChangeContent()));
    connect(this->goBack, SIGNAL(clicked()), this, SLOT(DeleteAllItems()));

}

void DashboardUI::ChangeContent()
{
    //    auto v = new searchResultsItem();
    //    auto h = new QListWidgetItem();
    //    h->setSizeHint(QSize(80, 100));
    //    searchResults->addItem(h);

    //    searchResults->setItemWidget(h, v);
    //    records.append(v);
    //    items.append(h);
    ClientThread::messageProtect.lock();
    *(ClientThread::pendingMessage) = "@SEARCH "+this->searchField->text()+"|"+this->author->text()+
            "|"+this->gen->text() + "|"+this->ISBN->text();
    ClientThread::messageProtect.unlock();
    //    records.back()->Setup("book", "1/5", "100");
    //    menu->setVisible(false);
    //    menu->setVisible(true);
}

void DashboardUI::AppendBooks(QVector<Book> books)
{
    qDebug()<<"Appendam carti!!!"<<Qt::endl;
    //sters initiale?
    for(auto& book: books)
    {
        auto v = new searchResultsItem();
        auto h = new QListWidgetItem();
        h->setSizeHint(QSize(80, 100));
        searchResults->addItem(h);
        records.append(v);
        items.append(h);

        searchResults->setItemWidget(h, v);
        records.back()->Setup(book.title, book.author, book.ISBN);
    }

    fflush(stdout);
}

void DashboardUI::DeleteAllItems()
{
    //    searchResults->clear();
    //    qDeleteAll(records.begin(), records.end());
    {
        for(int i=0; i<items.length(); i++)
        {
            searchResults->takeItem(i);
            delete items[i];
            delete records[i];
        }

    }
    records.clear();
    items.clear();
}
